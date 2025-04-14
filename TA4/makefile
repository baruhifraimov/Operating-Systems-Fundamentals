CXX = g++
CXXFLAGS = -Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $< -o $@

clean:
	rm *.gcov