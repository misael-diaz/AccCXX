/*
 * source: main.cpp
 * author: misael-diaz
 * date:   2021/05/10
 *
 * Synopsis:
 * Solves problem 4-6, program uses a minimalistic student info class whose
 * sole data members are the student name and final grade.
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
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <ios>

import student_info ;	// imports the StudentInfo struct and related funs

std::string::size_type
push (std::string::size_type, const StudentInfo&, 
      std::vector<StudentInfo>&) ;

void report (std::string::size_type, std::string, double) ;


using std::max ;
using std::cout ;
using std::endl ;
using std::setw ;
using std::left ;
using std::sort ;
using std::vector ;
using std::string ;
using std::streamsize ;
using std::setprecision ;

int main() {

	vector<StudentInfo> students ;

	std::ifstream roster ;
	string filename = "students_grades.txt" ;
	roster.open(filename, std::ios::in) ;

	string::size_type maxlen = 0 ; // max #chars in students.names
	if ( roster.is_open() ) {

		try {
			StudentInfo record ;
			// reads student records into vector
			while ( read(roster, record) ) 
				maxlen = push(maxlen, record, students) ;

		} catch (std::domain_error err) {
			cout << err.what() << endl ;
			return 1 ;
		}

	} else {
		cout << "I/O Error: " << filename << endl ;
		return 1 ;
	}

	roster.close() ;
	
	// reports the final grade for each student alphabetically
	sort(students.begin(), students.end(), compare) ;
	for (const auto& student: students)
		report(maxlen, student.name, student.final) ;

	return 0 ;

}

std::string::size_type
push (std::string::size_type maxlen, const StudentInfo& record,
      std::vector<StudentInfo>& students) {
	// pushes a record onto the back of vector, and returns
	// the maximum string length of students.name as a side-effect
				
	students.push_back(record) ;
	return max(record.name.size(), maxlen) ;
}

void report(string::size_type maxlen, string nm, double final) {
	/* reports the student's name and final grade on the ostream */

	// finds padding for vertical alignment
        string::size_type nspaces = maxlen - nm.size() + 4 ;
        nm += string(nspaces, ' ') ;


	streamsize osw = cout.width() ;
        streamsize prec = cout.precision() ;

        cout << nm << setw(4) << left << setprecision(4) << final << endl ;

        cout.width(osw) ;
        cout.precision(prec) ;
	return ;
}
