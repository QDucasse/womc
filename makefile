# Choose your compiler (depending on your environment clang/gcc)
CC=gcc

# Add flags to the compilation
CC_FLAGS= -Wpedantic -Wall -Wextra -g

# These variables hold the name of all source files/headers/object files
SRCS=$(wildcard src/*.c)
HDRS=$(wildcard src/*.h)
OBJS=$(patsubst src/%.c,bin/%.o,$(SRCS))
<<<<<<< HEAD

TST_SRCS=$(wildcard tests/*.c)
TST_HDRS=$(wildcard tests/*.h)
TST_OBJS=$(filter-out bin/main.o, $(OBJS))
=======
TST_SRCS=$(wildcard tests/*.c)
TST_HDRS=$(wildcard tests/*.h)
TST_OBJS=$(filter-out bin/main.o, $(OBJS)) $(patsubst tests/%.c,bin/%.o,$(TST_SRCS))
>>>>>>> 628f55bffc1c989e5278053af5249069bb09c04a

MU_TST_SRCS=$(wildcard mutests/*.c) mutests/munit/munit.c
MU_TST_HDRS=$(wildcard mutests/*.h) mutests/munit/munit.h
MU_TST_OBJS=$(filter-out bin/main.o, $(OBJS))

# To display one of the above variable, uncomment the next line
# $(info SRCS is $(SRCS))
# $(info HDRS is $(HDRS))
# $(info OBJS is $(OBJS))
# $(info TST_SRCS is $(TST_SRCS))
<<<<<<< HEAD
# $(info TST_OBJS is $(TST_OBJS))
# $(info MU_TST_SRCS is $(MU_TST_SRCS))
# $(info MU_TST_HDRS is $(MU_TST_HDRS))
# $(info MU_TST_OBJS is $(MU_TST_OBJS))
=======
# $(info TST_HDRS is $(TST_HDRS))
# $(info TST_OBJS is $(TST_OBJS))
>>>>>>> 628f55bffc1c989e5278053af5249069bb09c04a

default: bin/womc
tests: bin/tests
mutests: bin/mutests

# This rule produces the executable by compiling and linking all objects
# $^ are the names of all prerequisites (the object files)
# $@ is the name of the target (bin/womc in this case)
bin/womc: $(OBJS)
	$(CC) $^ -o $@ 
# must start with TAB character

# This rule produces all object files
# -c option tells gcc to only compile one source file at a time
#  $< is the name of the first prerequisite (the c file in this case)
bin/%.o: src/%.c $(HDRS)
	$(CC) $< $(CC_FLAGS) -c -o $@ 
# must start with TAB character

<<<<<<< HEAD
# To use munit the test suite written in tests/mutests will be executed
bin/tests: $(TST_SRCS) $(TST_OBJS)
	$(CC) $^ $(TST_HDRS) $() $(CC_FLAGS) -o $@ 


# To use munit the test suite written in tests/mutests will be executed
bin/mutests: $(MU_TST_SRCS) $(MU_TST_OBJS)
	$(CC) $^ $(MU_TST_HDRS) $() $(CC_FLAGS) -o $@ 
=======
# Similar rules for tests, munit is handled separately and linked against the rest
bin/tests: $(TST_OBJS) bin/munit.o
	$(CC) $^ -o $@

bin/%.o: tests/%.src $(TST_HEADERS) tests/munit/munit.h
	$(CC) $< $(CC_FLAGS) -c -o $@ 

bin/munit.o: tests/munit/munit.c tests/munit/munit.h
	$(CC) $< $(CC_FLAGS) -c -o $@ 
>>>>>>> 628f55bffc1c989e5278053af5249069bb09c04a

.PHONY: clean

clean:
	rm -f $(OBJS) bin/womc bin/tests bin/mutests