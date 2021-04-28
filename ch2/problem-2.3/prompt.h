#ifndef GUARD_MD_PROMPT_H
#define GUARD_MD_PROMPT_H

/*
 * source: prompt.h
 * author: misael-diaz
 * date:   2021/04/28
 *
 * Synopsis:
 * Defines a basic prompt using template classes.
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 * https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
 *
 */


#include <iostream>
#include <string>
#include <limits>

/* prototypes: */
void ignore_garbage(std::istream&) ;
std::istream& padding(std::istream&, const std::string&, int&) ;

template <class T>
std::istream& prompt(std::istream&, const std::string&, T&) ;

/* definitions: */
#include "prompt.cpp"
#endif
