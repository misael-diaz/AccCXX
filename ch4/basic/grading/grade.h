#ifndef GUARD_GRADE_H
#define GUARD_GRADE_H
/* 
 * Synopsis:
 * Declares grading (related) functions.
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
// function declarations
void is_empty(const std::vector<double>&) ;
void setHomeworks(std::vector<double>&) ;
double grade(const double&, const double&, const std::vector<double>&) ;
#endif
