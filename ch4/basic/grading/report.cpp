/* 
 * Synopsis:
 * Defines functions for reporting on the students grades.
 *
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 * Author: Misael Diaz-Maldonado             April 08, 2021
 *
 * TODO:
 * [ ] put user-defined functions into appropriate headers
 *
 */

/* REMOVE UNNEEDED HEADERS */
#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <ios>
#include <iomanip>
#include <numeric> // provides the std::accumulate() function
#include "median.h"
#include "grade.h"
#include "report.h"

void report(const double& midterm, const double& final, 
	    const std::vector<double>& homeworks) {

        // obtains the overall course score and reports
        double overall ;
        overall = grade(midterm, final, homeworks) ; /* throws exception */
	
	report_hw(homeworks) ;       
	report_median(homeworks) ;
	report_average(homeworks) ;
	report(overall) ;

	return ;
}

void report(const double& overall) {
	// reports the overall course score
	
	std::streamsize prec = std::cout.precision() ;
        std::cout << "your overall course grade is: "
                << std::setprecision(3) << overall
                << std::setprecision(prec) << std::endl ;

	return ;
}

void report_hw(const std::vector<double>& homeworks) {
	// displays the homework scores to user

        // displays grades to stdout
        std::cout << "homework grades: " << std::endl ;
	// stores the default precision and changes it to four digits
        std::streamsize prec = std::cout.precision(4) ;
        for(const auto& homework: homeworks)
                std::cout << homework << std::endl ;
        // restores the default precision
        std::cout.precision(prec);
	
	return ;
}

void report_median(const std::vector<double>& hw) {
        // computes and reports the median of the homework scores
	
	// complains if student did no homework
	is_empty(hw) ;
	std::vector<double>::const_iterator b = hw.begin() ;
	std::vector<double>::const_iterator e = hw.end() ;
	double d = 0 ; /* dummy argument */

	std::streamsize prec = std::cout.precision() ;
        std::cout << "your homework grade via the median is: "
                << std::setprecision(3) << median(b, e, d)
                << std::setprecision(prec) << std::endl ;

	return ;
}

void report_average(const std::vector<double>& hw) {
	// reports the average homework score

        const std::vector<double>::size_type count = hw.size() ;
        
	double total = 0 ; // total homework score accumulator
	total = std::accumulate(hw.begin(), hw.end(), total);

	std::streamsize prec = std::cout.precision() ;
        std::cout << "your homework grade via the average is: "
                << std::setprecision(3) << (total / count)
		<< std::setprecision(prec) << std::endl ;

	return ;
}

