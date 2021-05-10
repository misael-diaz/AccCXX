/*
 * source: squares.cpp
 * author: misael-diaz
 * date:   2021/04/30
 *
 * Synopsis:
 * Solves problem 4-4, prints squares of doubles in the range [0, 1000)
 * in tabulated format.
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
 * www.cplusplus.com/reference/string/to_string/
 * www.cplusplus.com/reference/ios/right/
 *
 * TODO:
 * [ ] iterate range and squares vectors simultaneously with a zip-iterator
 *
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <string>

int numDigits(int) ;
std::streamsize ndigits(int) ;
std::streamsize ndigits(const std::vector<int>&) ;

using std::cout ;
using std::endl ;
using std::setw ;
using std::iota ;
using std::right ;
using std::vector ;
using std::transform ;
using std::streamsize ;
using std::scientific ;
using std::setprecision ;

int main() {

	// defines vector with integral values in the range [0, 1000)
	vector<int> range(1000) ;
	iota(range.begin(), range.end(), 0) ;
	// finds suitable streamsize based on the maximum number of digits
	streamsize w = ndigits(range) ;


	// squares computation
	vector<double> squares(1000) ;
	auto square = [](int i) { return ( (double) (i * i) ) ; } ;
	transform(range.begin(), range.end(), squares.begin(), square) ;


	streamsize osw  = cout.width() ;
	streamsize prec = cout.precision() ;
	// displays squares in tabulated format, tab delimited
	for (int i{0} ; const auto& square: squares) {

		/* use zip-iterator to iterate both range and squares */
		cout << setw(w) << right << i++ << "\t" << setw(24)
		     << setprecision(15) << right << scientific << square
		     << endl ;

	}
	cout.width(osw) ;
	cout.precision(prec) ;
	return 0 ;
}

std::streamsize ndigits(const std::vector<int>& v) {
	// returns the maximum number of digits in a vector of integers

        std::vector<int>::const_iterator
		max = std::max_element(v.begin(), v.end()) ;
        std::streamsize size = ndigits(*max) ;
	return size ;
}

std::streamsize ndigits(int i) {
	// returns the number of digits of an integer

	std::string str = std::to_string(i) ;
	std::streamsize size = str.size() ;
	return size ;
}

int numDigits(int i) {
	// obtains the number of digits using integer arithmetic (unused)

	int digits = 1 ;
	// invariant: integer /i/ has known /digits/ digits
	while (i /= 10)
		++digits ;

	return (digits) ;
}
