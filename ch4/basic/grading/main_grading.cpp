/* 
 * Synopsis:
 * My version of the grading program, doesn't read values from standard
 * input. Samples random numbers from a uniform distribution to generate
 * the student homework grades. It also uses a template function for the
 * computation of the median.
 *
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 * Author: Misael Diaz-Maldonado             	March 30, 2021
 *
 * Revisions:
 * [1] partial partitioning             	April 07, 2021
 * [2] full paritioning				April 22, 2021
 *
 * TODO:
 * [x] partition into single tasks carried out by a function each
 * [x] put user-defined functions into appropriate headers
 *
 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include "report.h"
#include "grade.h"

int main() {
	// program reports the student his or her overall course grade

	// defines the midterm and final exam grades
	const double midterm = 85, final = 90 ;

	// generates the homework scores
	std::vector<double> homeworks ;
        setHomeworks(homeworks) ; // sampled from a random distribution

	try {
		// tries to obtain the overall score, reports if successful
		report(midterm, final, homeworks) ;
	} catch (std::domain_error err) {
		// catches exception if student did no homework
		std::cout << std::endl << err.what() << std::endl ;
	}

	return 0 ;
}

