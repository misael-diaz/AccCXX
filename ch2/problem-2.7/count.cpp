/*
 * source: count.cpp
 * author: misael-diaz
 * date:   2021/03/26 
 *
 * Synopsis:
 * Solves problem 2-7 with standard library facilities. 
 * Prints the integers in the asymmetric range [10, -6).
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

	std::vector<int> x(16) ;		// preallocates vector
	std::iota(x.begin(), x.end(), 0) ;	// defines index: [0, 16)


	// transforms index to values in the sought range [10, -6)
	auto t = [](int i) { return (10 - i) ; } ;	/* lambda */
	std::transform(x.begin(), x.end(), x.begin(), t) ;


	std::streamsize w = std::cout.width() ;	// gets ostream width
	// displays the count down
	for (const auto& i: x) {
		// applies width and right "justifies" for alignment
		std::cout << std::setw(4) << std::right << i << std::endl ;
	}
	std::cout.width(w) ;	// restores ostream width

	return 0 ;
}
