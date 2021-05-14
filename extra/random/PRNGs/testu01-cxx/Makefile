#!/usr/bin/make
#
#
# source: Makefile
# author: misael-diaz
# date:   2021/05/13
#
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
#
# Copyright (c) 2021 Misael Diaz-Maldonado
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#

include make-inc

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXOPT) $(OBJECTS) -o $(EXEC) $(LIBS)\
	       	-Wl,-rpath -Wl,$(LIBSTDCXX_DIR)

$(MOD_UTIL_O): $(MOD_UTIL)
	$(CXX) $(CXXOPT) -c $(MOD_UTIL) -o $(MOD_UTIL_O)

$(MOD_UNIF01_O): $(MOD_UTIL_O) $(MOD_UNIF01)
	$(CXX) $(CXXOPT) -c $(MOD_UNIF01) -o $(MOD_UNIF01_O)

$(MOD_ULCG_O): $(MOD_UTIL_O) $(MOD_UNIF01_O) $(MOD_ULCG)
	$(CXX) $(CXXOPT) -c $(MOD_ULCG) -o $(MOD_ULCG_O)

$(MOD_STAT_O): $(MOD_STAT)
	$(CXX) $(CXXOPT) -c $(MOD_STAT) -o $(MOD_STAT_O)

$(MAIN_O): $(MODS_O) $(MAIN)
	$(CXX) $(CXXOPT) -c $(MAIN) -o $(MAIN_O)

clean:
	/bin/rm -rf $(ALL_OBJECTS) $(EXEC) $(GCM_CACHE)
