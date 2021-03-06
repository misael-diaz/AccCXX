/*
 *
 * source: stats-module.cpp
 * author: misael-diaz
 * date:   2021/05/03
 *
 *
 * Synopsis:
 * Defines the statistics module.
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 *
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 *
 * Revisions:
 * 	2021/05/05	implements the mean (or average) function
 * 	2021/05/09      adds the median function
 *	2021/05/13      removes unused variables
 *
 *
 *
 *
 */

module ;

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

export module statistics ;

typedef std::vector<double>::size_type size ;
std::vector<double> odd(std::vector<double>) ;
std::vector<double> even(std::vector<double>) ;
std::vector<double> avg(size, size, size, const std::vector<double>&) ;
std::vector<double> exact(size, size, size, const std::vector<double>&) ;
std::vector<double> odd(size, size, size, const std::vector<double>&) ;
std::vector<double> even(size, size, size, const std::vector<double>&) ;
double interpolate(double, double, double) ;

export namespace stats {
	double median (std::vector<double>) ;
	double mean (const std::vector<double>&) ;
	std::vector<double> quartiles (const std::vector<double>&) ;
}

double stats::median (std::vector<double> v) {
        // computes the median of a vector of doubles

        const std::vector<double>::size_type v_size = v.size() ;
        const std::vector<double>::size_type mid    = v_size / 2 ;

        if (v_size == 0) {
                throw std::domain_error("empty vector") ;
        }

        std::sort( v.begin(), v.end() ) ;

        return ( (v_size % 2)? v[mid]: 0.5 * (v[mid] + v[mid - 1]) ) ;

}


double stats::mean(const std::vector<double>& x) {
	// returns the mean value of a vector of doubles

	if (x.size() == 0) {
		throw std::domain_error("empty vector") ;
	}

	double sum = 0 ;
	return ( std::accumulate(x.begin(), x.end(), sum) / x.size() ) ;

}

std::vector<double> stats::quartiles(const std::vector<double>& x) {
	// returns the quartiles of a vector

	if (x.size() == 0) {
		throw std::domain_error("empty vector") ;
	}

	std::vector<double> q ; // quartiles
	if (x.size() % 2) {
		q = odd(x) ;
	} else {
		q = even(x) ;
	}

        return q ;

}

std::vector<double> odd(std::vector<double> x) {
	// returns the quartiles of a vector with an odd number of elements
	
	std::vector<double> quartiles ;
	std::sort( x.begin(), x.end() ) ;

	// initializes indexes for determining q1, q2, and q3, respectively
	size sz  = x.size() ;
	size b  =     sz / 4 ;
	size m  =     sz / 2 ;
	size a  = 3 * sz / 4 ;

	// obtains the quartiles based on the location of the middle value
	if (m % 2) {
		quartiles = avg(b, m, a, x) ;
	} else {
		quartiles = exact(b, m, a, x) ;
	}

	return quartiles ;
}
std::vector<double> exact(size b, size m, size a,
		         const std::vector<double>& x) {
	// obtains the quartiles through indexing (exact values)

	double q1, q2, q3 ;		// quartiles
	q1 = x[b] ;	q2 = x[m] ;	q3 = x[a] ;
	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}
std::vector<double> avg(size b, size m, size a,
		        const std::vector<double>& x) {
	// obtains quartiles with averages

	double q1, q2, q3 ;		// quartiles

	if (m == 0) {
		q1 = q2 = q3 = x[m] ;	// vector of a single element
	} else {
		q1 = 0.5 * (x[b] + x[b + 1]) ;
		q2 = x[m] ;
		q3 = 0.5 * (x[a] + x[a - 1]) ;
	}

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}

std::vector<double> even(std::vector<double> x) {
	// returns the quartiles for a vector having a pair of values

	std::vector<double> quartiles ;
	std::sort( x.begin(), x.end() ) ;

	// initializes indexes for determining q1, q2, and q3, respectively
	size sz  = x.size() ;
	size b  =     sz / 4 ;	// below the median
	size m  =     sz / 2 ;	// median
	size a  = 3 * sz / 4 ;	// above the median

	if (m % 2) {
		quartiles = odd(b, m, a, x) ;
	} else {
		quartiles = even(b, m, a, x) ;
	}

	return quartiles ;

}

std::vector<double> even(size b, size m, size a,
		         const std::vector<double>& x) {
	// Computes the quartiles when x.size() / 4 is an even integer,
	// that is the number of elements in vector is a multiple of 4.

	double alpha ;
	double q1, q2, q3 ;                     // quartiles

	alpha = 0.25 ;  q1 = interpolate(x[b - 1], x[b], 1. - alpha) ;
	alpha = 0.50 ;  q2 = alpha * (x[m - 1] + x[m]) ;
	alpha = 0.75 ;  q3 = interpolate(x[a - 1], x[a], 1. - alpha) ;

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;
}


std::vector<double> odd(size b, size m, size a,
		         const std::vector<double>& x) {
	// Computes the quartiles when x.size() / 4 is an odd integer.
	// The vector has an even number of elements but the number of
	// elements is not a multiple of 4.

	double alpha ;
	double q1, q2, q3 ;                     // quartiles

	alpha = 0.25 ;  q1 = interpolate(x[b], x[b + 1], alpha) ;
	alpha = 0.50 ;  q2 = alpha * (x[m - 1] + x[m]) ;
	alpha = 0.75 ;  q3 = interpolate(x[a - 1], x[a], alpha) ;

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}

double interpolate(double x1, double x2, double alpha) {
	// applies linear interpolation to obtain the quartile

	double x = x1 + alpha * (x2 - x1) ;
	return x ;
}
