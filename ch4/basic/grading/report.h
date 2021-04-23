#ifndef GUARD_REPORT_H
#define GUARD_REPORT_H

/* 
 *
 * Synopsis:
 * Declares functions tasked with producing reports.
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

// declarations
void report_hw(const std::vector<double>&) ;
void report_median(const std::vector<double>&) ;
void report_average(const std::vector<double>&) ;
void report(const double&) ;
void report(const double&, const double&, const std::vector<double>&) ;

#endif
