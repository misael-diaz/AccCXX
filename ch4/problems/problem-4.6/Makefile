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

$(ROSTER_EXEC): $(ROSTER_O)
	$(CXX) $(CXXOPT) $(ROSTER_O) -o $(ROSTER_EXEC) $(LIBS)\
	       	-Wl,-rpath -Wl,$(LIBSTDCXX_DIR)

$(MAIN_EXEC): $(OBJECTS)
	$(CXX) $(CXXOPT) $(OBJECTS) -o $(MAIN_EXEC) $(LIBS)\
	       	-Wl,-rpath -Wl,$(LIBSTDCXX_DIR)

$(MOD_STUDENT_INFO_O): $(MOD_STATISTICS) $(MOD_STUDENT_INFO)
	$(CXX) $(CXXOPT) -c $(MOD_STUDENT_INFO) -o $(MOD_STUDENT_INFO_O)

$(MOD_STATISTICS_O): $(MOD_STATISTICS)
	$(CXX) $(CXXOPT) -c $(MOD_STATISTICS) -o $(MOD_STATISTICS_O)

$(MAIN_O): $(MOD_STATISTICS_O) $(MOD_STUDENT_INFO_O) $(MAIN)
	$(CXX) $(CXXOPT) -c $(MAIN) -o $(MAIN_O)

clean:
	/bin/rm -rf $(ALL_OBJECTS) $(EXEC) $(GCM_CACHE)
