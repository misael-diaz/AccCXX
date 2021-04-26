#ifndef GUARD_MD_DISTINCT_TEMPLATE_H
#define GUARD_MD_DISTINCT_TEMPLATE_H
#include <string>
#include <vector>

/*
 * source: distinct_template.cpp
 * author: misael-diaz
 * date:   April 26, 2021
 *
 * Synopsis:
 * Declares template functions for determining the number of distinct
 * elements in a vector.
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 */

template <class Ran, class T> size_t distinct(const Ran&, const Ran&, T) ;

template <class T>
typename std::vector<T>::size_type distinct(std::vector<T> vector) ;

#include "distinct_template.cpp"
#endif
