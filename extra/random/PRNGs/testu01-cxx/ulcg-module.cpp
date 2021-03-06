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

void ulcg_implCheckLCG (const long& c) ;
void ulcg_implCheckLCG (const long& q, const long& r) ;
void ulcg_implCheckLCG (const long& c, const long& q, const long& r) ;
void ulcg_implCheckLCG (const std::vector<long>& Parameters) ;



unif01_Gen* ulcg_createLCG (const std::vector<long>&) ;	// core
unif01_Gen* ulcg_createLCG (LCG_param*, LCG_state*) ;	// distinctive
unif01_Gen* ulcg_createLCG (unif01_Gen*) ;	// small LCGs


unif01_Gen* ulcg_createLCG (unif01_Gen*, const long&, const long&,
		            const long&) ; // selects Medium - Large LCGs


unif01_Gen* ulcg_createLCG (unif01_Gen*, const long&) ; // Medium LCGs
unif01_Gen* ulcg_createLCG (unif01_Gen*, const long&, const long&) ;// Larg



void WrLCG (LCG_state*) ;


double SmallLCG_U01 (LCG_param*, LCG_state*) ;
unsigned long SmallLCG_Bits (LCG_param*, LCG_state*) ;


double MediumLCG_U01 (LCG_param*, LCG_state*) ;
unsigned long MediumLCG_Bits (LCG_param*, LCG_state*) ;


double MediumMLCG_U01 (LCG_param*, LCG_state*) ;
unsigned long MediumMLCG_Bits (LCG_param*, LCG_state*) ;



// function definitions:
unif01_Gen* ulcg::ulcg_CreateLCG (const std::vector<long>& Parameters) {
	// creates a linear congruential generator

	ulcg_CheckLCG_Params(Parameters) ;	// validates input
	return ulcg_createLCG(Parameters) ;

}


void ulcg_CheckLCG_Params(const std::vector<long>& Parameters) {
	// complains if input is invalid


	ulcg_CheckLCG_Vector(Parameters) ;
	ulcg_CheckLCG_Values(Parameters) ;

}


void ulcg_CheckLCG_Vector(const std::vector<long>& Parameters) {

	if (Parameters.size() != 4) {
                throw std::domain_error (
                    "ulcg_CreateLCG:    invalid vector"
                ) ;
        }

}


void ulcg_CheckLCG_Values(const std::vector<long>& Parameters) {
        
	// unpacks
        const long& m = Parameters[0] ;      // modulus
        const long& a = Parameters[1] ;      // constant
        const long& c = Parameters[2] ;      // constant
        const long& s = Parameters[3] ;      // seed

        if ( (a < 0) || (c < 0) || (s < 0) ) {

                throw std::domain_error (
                    "ulcg_CreateLCG:    Invalid parameter"
                ) ;

        } else if ( (a >= m) || (c >= m) || (s >= m) || (m <= 0) ) {

                throw std::domain_error (
                    "ulcg_CreateLCG:    Invalid parameter"
                ) ;

	}

	// checks if the LCG's been implemented
	ulcg_implCheckLCG(Parameters) ;

}

void ulcg_implCheckLCG (const std::vector<long>& Parameters) {

        // unpacks
        const long& m = Parameters[0] ;	// modulus
        const long& a = Parameters[1] ;	// constant
        const long& c = Parameters[2] ;	// constant

	const long q = m / a ;		// quotient
	const long r = m % a ;		// reminder


        /* NOTE: only the SmallLCG has been implemented */
        if (m - 1 > (LONG_MAX - c) / a) {

		ulcg_implCheckLCG (c, q, r) ; 	// Medium LCGs

        } else {

		return ;	// Small LCGs
	}
	

}

void ulcg_implCheckLCG (const long& q, const long& r) {
	// checks implementation status of Large LCGs

	throw std::domain_error (
		"ulcg_CreateLCG: Large LCGs are yet to be implemented"
	) ;

}

void ulcg_implCheckLCG (const long& c, const long& q, const long& r) {

	if (r > q) {

		ulcg_implCheckLCG(q, r) ;	// Large LCGs

	} else {

		ulcg_implCheckLCG(c) ;		// Medium LCGs

	}

	return ;

}

void ulcg_implCheckLCG(const long& c) {

	if (c != 0) {	// Medium LCGs

		return ;

	} else {	// Medium MLCGs

		return ;
	}

	return ;

}

