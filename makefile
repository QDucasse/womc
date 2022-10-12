# Choose your compiler (depending on your environment clang/gcc)
CC=gcc

# Add flags to the compilation

CC_FLAGS= -Wpedantic -Wall -Wextra -g

# These variables hold the name of all source files/headers/object files
SRCS=$(wildcard src/*.c)
HDRS=$(wildcard src/*.h)
OBJS=$(patsubst src/%.c,bin/%.o,$(SRCS))

TST_SRCS=$(wildcard tests/*.c) tests/munit/munit.c
TST_HDRS=$(wildcard tests/*.h) tests/munit/munit.h
TST_OBJS=$(filter-out bin/main.o, $(OBJS))

# To display one of the above variable, uncomment the next line
# $(info SRCS is $(SRCS))
# $(info HDRS is $(HDRS))
# $(info OBJS is $(OBJS))
# $(info TST_SRCS is $(TST_SRCS))
# $(info TST_HDRS is $(TST_HDRS))

default: bin/womc
tests: bin/tests

# This rule produces the executable by compiling and linking all objects
# $< are the names of all prerequisites (the object files)
# $@ is the name of the target (bin/womc in this case)
bin/womc: $(OBJS)
	$(CC) $^ $(CC_FLAGS) -o $@ 
# must start with TAB character

# This rule produces all object files
# -c option tells gcc to only compile one source file at a tile
#  $< is the name of the first prerequisite (the c file in this case)
bin/%.o: src/%.c $(HDRS)
	$(CC) $< $(CC_FLAGS) -c -o $@ 
# must start with TAB character

bin/tests: $(TST_OBJS)
	$(CC) $(TST_SRCS) $^ $(TST_HDRS) $() $(CC_FLAGS) -o $@ 

.PHONY: clean

clean:
	rm -f $(OBJS) bin/womc bin/tests