/*
 *
 * ====================================================================== \
 * NOTICE:
 * This Work is derived from the TestU01 Package. Translates portions of
 * the following source file to the c++ language: bat1.c. Names of
 * variables and functions have been preserved to some extent. Generic
 * procedures have been implemented using templates, and modules (c++20)
 * have been used for encapsulation.
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
 * source: main.cpp
 * author: misael-diaz
 * date:   2021/05/13
 *
 *
 * Synopsis:
 * A simple program that produces pseudo-random numbers PRNs by using
 * a "small" Linear Congruential Generator LCG.
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
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 *
 */

#include <iostream>
#include <vector>

import ULCG ;
import UNIF01 ;
import statistics ;

using namespace ulcg ;
using namespace stats ;
using namespace unif01 ;

typedef unif01_GenClass<LCG_param, LCG_state> unif01_Gen ;

int main() {

	// placeholder for pseudo-random numbers
        std::vector<double> prnums(0x00FFFFFF) ;

        // defines suitable parameters for a Small LCG:   (m, a, c, s)
        const std::vector<long> params{ 2147483647, 12001, 0, 12345 } ;

        unif01_Gen *gen = NULL ;
        gen = ulcg_CreateLCG (params) ; // creates LCG object


        for (auto& prnum: prnums)	// stores PRNs in placeholder
                prnum = gen -> GetU01(gen -> param, gen -> state) ;


	// displays the name and (current) state of the LCG
	std::cout << " " << gen -> name << ":" << std::endl ;
        gen -> Write(gen -> state) ;    
        gen = ulcg_DeleteGen (gen) ;    // destroys LCG object



	/* post-processing (small crush suite is yet to be implemented) */


	std::vector<double> q = quartiles(prnums) ;
	// displays the quartiles of the pseudo-random numbers
	std::cout << " quartiles (0.25, 0.50, 0.75): " << "(" <<
	    q[0] << ", " << q[1] << ", " << q[2] << ")" << std::endl ;


        return 0 ;

}

//
// Comments:
//
// Linear Congruential Generators LCGs are characterized by the following
// recurrence formula:
//
// 			s = (a * s + c) % m
//
// m: 	modulus
// a:	parameter
// c:	parameter
// s:	state
//
//
// Note that the seed defined in the params vector "initializes" the state
// of the LCG.
//
//


/*
 *
 * TODO:
 * [ ] Translate other LCG PRNGs defined in the source file ulcg.c.
 * [ ] Translate some of the tests defined in the small crush suite.
 * [ ] Use templates to translate generic procedures in small crush.
 *
 *
 */
