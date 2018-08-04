C_FILES=amiget.c metaparser.c utility.c list.c

all: test amiga

build_tests:
	g++ -o tests_run -g -Wall test/UNIT_test_suite.cpp -lgtest -lpthread 

test: build_tests
	./tests_run

gdbtest: build_tests
	gdb ./tests_run

valgrind: build_tests
	valgrind ./tests_run

amiga:
	vc +aos68k -c99 -I${NDK_INC} -lamiga -lauto ${C_FILES} -o ../bin/amiget 

