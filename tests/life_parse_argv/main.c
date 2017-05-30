#include <stdlib.h>
#include <stdio.h>
#include <life.h>
#include <string.h>
#include <assert.h>


int main() 
{
    
    life_settings_t settings;


    char * test_1[]  = {"aaa", "-f", 0};
    assert( life_argv_parse(2, test_1,  &settings) == LIFE_ERR_ARG_VAL_EMPTY );


    char * test_2[]  = {"aaa", "-f", "-t", 0};
    assert( life_argv_parse(3, test_2,  &settings) == LIFE_OK );
    assert( strcmp(settings.cfg_file_name, "-t") == 0 );


    char * test_3[]  = {"aaa", "-f", "file", 0}; 
    assert( life_argv_parse(3, test_3,  &settings) == LIFE_OK );
    assert( strcmp(settings.cfg_file_name, "file") == 0 );


    char * test_4[]  = {"aaa", "-f", "file file", 0};  
    assert( life_argv_parse(3, test_4,  &settings) == LIFE_OK );
    assert( strcmp(settings.cfg_file_name, "file file") == 0 );


    char * test_5[]  = {"aaa", "-f", "file", "-t", 0};
    assert( life_argv_parse(4, test_5,  &settings) == LIFE_ERR_ARG_VAL_EMPTY );


    char * test_6[]  = {"aaa", "-f", "-t", "56", 0};
    assert( life_argv_parse(4, test_6,  &settings) == LIFE_ERR_ARG_UNKNOWN );


    char * test_7[]  = {"aaa", "-f", "file", "-t", "100", 0};
    assert( life_argv_parse(5, test_7,  &settings) == LIFE_OK );
    assert( strcmp(settings.cfg_file_name, "file") == 0 );
    assert( settings.sleep_time == 100 );


    char * test_8[]  = {"aaa", "-t", "-45", 0};
    assert( life_argv_parse(3, test_8,  &settings) == LIFE_OK );
    assert( settings.sleep_time == -45 );


    char * test_9[]  = {"aaa", "-t", "-t", 0}; 
    assert( life_argv_parse(3, test_9,  &settings) == LIFE_ERR_ARG_VAL_SYNTAX );


    char * test_10[] = {"aaa", "-t", "100", 0};
    assert( life_argv_parse(3, test_10, &settings) == LIFE_OK );
    assert( settings.sleep_time == 100 );


    char * test_11[] = {"aaa", "-t", "100", "45", 0};
    assert( life_argv_parse(4, test_11, &settings) == LIFE_ERR_ARG_UNKNOWN );


    char * test_12[] = {"aaa", "-t", "wqeqwe", 0};
    assert( life_argv_parse(3, test_12, &settings) == LIFE_ERR_ARG_VAL_SYNTAX );


    char * test_13[] = {"aaa", "-t", "45qwe56", 0};
    assert( life_argv_parse(3, test_13, &settings) == LIFE_ERR_ARG_VAL_SYNTAX );


    char * test_14[] = {"aaa", "-t", "qwe56", 0};
    assert( life_argv_parse(3, test_14, &settings) == LIFE_ERR_ARG_VAL_SYNTAX );


    return 0;
}
