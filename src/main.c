#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <life.h>


#define SLEEP_TIME_DEFAULT 3


int main(int argc, char * argv[]) 
{
    life_settings_t settings = {NULL, SLEEP_TIME_DEFAULT};


    if ( life_argv_parse(argc, argv, &settings) ) {
        return 1;
    }


    life_map_t map;
    if ( life_map_init(&map, settings.cfg_file_name) ) {
        return 1;
    }

    
    while (1) {
        system("clear");
        life_map_print(&map);
        sleep( settings.sleep_time );
        life_step(&map);
    }


    life_map_free( &map );

    return 0;
}
