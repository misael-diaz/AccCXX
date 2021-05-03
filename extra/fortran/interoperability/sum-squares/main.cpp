/*
 * source: main.cpp
 * author: misael-diaz
 * date:   2021/05/03
 *
 * Synopsis:
 * Computes the sum of the squares of a vector using standard library
 * facilities and a Fortran subroutine.
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 * S. J. Chapman, Fortran for Scientists and Engineers
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include "macros.h"

extern"C" void sum_squares(double*, double*) ;

int main() {

	std::vector<double> x(N), squares(N) ;
	std::iota(x.begin(), x.end(), 0) ;
	auto square = [](double value) { return (value * value) ; }  ;
	std::transform(x.begin(), x.end(), squares.begin(), square) ;

	double sum = 0 ;
	sum = std::accumulate(squares.begin(), squares.end(), sum) ;

	double total ;
	sum_squares(&x[0], &total) ;
	std::cout << "sum:   " << sum   << std::endl ;
	std::cout << "total: " << total << std::endl ;

	return 0 ;
}
