#!/usr/bin/make
#
# source: Makefile
# author: misael-diaz
# date:   2021/05/03
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2021 Misael Diaz-Maldonado
#
# This file is released under the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

include make-inc

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXOPT) $(OBJECTS) -o $(EXEC) $(LIBS)

$(SUB_O): $(HEADER) $(SUB)
	$(FC) $(FCOPT) -c $(SUB) -o $(SUB_O)

$(MAIN_O): $(HEADER) $(SUB_O) $(MAIN)
	$(CXX) $(CXXOPT) -c $(MAIN) -o $(MAIN_O)

clean:
	rm -f $(OBJECTS) $(EXEC)
