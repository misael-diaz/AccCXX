/*
 * source: frequency.cpp
 * author: misael-diaz
 * date:   2021/05/04
 *
 * Synopsis:
 * Reports frequency of student grades. 
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
 *
 */

#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <cmath>
#include <map>

void push(std::vector<double>& vector) ;
void limit(std::vector<double>& vector) ;
std::string arange(const auto& m, double w) ;

int main() {

	// fills vector with grades in the range [0, 100)
	std::vector<double> x ;	push(x) ; limit(x) ;

	double w = 10 ;	/* bin width */
	std::map<double, int> map ;		// grade-based association
	for(double i{0} ; const auto& value: x) {
		i  = std::floor(0.10 * value) ;
		(i > 5) ? ++map[i]: ++map[.0] ;	// groups failure scores
	}

	// reports frequency in tabulated form
	std::streamsize osw = std::cout.width() ;
	std::cout << "bin\t range   \t frequency" << std::endl ; // header
	for(int bin{0} ; const auto& m: map) {

		std::string range = arange(m, w) ;

		std::cout << bin++ << "\t " << std::setw(8)
			  << range << "\t " << m.second << std::endl ;

	}
	std::cout.width(osw) ;

	return 0 ;
}

std::string arange(const auto& m, double w) {
	// defines range of bin (note failure scores are grouped)

	size_t i = std::floor(w * m.first) ;
	size_t j = (i == 0) ? std::floor( w * (m.first + 6) ):
			      std::floor( w * (m.first + 1) ) ;

	std::string range ;
	if (i == 90) {	/* last bin is inclusive by definition */
		range = "[" + std::to_string(i) + "-" +
			      std::to_string(j) + "]" ;
	} else {	/* exclusive */
		range = "[" + std::to_string(i) + "-" +
			      std::to_string(j) + ")" ;
	}

	return range ;
}

void push(std::vector<double>& vector) {
	// pushes doubles from a uniform distribution to the back of vector

        std::random_device randev ; 
        std::default_random_engine generator( randev() ) ;
        std::uniform_real_distribution<double> distribution(0, 100) ;

	for(int i = 0 ; i != 1024 ; ++i)
		vector.push_back( distribution(generator) ) ;

}

void limit(std::vector<double>& vector) {
	// limits vector from above to ensure "inclusiveness" of last bin

	for(auto& x: vector)
		x = (x > 99.99) ? 99.99: x ;

}
