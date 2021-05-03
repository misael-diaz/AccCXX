/*
 * source: main.cpp
 * author: misael-diaz
 * date:   2021/04/27
 *
 * Synopsis:
 * Solves problem 3-5, computes the final grades of the students by
 * processing a roster file.
 *
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <string>
#include <ios>

void grade(
	std::ifstream&, std::vector<std::string>&, std::vector<double>&
) ;
std::ifstream& name(std::ifstream&, std::string&) ;
std::ifstream& grade(std::ifstream&, double&) ;

int main() {

	// opens the roster file for input
	std::string filename = "roster.txt" ;
	std::ifstream roster ;
	roster.open(filename, std::ios::in) ;

	std::vector<std::string> names ;
	std::vector<double> grades ;

	if (roster.is_open()) {
		// processes roster file for grading

		try {
			// grades students
			grade(roster, names, grades) ;
		} catch (std::runtime_error err) {
			std::cout << err.what() << std::endl ;
			return 1 ;
		}

	} else {
		std::cout << "Input/Output error with Roster: " 
			<< filename << std::endl ;
		return 1 ;
	}

	double sum = 0. ;
	sum = std::accumulate(grades.begin(), grades.end(), sum) ;
	if (grades.size() != 0) {
		// reports the average grade of the whole class
		std::streamsize prec = std::cout.precision() ;
		std::cout << "class average grade: "
			<< std::setprecision(4) << sum / grades.size() 
			<< std::setprecision(prec) << std::endl ;
	}

	roster.close() ;

	return 0 ;
}

void grade(std::ifstream& roster, 
	   std::vector<std::string>& names, 
	   std::vector<double>& grades) {
	// obtains the final grades for all students
                
	std::string nm ;	// student name
	double final ;		// student final grade
	while ( name(roster, nm) && grade(roster, final) ) {
		// pushes the students' data to corresponding vectors
		names.push_back(nm) ;
		grades.push_back(final) ;
	}

	return ;
}
	
std::ifstream& name(std::ifstream& in, std::string& nm) {
	// reads the student name (if any), caller handles EOF instance
	in >> nm ;
	return in ;
}

std::ifstream& grade(std::ifstream& in, double& final) {
	// Synopsis:
	// Computes the final grade of a student.
	//
	// inputs:
	//
	// in           input file stream, roster
	// final        undefined on entry
	//
	// outputs:
	//
	// in           input file stream, roster
	// final        final grade of student on exit

	// double-checks the state of the input file stream
	if (in) {

		// reads the scores of the midterm and final tests
		double midterm ;
		in >> midterm >> final ;

		double hw ;
		int count = 0 ;
		double sum = 0 ;
		while (in >> hw) {	// accumulates homework scores
			sum += hw ;
			++count ;
		}

		if (count == 0) {
			// checks that the student has done homework
                	throw std::runtime_error(
                        	"incompatible roster file, verify that "
				"the file has enough fields for the "
				"midterm, final, and homework scores."
                	) ;
		}

		// computes the final course score of the student
		final = (0.2 * midterm + 0.4 * final + 0.4 * sum / count) ;
		in.clear() ;	// clears the stream for the next student

	}

	return in ;

}
