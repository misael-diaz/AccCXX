/*
 * source: module-student-info.cpp
 * author: misael-diaz
 * date:   2021/05/07
 *
 * Synopsis:
 * Defines the student info module.
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * References:
 * A Koenig and B Moo, Accelerated C++: Practical Programming by Example 
 * 
 * TODO:
 * [x] import the statistics module to be able to use the median
 *
 */

module ;
#include <stdexcept>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
import statistics ;

export module student_info ;

export struct StudentInfo ;
export bool compare (const StudentInfo&, const StudentInfo&) ;
export std::ifstream& read (std::ifstream&, StudentInfo&) ;
export double grade (const StudentInfo&) ;

struct StudentInfo {
	std::string name ;
	double midterm, final ;
	std::vector<double> homeworks ;
} ;

double grade (double, double, double) ;
double grade (double, double, const std::vector<double>&) ;
std::ifstream& read_hw (std::ifstream&, std::vector<double>&) ;

bool compare (const StudentInfo& x, const StudentInfo& y) {

	return (x.name < y.name) ;

}

std::ifstream& read (std::ifstream& in, StudentInfo& s) {
	// reads student's info into data members of the StudentInfo class
	in >> s.name >> s.midterm >> s.final ;

	read_hw(in, s.homeworks) ;	// reads homeworks into vector

	return in ;
}

std::ifstream& read_hw (std::ifstream& in, std::vector<double>& hw) {
	// reads scores into homeworks until we reach next student or EOF

	if (in) {
		hw.clear() ;	// obliterates existing values

		double x ;
		while(in >> x)
			hw.push_back(x) ;

		in.clear() ;	// clears failure state for the next one
	}

	return in ;
}

double grade (double midterm, double final, double homework) {
        // applies grading policy to compute the overall student grade

        return (0.2 * midterm + 0.4 * final + 0.4 * homework) ;

}

double grade (const StudentInfo& s) {
        // returns the overall grade of a student

        return grade(s.midterm, s.final, s.homeworks) ;

}

double grade(double midterm, double final, 
	     const std::vector<double>& hw) {
	// uses the median of the homeworks to compute the student's grade

	if (hw.size() == 0)
		throw std::domain_error(
			"the student did not turn in any homework"
		) ;

	return grade( midterm, final, stats::median(hw) ) ;
}
