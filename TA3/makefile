CXX = g++
CXXFLAGS = -Wall -g -fPIC
SOFLAGS = -shared

run: main

main: main.cpp libmandellib.so mandel.hpp
	$(CXX) $(CXXFLAGS) $< -L. -Wl,-rpath,. -lmandellib -o $@

libmandellib.so: mandel.o
	$(CXX) $(SOFLAGS) $^ -o $@

mandel.o: mandel.cpp mandel.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: clean cleanall run

clean:
	rm -f *.o

cleanall:
	rm -f *.o *.so main