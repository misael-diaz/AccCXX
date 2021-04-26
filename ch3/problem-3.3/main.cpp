/*
 * source: main.cpp
 * author: misael-diaz
 * date:   March 28, 2021
 *
 * Synopsis:
 * Solves part of problem 3-3, counts the number of distinct elements of
 * a vector of strings.
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
 * Revisions:
 * 	April 26, 2021
 * 		* partitions code
 * 		* uses template function for counting distinct elements
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include "distinct_template.h"

int main(){
	// program obtains the number of distinct elements in vector

	// creates a vector of zeroes
	std::vector<int> zeros(8, 0) ;
	// creates a vector of integers in the range [0, 8)
	std::vector<int> range{0, 1, 2, 3, 4, 5, 6, 7} ;
	// creates a vector having repeated values
	std::vector<int> repls{0, 0, 0, 1, 1, 2, 3, 4} ;
	// creates a vector of strings
	std::vector<std::string> strings{
		"mom", "dad", "sister", "brother", "grandfather",
		"grandmother", "uncle", "aunt"
	} ;

	// finds and displays number of distinct elements for each vector
	{
	std::vector<int>::size_type count = distinct(zeros) ;
	std::cout << "zeros.distinct():\t\t" << count << std::endl ;
	}

	{
	std::vector<int>::size_type count = distinct(range) ;
	std::cout << "range.distinct():\t\t" << count << std::endl ;
	}

	{
	std::vector<int>::size_type count = distinct(repls) ;
	std::cout << "repls.distinct():\t\t" << count << std::endl ;
	}

	{
	std::vector<std::string>::size_type count = distinct(strings) ;
	std::cout << "strings.distinct():\t\t" << count << std::endl ;
	}

	{ /* invokes container oblivious version */
        std::vector<int>::size_type count = distinct(
			repls.begin(), repls.end(), 0
	) ;
        std::cout << "repls.distinct():\t\t" << count << std::endl ;
        }

	return 0 ;
}
