#ifndef _LIFE_H_
#define _LIFE_H_


#include <stdint.h>


typedef struct {

    uint32_t height;
    uint32_t width;
    char ** map;

} life_map_t;


typedef struct {

    char * cfg_file_name;
    int    sleep_time;

} life_settings_t;



int life_argv_parse(int argc, 
                    char * argv[], 
                    life_settings_t * settings);


int life_map_init(life_map_t * map, 
                  char * cfg_name);


void life_map_free(life_map_t * map);


int life_map_alloc(life_map_t * map);


void life_map_print(const life_map_t const * map);


void life_step(life_map_t * map);


#endif
