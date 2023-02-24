
.PHONY: all
all: main

CXX=g++
LDFLAGS=-lpthread
CXXFLAGS=-lpthread -std=c++2a

main: main.cpp
	g++ main.cpp $(CXXFLAGS) $(LDFLAGS) -o main

.PHONY: clean
clean:
	rm -rf main.o main

