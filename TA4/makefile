CXX = g++
CXXFLAGS = -Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage

run: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $< -o $@

clean:
	rm *.h.gcov *.tcc.gcov