/*
 * source: prompt.cpp
 * author: misael-diaz
 * date:   2021/04/28
 *
 * Synopsis:
 * Defines a basic prompt using template classes.
 *
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 * https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
 *
 */


#include <iostream>
#include <string>
#include <limits>

void ignore_garbage(std::istream& in) {
        // ignores whatever could not be extracted including the newline
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
}

std::istream& padding(std::istream& in, const std::string& msg, int& pad) {
	// prompts user for padding until the input passes validation

        while (in) {
                // prompts user until we get a valid input or EOF
                std::cout << msg ;
                in >> pad ;
		
                // handles invalid input, overflow, and out-of-range
                if ( (in.fail() && !in.eof()) || (pad < 0 || pad > 24) ) {
                        in.clear() ;
                        ignore_garbage(in) ;
                } else {
                        ignore_garbage(in) ;
                        break ;
                }

        }

	return in ;

}

template <class T>
std::istream& prompt(std::istream& in, const std::string& msg, T& value) {
        // Prompts user for value until input extraction succeeds
        // and returns the input stream to the caller, which is
        // (presumably) in a better position to deal with an
        // end-of-file (EOF) signal issued by the user.

        while (in) {
                // prompts user until we get a valid input or EOF
                std::cout << msg ;
                in >> value ;
		
                // handles invalid input from user including overflow
                if ( in.fail() && !in.eof() ) {
                        in.clear() ;
                        ignore_garbage(in) ;
                } else {
                        ignore_garbage(in) ;
                        break ;
                }

        }

        return in ;
}
