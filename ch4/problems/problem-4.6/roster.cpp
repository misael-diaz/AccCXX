/*
 * source: roster.cpp
 * author: misael-diaz
 * date:   2021/03/28
 *
 * Synopsis:
 * Generates a roster file, students grades are sampled from a uniform
 * random distribution.
 *
 * References:
 * A Koenig and B Moo, Accelerated C++ Practical Programming by Example
 * www.cplusplus.com/reference/cstring/strcat/
 *
 * TODO:
 * [ ] use std::format to pad the student "id" with leading zeros 
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <random>
#include <ios>

int numDigits(int) ;
void pushNames(std::vector<std::string>& names,
               std::vector<std::string>::size_type n) ;

void write(const std::vector<std::string>& names) ;
void write(std::ostream&  out, const std::vector<std::string>& names) ;
void write(std::ofstream& out, const std::vector<std::string>& names) ;

void spawnGrades(std::vector<double>& grades,
	         std::default_random_engine& generator, 
                 std::uniform_real_distribution<double>& distribution) ;
	
using std::max ;
using std::cout ;
using std::endl ;
using std::setw ;
using std::left ;
using std::string ;
using std::vector ;
using std::ostream ;
using std::ofstream ;
using std::streamsize ;

int main() {

	ofstream roster ;
	const string filename = "students_grades.txt" ;

	const vector<string>::size_type n = 256 ; // defs num of students
	vector<string> names ;
	pushNames(names, n) ;
	
	// opens the rosters for writing
	roster.open(filename, std::ios::out);	/* truncates ofstream */
	if ( roster.is_open() ) {
		// generates the roster file verbosely
		write(cout, names) ;
		write(roster, names) ;
	} else {
		// displays I/O error upon failure
		cout << "failed to open: " << filename << endl ;
		return 1 ;
	}	

	roster.close() ;
	return 0 ;
}

void write(ofstream& out, const vector<string>& names) {
        // writes the grades of each student on output file stream
	
	string::size_type maxlen = 0;

        // chooses default prng and sets the range of the distribution
        std::default_random_engine generator ;
        std::uniform_real_distribution<double> distribution(65.0, 100.0) ;


        // finds the max string size in names vector
        for (const auto& name: names)
                maxlen = max(name.size(), maxlen) ;


        streamsize prec = out.precision(4) ;
        for (const auto& name: names) {

        	vector<double> grades ;
                // generates the midterm, final, and homework grades
                spawnGrades(grades, generator, distribution) ;
                
		// writes name on student record
		out << name << string(maxlen - name.size() + 1, ' ') ;
                
		// writes grades on student record
                streamsize osw = out.width() ;
                for(const auto& grade: grades) {
                        // left-justifies for vertical alignment
                        out << left << setw(6) << grade << " " ;
                }
                out << endl ;
                out.width(osw) ; 
                
		grades.clear() ; // clears grades vector for next student
        }
        out.precision(prec) ;	
	return ;
}

void write(ostream& out, const vector<string>& names) {
        // writes the grades of each student on output stream

        string::size_type maxlen = 0;

        // chooses default prng and sets the range of the distribution
        std::default_random_engine generator ;
        std::uniform_real_distribution<double> distribution(65.0, 98.0) ;


        // finds the max string size in names vector
        for (const auto& name: names)
                maxlen = max(name.size(), maxlen) ;

        
	streamsize prec = out.precision(4) ;
        for (const auto& name: names) {

        	vector<double> grades ;
                // generates the midterm, final, and homework grades
                spawnGrades(grades, generator, distribution) ;
		
		// writes name on student record
		out << name << string(maxlen - name.size() + 1, ' ') ;
		
		// writes grades on student record
                streamsize osw = out.width() ;
                for(const auto& grade: grades) {
                        // left-justifies for vertical alignment
                        out << left << setw(6) << grade << " " ;
                }
                out << endl ;
                out.width(osw) ;

                grades.clear() ; // clears grades vector for next student

        }
        out.precision(prec) ;
	return ;
}
void write(const vector<string>& names) {
	// writes the grades of each student on standard output 

	string::size_type maxlen = 0;
        
	// chooses default prng and sets the range of the distribution
        std::default_random_engine generator ;
        std::uniform_real_distribution<double> distribution(65.0, 98.0) ;


	// finds the max string size in names vector
	for (const auto& name: names) {
		// updates the max string size
		maxlen = max(maxlen, name.size()) ;
	}

	// sets four digits of precision on the output stream
	streamsize prec = cout.precision(4) ;
	for (const auto& name: names) {

		vector<double> grades ;
                // generates the midterm, final, and homework grades
		spawnGrades(grades, generator, distribution) ;
                
		// writes name on student record
		cout << name << string(maxlen - name.size() + 1, ' ') ;
		
		// writes grades on student record
	        streamsize osw = cout.width() ;
		for(const auto& grade: grades) {
                	// left-justifies for vertical alignment
			cout << left << setw(6) << grade << " " ;
		}
		cout << endl ;
		cout.width(osw) ;

		grades.clear() ; // clears grades vector for next student
	
	}
        cout.precision(prec) ; 
	return ;

}

void spawnGrades(std::vector<double>& grades, 
	         std::default_random_engine& generator, 
 		 std::uniform_real_distribution<double>& distribution) {


	double rand ;
        // pushes the midterm, final, and the homework grades 
        for(int i = 0; i != 8; ++i) {
		rand = distribution(generator) ;
                grades.push_back(rand) ;
        }

	return ;

}

void pushNames(vector<string>& names, vector<string>::size_type n) {
	// pushes /n/ student names to a vector of strings

	// obtains the max number of digits needed for the student "id"'s
	int ndigits = numDigits(n) ;
	char buffer[ndigits + 1] ;

	// defs a format string-literal to fill "id"'s with leading zeros
	char fstring[7] ;
	char ndigits_char[8] ;
	strcpy(fstring, "%0") ;
	sprintf(ndigits_char, "%u", ndigits) ;
	strcat(fstring, ndigits_char) ;
	strcat(fstring, "d") ;

	typedef vector<string>::size_type size;
	for (size i = 0; i != n; ++i) { /* TODO: use C++20 std::format */

		//name = "student" + std::to_string(i) ; // former
		//string id = std::format("{02d}", i) ;  // future
		
		// generates the student name: "student" + "id"
		sprintf(buffer, fstring, i) ;
		string name = "student" + string(buffer) ;
		names.push_back(name) ;

	}

	return ;
}

int numDigits(int i) {
        // obtains the number of digits using integer arithmetic

        int digits = 1 ;
        // invariant: integer /i/ has known /digits/ digits
        while (i /= 10)
                ++digits ;

        return (digits) ;
}

