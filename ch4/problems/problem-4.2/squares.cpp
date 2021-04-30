/*
 * source: squares.cpp
 * author: misael-diaz
 * date:   2021/04/30 
 *
 * Synopsis:
 * Solves problem 4-2 with standard library facilities: 
 * cout, setw, vector, iota (c++11), transform, lambdas (c++11), type
 * deduction (auto keyword), range-based for loop with initializer (c++20).
 *
 * Prints squares of integers up to 100 in tabulated format.
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
 * www.learncpp.com/cpp-tutorial/for-each-loops/
 * www.cplusplus.com/reference/numeric/iota/
 * en.cppreference.com/w/cpp/language/lambda
 * www.cplusplus.com/reference/ios/right/
 *
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>

int main() {

	// defines vector with integral values in the range [0, 101)
	std::vector<int> squares(101) ;		
	std::iota(squares.begin(), squares.end(), 0) ;


	// squares computation
	auto square = [](int i) { return (i*i) ; } ;	/* lambda */
	
	std::transform(
		squares.begin(), squares.end(), squares.begin(), square
	) ;


	/* displays squares in tabulated format, tab delimited */
	std::streamsize w = std::cout.width() ;	// gets ostream width
	for (int i{0} ; const auto& square: squares) {

		// applies width and right "justifies" for alignment
		std::cout << std::setw(4) << std::right << i++ << "\t" <<
			std::setw(8) << std::right << square << std::endl ;

	}
	std::cout.width(w) ;	// restores ostream width
	return 0 ;
}
