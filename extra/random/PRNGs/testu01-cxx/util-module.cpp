/*
 *
 * ====================================================================== /
 * NOTICE:
 * This Work is derived from the TestU01 Package. Translates portions of
 * the following source file to the c++ language: util.c. Names of
 * variables and functions have been preserved to some extent. Generic
 * procedures (or functions) have been implemented using templates,
 * and modules (c++20) have been used for encapsulation. Memory management
 * functions return a pointer to the (de)allocated object. Memory
 * allocations with malloc have been replaced by the operator new().
 * Since the operator throws std::bad_alloc exception by default, malloc
 * checks have been dropped from the allocator utilities.
 * ====================================================================== /
 *
 *
 *
 *
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal.
 * e-mail: lecuyer@iro.umontreal.ca
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted without a fee for private, research,
 * academic, or other non-commercial purposes.
 * Any use of this software in a commercial environment requires a
 * written licence from the copyright owner.
 *
 * Any changes made to this package must be clearly identified as such.
 *
 * In scientific publications which used this software, a reference to it
 * would be appreciated.
 *
 * Redistributions of source code must retain this copyright notice
 * and the following disclaimer.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 *
 * Derived Work
 *
 * source: util-module.cpp
 * author: misael-diaz
 * date:   2021/05/13
 * 
 *
 * Synopsis:
 * Defines memory management utilities.
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 *
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 *
 */


module ;
#include <cstddef>
export module UTIL ;

export namespace util {


	template <class T> T* util_Malloc (T *p) {
		// allocates memory for object
	
		p = new (T) ;
		return p ;
	}


	template <class T> T* util_Free (T *p) {
        	// frees allocated memory

		if (p == NULL) {
			return NULL ;
		} else {
        		delete p ;
			return NULL ;
		}
	}


}
