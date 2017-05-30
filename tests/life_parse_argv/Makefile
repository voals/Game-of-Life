###########################################################################
# TEST VARIABLES	
TEST_NAME = life_parse_argv
TEST_DIR = tests/life_parse_argv


###########################################################################
# SOURCES AND OBJECTS
EXEC = $(TEST_DIR)/bin/$(TEST_NAME)

OBJS = $(TEST_DIR)/objs/main.o \
	   objs/life.o

SRC  = $(TEST_DIR)/main.c \
	   src/life.c


###########################################################################
# COMPILER'S OPTIONS
ALL_INCS = -I "src/"
CFLAGS = -pipe -Wall -Wextra -pedantic -g


###########################################################################
# TARGETS

all: $(EXEC)
	

$(EXEC): $(OBJS)
	gcc $(OBJS) $(ALL_INCS) -o $(EXEC)


$(TEST_DIR)/objs/main.o: $(TEST_DIR)/main.c
	gcc $(CFLAGS) $(ALL_INCS) -c $(TEST_DIR)/main.c -o $(TEST_DIR)/objs/main.o
	

objs/life.o: src/life.c
	gcc $(CFLAGS) $(ALL_INCS) -c src/life.c -o objs/life.o


clean:
	@rm -f objs/life.o
	@rm -f $(TEST_DIR)/obj/*.o
	@rm -f $(TEST_DIR)/bin/life


###########################################################################
# STATIC ANALYSIS
analys: cppcheck scan-build

cppcheck:
	cppcheck --enable=all --std=c11 $(SRC) 

scan-build:
	scan-build make
	make clean
