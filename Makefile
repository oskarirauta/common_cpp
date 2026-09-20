all: world
CXX?=g++
CXXFLAGS?=--std=c++20 -Wall -fPIC -g

INCLUDES+= -I./include

OBJS:= \
	objs/main.o

COMMON_DIR:=.
include ./Makefile.inc

world: example

$(shell mkdir -p objs)

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

example: $(COMMON_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@;

.PHONY: clean
clean:
	@rm -f objs/*.o example
	@rmdir objs
