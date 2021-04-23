/* 
 * Synopsis:
 * TO ADD
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

#include <vector>
#include <random>
#include "median.h"
#include "grade.h"

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

