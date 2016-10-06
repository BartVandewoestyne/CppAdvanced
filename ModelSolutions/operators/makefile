
#CXX = g++-4.9
CXXFLAGS = -Wall -Wextra -std=c++1y
LDFLAGS =  -lcppunit

RECIPE = $(LINK.cc) $^ -o $@

default: EndsWithTests unary_negate_tests

EndsWithTests.o: EndsWith.hpp
EndsWithTests: EndsWithTests.o 
	$(RECIPE)

unary_negate_tests.o: unary_negate.hpp EndsWith.hpp
unary_negate_tests: unary_negate_tests.o
	$(RECIPE)

clean:
	rm *.o
	rm EndsWithTests unary_negate_tests

make_run: default run

run:
	echo Running EndsWithTests
	./EndsWithTests
	echo
	echo Running unary_negate_tests
	./unary_negate_tests
	echo
