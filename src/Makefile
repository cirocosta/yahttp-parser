CXX = /usr/bin/clang++-3.5
LEX		= flex
YACC	= bison

CXXFLAGS = -Wall -g -std=c++11 -Wno-deprecated-register
YFLAGS = -y -d
LFLAGS =

TESTS_D = ./tests

all: test.out

scanner.o: scanner.cc
parser.o: parser.cc
driver.o: driver.cc

test.out: $(TESTS_D)/test.cc parser.o scanner.o driver.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $^

scanner.cc: scanner.ll
	$(LEX) $(LFLAGS) -o $@ $^

parser.cc: parser.yy
	$(YACC) $(YFLAGS) -o $@ $^


.PHONY: clean

clean:
	find . -name "*.out" -delete & \
	find . -name "*.o" -delete & \
	$(RM) scanner.cc parser.cc parser.hh && touch parser.hh

