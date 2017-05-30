TEST_NAME = life_step


###########################################################################
# SOURCES AND OBJECTS
EXEC = tests/$(TEST_NAME)/bin/$(TEST_NAME)

OBJS = tests/$(TEST_NAME)/objs/main.o \
	   tests/$(TEST_NAME)/objs/life.o 

SRC  = tests/$(TEST_NAME)/main.c \
	   src/life.c


###########################################################################
# TARGETS

all: $(EXEC)
	

$(EXEC): $(OBJS)
	gcc $(OBJS) $(ALL_INCS) -o $(EXEC)


tests/$(TEST_NAME)/objs/main.o: tests/$(TEST_NAME)/main.c
	gcc $(CFLAGS) $(ALL_INCS) -c tests/$(TEST_NAME)/main.c -o tests/$(TEST_NAME)/objs/main.o
	

tests/$(TEST_NAME)/objs/life.o: src/life.c
	gcc $(CFLAGS) $(ALL_INCS) -c src/life.c -o tests/$(TEST_NAME)/objs/life.o


clean:
	@rm -f tests/$(TEST_NAME)/obj/*.o
	@rm -f tests/$(TEST_NAME)/bin/life
