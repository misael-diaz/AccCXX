/*
 * source: distinct_template.cpp
 * author: misael-diaz
 * date:   April 26, 2021
 *
 * Synopsis:
 * Defines a template function that determines the number of distinct
 * elements in a vector.
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * References:
 * A Koenig and B Moo, Accelerated C++ Practical Programming by Example
 *
 * TODO:
 * [x] consider writing a container-oblivious version
 *
 */

#include <algorithm>
#include <string>
#include <vector>

template <class Ran>
size_t distinct(Ran begin, Ran end) {
	// counts number of distinct elements in container
	/* assumes elements have been sorted in non-decreasing order */

	// invariant: we have counted/processed [count] elements so far
	size_t count = 0 ;
        while (begin != end) {
                size_t duplicates = 0 ;
		// invariant:
		// we have counted [duplicates] duplicates of the value
		// pointed to by the iterator [begin]
                for (Ran it = begin + 1; it != end; ++it) {
                        if (*it == *begin)
                                ++duplicates ;
                        else
                                break ;
                }
                ++begin += duplicates ;
                ++count ;
        }

	return count ;

}

template <class T>
typename std::vector<T>::size_type distinct(std::vector<T> vector) {
	// counts number of distinct elements in vector
        
	typedef typename std::vector<T>::size_type size ;

	std::sort(vector.begin(), vector.end()) ;	// sorts vector

	size i = 0 ;
	size vecsz = vector.size() ;
	size count = 0 ;
	// assumption: 
	// vector elements have been sorted in non-decreasing order
	// loop invariant: 
        // we have counted [i] elements of the vector and
        // have found [count] distinct elements so far
        while (i != vecsz) {
                size duplicates = 0 ;
                // loop invariant: 
                // we have counted [duplicates] duplicates of the 
                // [i]th element of the vector so far
                for (size j = i + 1; j != vecsz; ++j) {
                        if (vector[j] == vector[i])
                                ++duplicates ;
                        else
                                break ;
                }
                ++i += duplicates ;
                ++count ;
        }

	return count ;
}