unif01_Gen* ulcg_createLCG (const std::vector<long>& Parameters) {
        /* defines the "Core" characteristics of the LCG */

	LCG_param *param = NULL ;
	LCG_state *state = NULL ;

	param = util::util_Malloc(param) ;
	state = util::util_Malloc(state) ;

	param -> M = Parameters[0] ;
	param -> A = Parameters[1] ;
	param -> C = Parameters[2] ;
	state -> S = Parameters[3] ;		// state
	param -> q = param -> M / param -> A ;	// quotient
	param -> r = param -> M % param -> A ;	// reminder
	param -> Norm = 1.0 / param -> M ;

	return ulcg_createLCG (param, state) ;

}


unif01_Gen* ulcg_createLCG (LCG_param* param, LCG_state* state) {
	/* defines the "Distinctive" characteristics */

	unif01_Gen *gen = NULL ;
	gen = util::util_Malloc(gen) ;

	gen -> param   = param ;
	gen -> state   = state ;

	if (param -> M - 1 > (LONG_MAX - param -> C) / param -> A) {

		return ulcg_createLCG (	// selects Medium - Large LCGs
			gen, param -> C, param -> q, param -> r
		) ;

	} else {

		return ulcg_createLCG (gen) ;	// Small LCGs

	}

}

unif01_Gen* ulcg_createLCG (unif01_Gen* gen) {

	gen -> name    = std::string("SmallLCG_U01") ;
	gen -> Write   = &WrLCG ;
	gen -> GetU01  = &SmallLCG_U01 ;
	gen -> GetBits = &SmallLCG_Bits ;

	return gen ;
}

unif01_Gen* ulcg_createLCG (unif01_Gen* gen, const long& c,
			    const long& q,   const long& r) {

	if (r > q) {

		return ulcg_createLCG (gen, q, r) ;	// Large LCGs

	} else {

		return ulcg_createLCG (gen, c) ;	// Medium LCGs

	}

}

unif01_Gen* ulcg_createLCG (unif01_Gen* gen, const long& q, const long& r)
{

	throw std::domain_error (
		"ulcg_CreateLCG: Large LCGs are yet to be implemented"
	) ;

	return NULL ;

}

unif01_Gen* ulcg_createLCG (unif01_Gen* gen, const long& c) {


	if (c != 0) {	// Medium LCGs

		gen -> name    = std::string("MediumLCG_U01") ;
		gen -> Write   = &WrLCG ;
		gen -> GetU01  = &MediumLCG_U01 ;
		gen -> GetBits = &MediumLCG_Bits ;
		return gen ;

	} else {	// Medium MLCGs

		gen -> name    = std::string("MediumMLCG_U01") ;
		gen -> Write   = &WrLCG ;
		gen -> GetU01  = &MediumMLCG_U01 ;
		gen -> GetBits = &MediumMLCG_Bits ;
		return gen ;

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

	unsigned long bits = (
		unif01::unif01_NORM32 * SmallLCG_U01 (param, state)
	) ;

	return bits ;

}

double MediumLCG_U01 (LCG_param *param, LCG_state *state) {
	// implements a medium LCG:  ( r < q  &&  (c != 0) )


	long k = state -> S / param -> q ;
	state -> S = param -> A * (state -> S - k * param -> q) - k *
		     param -> r ;

	if (state -> S < 0)
		state -> S += param -> C ;
	else
		state -> S = (state -> S - param -> M) + param -> C ;

	if (state -> S < 0)
		state -> S += param -> M ;

	return (state -> S * param -> Norm) ;

}

unsigned long MediumLCG_Bits (LCG_param *param, LCG_state *state) {
	
	unsigned long bits = (
		unif01::unif01_NORM32 * MediumLCG_U01 (param, state)
	);

	return bits ;
}


double MediumMLCG_U01 (LCG_param *param, LCG_state *state) {
	// LCG implementation is applied when r < q and c = 0

	long k = state -> S / param -> q ;
	state -> S = param -> A * (state -> S - k * param -> q) - k *
	             param -> r ;

	if (state->S < 0)
		state -> S += param -> M ;

	return (state->S * param->Norm) ;
}


unsigned long MediumMLCG_Bits (LCG_param *param, LCG_state *state) {

	unsigned long bits = (
		unif01::unif01_NORM32 * MediumMLCG_U01 (param, state)
	) ;

	return bits ;
}



unif01_Gen* ulcg::ulcg_DeleteGen (unif01_Gen* gen) { // Destroys generator

	return unif01::unif01_DeleteGen (gen) ;

}
