#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h> 
#include <life.h>


#define EMPTY  '0'
#define ALIVE  '1'
#define CHILD  '2'
#define CORPSE '3'

static int
life_cfg_read_map_size(FILE * cfg, life_map_t * map)
{
    uint32_t width = 0;

    map->height = 0;
    map->width  = 0;

    for ( int ch = getc(cfg); ch != EOF; ch = getc(cfg) ) {

        if (ch == ';') {

            ++map->height;

            if (width > map->width) {
                map->width = width;
            }

            width = 0;

        } else if ( !isspace(ch) && ch != EOF) {
            
            ++width;

        }
    } 

    if (width)
        ++map->height;


    if ( ferror(cfg) ) {
        fprintf(stderr, "Error: %s: %s: %i: error at reading cfg file.\n", 
                         __FILE__, __func__, __LINE__);
        return 1;
    }


    return 0;
}


static int
life_cfg_read_map(FILE * cfg, life_map_t * map)
{
    size_t i = 0;
    size_t j = 0;

    for ( int ch = getc(cfg); ch != EOF; ch = getc(cfg) ) {

        if (ch == ';') {

            ++i;
            j = 0;

        } else if (ch == '0') {

            ++j;

        } else if (!isspace(ch) && ch != EOF) {

            map->map[i][j] = ALIVE;
            ++j;

        }
    } 


    if ( ferror(cfg) ) {
        fprintf(stderr, "Error: %s: %s: %i: error at reading cfg file.\n", 
                         __FILE__, __func__, __LINE__);
        return 1;
    }


    return 0;
}


static int
life_cfg_read(FILE * cfg, life_map_t * map)
{
    if ( life_cfg_read_map_size(cfg, map) ) {
        return 1;
    }


    rewind(cfg);


    if ( life_map_alloc(map) )
        return 1;

    
    if ( life_cfg_read_map(cfg, map) ) {
        life_map_free(map);
        return 1;
    }

    return 0;
}


int 
life_argv_parse(int argc, char * argv[], life_settings_t * settings)
{
    for (int i = 1; i < argc; ++i) {

        if ( strcmp(argv[i], "-f") == 0 ) {

            ++i;
            if (argv[i] == 0) {

                fprintf(stderr, "Error: %s: %s: %i: \"-f\" is missing value.\n", 
                                 __FILE__, __func__, __LINE__);

                return 1;
            }

            settings->cfg_file_name = argv[i];

        } else if ( strcmp(argv[i], "-t") == 0) {

            ++i;
            if (argv[i] == 0) {

                fprintf(stderr, "Error: %s: %s: %i: \"-t\" is missing value.\n", 
                                 __FILE__, __func__, __LINE__);

                return 1;
            }

            char * endptr = 0;

            settings->sleep_time = strtol(argv[i], &endptr, 10);
            if (*endptr != '\0') {

                fprintf(stderr, "Error: %s: %s: %i: \"-t\" value is uncorrect.\n", 
                                 __FILE__, __func__, __LINE__);

                return 1;
            }

        } else {
            fprintf(stderr, "Error: %s: %s: %i: unknown parametr.\n", 
                             __FILE__, __func__, __LINE__);
            return 1;
        }
    }

    return 0;
}



int life_map_init(life_map_t * map, char * cfg_name)
{
    FILE * cfg = fopen(cfg_name, "rb");
    if ( !cfg ) {

        fprintf(stderr, "Error: %s: %s: %i: failed \"fopen()\".\n", 
                         __FILE__, __func__, __LINE__);
        perror("Errno");
        return 1;
    }


    int rc = 0;
    rc = life_cfg_read(cfg, map);

       
    if ( fclose(cfg) == EOF ) {
        fprintf(stderr, "Error: %s: %s: %i: failed \"fclose()\".\n", 
                         __FILE__, __func__, __LINE__);
        rc = 1;
    }


    return rc;
}


void life_map_free(life_map_t * map)
{
    for (size_t i = 0; i < map->height; ++i)
        free( map->map[i] );
    
    free( map->map );
}


