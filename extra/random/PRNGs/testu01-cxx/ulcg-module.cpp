/*
 *
 * ====================================================================== \
 * NOTICE:
 * This Work is Derived from the TestU01 Package. Translates portions of
 * the following source file to the c++ language: ulcg.c. Names of
 * variables and functions have been preserved to some extent. Generic
 * procedures have been implemented using templates, and modules (c++20)
 * have been used for encapsulation. Argument lists of built-in types
 * to functions have been replaced by a container holding the values
 * of the arguments. Some functions have been partioned further for
 * simplicity. Memory management functions return a pointer to the
 * (de)allocated object.
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
 * source: ulcg-module.cpp
 * author: misael-diaz
 * date:   2021/05/13
 *
 *
 * Synopsis:
 * Implements a "small" Linear Congruential Generator LCG.
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
 *
 */

module ;
#include <vector>
#include <cstddef>
#include <climits>
#include <iostream>
#include <stdexcept>
import UTIL ;
import UNIF01 ;


export module ULCG ;

export namespace ulcg {
	// interface:


	typedef struct {	// parameters of the prng
                long M, A, C, q, r ;
                double Norm ;
        } LCG_param ;


        typedef struct {        // state of the prng
                long S ;
        } LCG_state ;
	

	// functions
	unif01::unif01_GenClass<LCG_param, LCG_state>*
	    ulcg_CreateLCG (const std::vector<long>&) ; // creates  Gen

	unif01::unif01_GenClass<LCG_param, LCG_state>*
            ulcg_DeleteGen (				// destroys Gen
		unif01::unif01_GenClass<LCG_param, LCG_state>*
	    ) ;

}

// implementation:

// type definitions for simplicity
typedef ulcg::LCG_param LCG_param ;
typedef ulcg::LCG_state LCG_state ;


typedef unif01::unif01_GenClass<LCG_param, LCG_state> unif01_Gen ;


// function declarations:
void ulcg_CheckLCG_Params (const std::vector<long>& Parameters) ;
void ulcg_CheckLCG_Vector (const std::vector<long>& Parameters) ;
void ulcg_CheckLCG_Values (const std::vector<long>& Parameters) ;

void WrLCG (LCG_state *state) ;
double SmallLCG_U01 (LCG_param *param, LCG_state *state) ;
unsigned long SmallLCG_Bits (LCG_param *param, LCG_state *state) ;


// function definitions:
unif01_Gen* ulcg::ulcg_CreateLCG (const std::vector<long>& Parameters) {
	// creates a linear congruential generator
        

	unif01_Gen *gen  = NULL ;
	LCG_param *param = NULL ;
	LCG_state *state = NULL ;


	ulcg_CheckLCG_Params(Parameters) ;	// validates input


	// unpacks vector of parameters
	const long m = Parameters[0] ;	// modulus
	const long a = Parameters[1] ;	// constant
	const long c = Parameters[2] ;	// constant
	const long s = Parameters[3] ;	// seed

	
	gen = util::util_Malloc(gen) ;
	param = util::util_Malloc(param) ;
	state = util::util_Malloc(state) ;


	param -> M = m ;
	param -> A = a ;
	param -> C = c ;
	param -> q = m / a ;		// quotient
	param -> r = m % a ;		// reminder
	param -> Norm = 1.0 / m ;

	state -> S = s ;


	gen -> param   = param ;
	gen -> state   = state ;
	// TODO: set it up so that the "name" is determined at runtime
	gen -> name    = std::string("SmallLCG_U01") ;
	gen -> Write   = &WrLCG ;
	gen -> GetU01  = &SmallLCG_U01 ;
	gen -> GetBits = &SmallLCG_Bits ;


        return gen ;

}


void ulcg_CheckLCG_Params(const std::vector<long>& Parameters) {
	// complains if input is invalid


	ulcg_CheckLCG_Vector(Parameters) ;
	ulcg_CheckLCG_Values(Parameters) ;

}


void ulcg_CheckLCG_Vector(const std::vector<long>& Parameters) {

	if (Parameters.size() != 4) {
                throw std::domain_error (
                    "uclg_CreateLCG:    invalid vector"
                ) ;
        }

}


void ulcg_CheckLCG_Values(const std::vector<long>& Parameters) {
        
	// unpacks
        const long m = Parameters[0] ;      // modulus
        const long a = Parameters[1] ;      // constant
        const long c = Parameters[2] ;      // constant
        const long s = Parameters[3] ;      // seed

        if ( (a < 0) || (c < 0) || (s < 0) ) {

                throw std::domain_error (
                    "ulcg_CreateLCG:    Invalid parameter"
                ) ;

        } else if ( (a >= m) || (c >= m) || (s >= m) || (m <= 0) ) {

                throw std::domain_error (
                    "ulcg_CreateLCG:    Invalid parameter"
                ) ;

	}


	/* NOTE: only the SmallLCG has been implemented */
	if (m - 1 > (LONG_MAX - c) / a) {
                throw std::domain_error (
                    "ulcg_CreateLCG:    Medium or Larger LCGs "
		    "have not been implemeneted"
                ) ;
	}
	
}


void WrLCG (LCG_state *state) {	// writes state to the std ostream

	std::cout << " s = " << state -> S << std::endl ;

}


double SmallLCG_U01 (LCG_param *param, LCG_state *state) {
	// implements a small LCG:    a * (m - 1) + c    holds a long int

	state -> S = (param -> A * state -> S + param -> C) % param -> M ;
	return ( state -> S * param -> Norm ) ;

}

unsigned long SmallLCG_Bits (LCG_param *param, LCG_state *state) {
	/* TODO: implement */

	throw std::runtime_error("not implemented") ;
	return 0UL ;

}


unif01_Gen* ulcg::ulcg_DeleteGen (unif01_Gen* gen) { // Destroys generator
	
	return unif01::unif01_DeleteGen (gen) ;

}




