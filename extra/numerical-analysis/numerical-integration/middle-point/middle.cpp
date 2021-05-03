/*
 * source: middle.cpp
 * author: misael-diaz
 * date:   2021/05/03
 *
 * Synopsis:
 * Possible implementation of the middle point method.
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
 * [1] A Gilat and V Subramanian, Numerical Methods for Engineers and 
 *     Scientists, 3rd edition.
 * [2] A Koenig and B Moo, Accelerated C++ Practical Programming by
 *     Example.
 * [3] https://en.cppreference.com/w/cpp/language/lambda
 *
 */


#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// defines the objective function
auto objf = [](double value) { return value * value ; } ;
double mid(int, double, double) ;

int main() {

	const int N = 16 ;			// number of intervals
	double l = 0 ;	double u = 1 ;		// limits (l, u)
	double exact = 1.0 / 3 ;

	double integral = mid(N, l, u) ;
	double error    = (1.0 - integral / exact) * 100.0 ;

	std::cout << "integral:\t" << integral << std::endl ;
	std::cout << "\%error: \t" << error    << std::endl ;
	
	return 0 ;

}

double mid(int N, double l, double u) {
	// uses the middle point to approximate the integral

	const double step = (u - l) / N ;	// step-size, dx
	const double xi = l + 0.5 * step ;	// initial mid coord
	std::vector<double> x(N) ;		// middle coordinates
	std::vector<double> heights(N) ;	// heights, f(x)

	auto mcoord = [&xi, &step](double pos){
		return (xi + pos * step) ;	// returns mid coord
	} ;
	
	std::iota(x.begin(), x.end(), 0) ;
	std::transform(x.begin(), x.end(), x.begin(), mcoord) ;
	std::transform(x.begin(), x.end(), heights.begin(), objf) ;
	
	double sum = 0 ;
	sum = std::accumulate(heights.begin(), heights.end(), sum) ;

	return (step * sum) ;
}