int life_map_alloc(life_map_t * map)
{
    map->map = (char**) malloc( map->height * sizeof(char*) );

    if (map->map == NULL) {
        fprintf(stderr, "Error: %s: %s: %i: failed memory allocation.\n", 
                         __FILE__, __func__, __LINE__);
        perror("Errno");
        return 1;
    }


    for (size_t i = 0; i < map->height; ++i) {
        
        map->map[i] = (char*) malloc( map->width * sizeof(char) );

        if (map->map[i] == NULL) {
            fprintf(stderr, "Error: %s: %s: %i: failed memory allocation.\n", 
                             __FILE__, __func__, __LINE__);
            perror("Errno");
            return 1;
        }

        memset(map->map[i], EMPTY, map->width);
    }

    return 0;
}


void life_map_print(const life_map_t const * map)
{
    for (size_t i = 0; i < map->height; ++i) {
        
        for (size_t j = 0; j < map->width; ++j) {
            putchar( map->map[i][j] );
            putchar(' ');
        }

        putchar('\n');
    }
}


static int life_cell_neighbours(const life_map_t const * map,   
                                const size_t i, 
                                const size_t j)
{
    int neighbours = 0;

    // check column left from map->map[i][j]
    if ( i > i - 1) {
        
        if (j > j - 1)
            if ( map->map[i - 1][j - 1] == ALIVE || map->map[i - 1][j - 1] == CORPSE )
                ++neighbours;
        
        if ( map->map[i - 1][j] == ALIVE || map->map[i - 1][j] == CORPSE )
            ++neighbours;
        
        if ( (j < j + 1) && (j + 1 < map->width) )
            if ( map->map[i - 1][j + 1] == ALIVE || map->map[i - 1][j + 1] == CORPSE )
                ++neighbours;
    }


    // check cells above and under map->map[i][j]
    if (j > j - 1)
        if ( map->map[i][j - 1] == ALIVE || map->map[i][j - 1] == CORPSE )
            ++neighbours;


    if ( (j < j + 1) && (j + 1 < map->width) )
        if ( map->map[i][j + 1] == ALIVE || map->map[i][j + 1] == CORPSE)
            ++neighbours;


    // check column right from map->map[i][j]
    if ( (i < i + 1) && (i + 1 < map->height) ) {
        
        if (j > j - 1)
            if ( map->map[i + 1][j - 1] == ALIVE || map->map[i + 1][j - 1] == CORPSE )
                ++neighbours;
        
        if ( map->map[i + 1][j] == ALIVE || map->map[i + 1][j] == CORPSE )
            ++neighbours;
        
        if ( (j < j + 1) && (j + 1 < map->width) )
            if ( map->map[i + 1][j + 1] == ALIVE || map->map[i + 1][j + 1] == CORPSE )
                ++neighbours;
    }
    

    return neighbours;
}


void life_step(life_map_t * map)
{
    // create children
    for (size_t i = 0; i < map->height; ++i) 
        for (size_t j = 0; j < map->width; ++j) 
            if (map->map[i][j] == EMPTY)
                if ( life_cell_neighbours(map, i, j) == 3 )
                    map->map[i][j] = CHILD;


    // death of adults from under or overpopulation
    for (size_t i = 0; i < map->height; ++i) 
        for (size_t j = 0; j < map->width; ++j) 
            if (map->map[i][j] == ALIVE) {
                int neighbours = life_cell_neighbours(map, i, j);
                if (neighbours < 2 || neighbours > 3)
                    map->map[i][j] = CORPSE;
            }


    // delete corpses of dead adults
    for (size_t i = 0; i < map->height; ++i) 
        for (size_t j = 0; j < map->width; ++j) 
            if (map->map[i][j] == CORPSE) 
                map->map[i][j] = EMPTY;


    // children become adult
    for (size_t i = 0; i < map->height; ++i) 
        for (size_t j = 0; j < map->width; ++j) 
            if (map->map[i][j] == CHILD) 
                map->map[i][j] = ALIVE;


    return 0;
}
