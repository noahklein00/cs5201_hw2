###############################################################################
## -->Makefile<--
###############################################################################
##
## Programmer : Noah Klein
## Instructor : Price
## Class      : CS5201 Spring 2020
## Assignment : Homework 2 - Templated Interpolator
## Filename   : Makefile
##
###############################################################################

###############################################################################
## This makefile will build an executable for the 2020-sp-a-hw2-nekgr8 directory.
###############################################################################

CXX = /usr/bin/g++
FLAGS = -W -Wall -g -pedantic-errors
OBJECTS = driver.o

.SUFFIXES: .cpp

.cpp.o: $<
	${CXX} -c ${FLAGS} $< -o $@

default: all

all: hw2.out

hw2.out: ${OBJECTS}
	${CXX} ${FLAGS} ${OBJECTS} -o $@

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f hw2.out > /dev/null 2>&1
	-@rm -f ${OBJECTS} > /dev/null 2>&1
	
# Dependency lists for the various source files
driver.o: driver.cpp\
          interpolator.h\
          interpolator.hpp
	g++ -c driver.cpp