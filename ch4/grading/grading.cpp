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
 * Author: Misael Diaz-Maldonado             March 30, 2021
 *
 * Revisions:
 * [1] program partitioning                  April 7, 2021
 *
 * TODO:
 * [x] partition into single tasks carried out by a function each
 * [ ] put user-defined functions into appropriate headers
 *
 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <ios>
#include <iomanip>
#include <numeric> // provides the std::accumulate() function
#include "median.h"

// function declarations
void setHomeworks(std::vector<double>&) ;
double grade(const double&, const double&, const std::vector<double>&) ;

void is_empty(const std::vector<double>&) ;
void report_hw(const std::vector<double>&) ;
void report_median(const std::vector<double>&) ;
void report_average(const std::vector<double>&) ;
void report(const double&) ;
void report(const double&, const double&, const std::vector<double>&) ;

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

void is_empty(const std::vector<double>& vector) {
	        
	// complains if the vector is empty
        std::vector<double>::size_type size = vector.size() ;
        if (size == 0) {
                throw std::domain_error(
                    "no scores have been defined for the student homeworks"
                ) ;
        }

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

void setHomeworks(std::vector<double>& homeworks) {
        // samples homework grades from a uniform random distribution

	const int n = 8 ; // defines the number of homeworks
        std::default_random_engine generator ;
        std::uniform_real_distribution<double> distribution(65.0, 98.0) ;

        for(int i = 0; i != n; ++i) 
                homeworks.push_back( distribution(generator) ) ;

	return ;
}

double grade(const double& midterm, const double& final, 
	     const std::vector<double>& homeworks) {
	// determines the student's overall course grade

        // complains if student did no homework
        is_empty(homeworks) ;

	return 0.2 * midterm + 0.4 * final + 0.4 * median(homeworks) ;
}

