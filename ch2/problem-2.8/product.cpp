/*
 * source: product.cpp
 * author: misael-diaz
 * date:   2021/03/26 
 *
 * Synopsis:
 * Solves problem 2-8, obtains the product of integers in the range [1, 10)
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 */

#include <iostream>

int main() {

	int prod = 1 ;
	// computes product of integers in the range [1, 10)
	for (int i = 1; i != 10; ++i) {
		prod *= i ;
	}

	// displays answer
	std::cout << "product of integers in the range [1, 10): "
		  << prod << std::endl ;

	return 0 ;
}
