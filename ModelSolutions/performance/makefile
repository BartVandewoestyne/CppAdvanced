

CXXFLAGS = -Wall -Wextra -std=c++1y -O2

RECIPE = $(LINK.cc) $^ -o $@

#strings :CXXFLAGS+= -O2 -fprofile-instr-generate
strings: strings.o
	$(RECIPE)

strings_scoped.o: ScopedDuration.hpp
strings_scoped: strings_scoped.o
	$(RECIPE)


make_run: strings_scoped
	echo Running strings_scoped
	./strings_scoped
	echo	
