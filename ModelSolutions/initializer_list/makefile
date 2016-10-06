
#CXX = g++-4.9
CXXFLAGS = -Wall -Wextra -std=c++1y
LDFLAGS =  -lcppunit

RECIPE = $(LINK.cc) $^ -o $@

default: SearchableStackTests

SearchableStackTests.o: SearchableStack.hpp 
SearchableStackTests: SearchableStackTests.o
	$(RECIPE)

clean:
	rm *.o
	rm SearchableStackTests

make_run: default run

run:
	echo Running SearchableStackTests
	./SearchableStackTests
	echo

