/*
 * source: automatic_alignment_squares.cpp
 * author: misael-diaz
 * date:   2021/04/30 
 *
 * Synopsis:
 * Prints squares of integers in the range [0, 1000) in tabulated format.
 * 
 * The following standard library facilities are used to solve problem 4-3:
 * cout, setw, vector, string, iota (c++11), transform, max_element, 
 * lambdas (c++11), to_string (c++11), type deduction (auto keyword), 
 * range-based for loop with initializer (c++20).
 *
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * Comments:
 * There are alternatives for obtaining the number of digits of an integer,
 * some better than others. Finding the most efficient way to do this has
 * been asked before (see stackoverflow thread listed in the references).
 *
 * Even though performance is one of my main concerns when writing code,
 * I prefer to rely (as much as possible) on the facilities provided by
 * the standard library. That's my reasoning for converting the integer
 * to a string to obtain the number of digits. How efficient that approach
 * might be compared to others is an interesting question that deserves
 * attention in the near future.
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
 * (stackoverflow.com/questions/1489830/efficient-way-to-determine-
 *  number-of-digits-in-an-integer)
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

int main() {

	// defines vector with integral values in the range [0, 1000)
	std::vector<int> squares(1000) ;		
	std::iota(squares.begin(), squares.end(), 0) ;
	// finds suitable streamsize based on the maximum number of digits
	std::streamsize w1 = ndigits(squares) ;	


	// squares computation
	auto square = [](int i) { return (i*i) ; } ;	/* lambda */
	
	std::transform(
		squares.begin(), squares.end(), squares.begin(), square
	) ;

	std::streamsize w2 = ndigits(squares) ;
	std::streamsize osw = std::cout.width() ;
	/* displays squares in tabulated format, tab delimited */
	for (int i{0} ; const auto& square: squares) {

		std::cout << std::setw(w1) << std::right << i++ << "\t" 
			  << std::setw(w2) << std::right << square 
			  << std::endl ;

	}
	std::cout.width(osw) ;	// restores ostream width
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
	// determines the number of digits using integer arithmetic

	int digits = 0 ;
	while (i /= 10)
		++digits ;

	return (++digits) ;
}
