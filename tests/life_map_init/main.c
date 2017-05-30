#include <stdio.h>
#include <life.h>


#define TEST(test, file, h, w)                                               \
    puts(test);                                                              \
    if (life_map_init(&map, file) == 1) {                                    \
        puts( test ": FAIL: uncorrect work" );                               \
    } else if (map.height != h || map.width != w) {                          \
        puts( test ": FAIL: uncorrect size");                                \
        printf("map.height = %i;\nmap.width = %i\n", map.height, map.width); \
    } else {                                                                 \
        life_map_print(&map);                                                \
        life_map_free(&map);                                                 \
    }                                                                        \
    puts("\n");


int main()
{
    life_map_t map;

    TEST("TEST 1",  "file_1",  3, 3);
    TEST("TEST 2",  "file_2",  3, 3);
    TEST("TEST 3",  "file_3",  0, 0);
    TEST("TEST 4",  "file_4",  1, 4);
    TEST("TEST 5",  "file_5",  3, 4);
    TEST("TEST 6",  "file_6",  3, 4);
    TEST("TEST 7",  "file_7",  3, 0);
    TEST("TEST 8",  "file_8",  6, 10);
    TEST("TEST 9",  "file_9",  2, 3);
    TEST("TEST 10", "file_10", 2, 3);
    
    return 0;
}
