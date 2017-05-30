###########################################################################
# SOURCES AND OBJECTS
###########################################################################

EXEC = bin/life

OBJS = objs/main.o \
	   objs/life.o

SRC  = src/main.c \
	   src/life.c


###########################################################################
# COMPILER'S OPTIONS
###########################################################################

ALL_INCS = -I "src/"
CFLAGS = -pipe -Wall -Wextra -pedantic -g


###########################################################################
# TARGETS
###########################################################################

all: $(EXEC)
	

$(EXEC): $(OBJS)
	gcc $(OBJS) $(ALL_INCS) -o $(EXEC)


objs/main.o: src/main.c
	gcc $(CFLAGS) $(ALL_INCS) -c src/main.c -o objs/main.o
	

objs/life.o: src/life.c
	gcc $(CFLAGS) $(ALL_INCS) -c src/life.c -o objs/life.o


clean:
	@rm -f objs/*.o
	@rm -f bin/life

###########################################################################
# STATIC ANALYSIS
###########################################################################

analys: cppcheck scan-build

cppcheck:
	cppcheck --enable=all --std=c11 $(SRC) 

scan-build:
	scan-build make
	make clean


###########################################################################
# TESTS
###########################################################################

export CFLAGS
export ALL_INCS

life_parse_argv:
	make -f tests/life_parse_argv/Makefile

life_map_init:
	make -f tests/life_map_init/Makefile

life_step:
	make -f tests/life_step/Makefile
