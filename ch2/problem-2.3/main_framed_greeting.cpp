/* 
 * source: main_framed_greeting.cpp
 * author: misael-diaz
 * date:   2021/03/26
 *
 *
 * Synopsis:
 * Solves problem 2-3, produces a framed greeting. Program asks the user
 * to set the padding used for separating the greeting from the frame.
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
 * Revisions:
 * 2021/04/29	implements a basic prompt with template classes
 *
 */

#include <iostream>
#include <string>
#include "prompt.h"

std::istream& padding(std::istream&, int&) ;
void print(const std::string&, const int&) ;

int main() {

	// asks user for the padding to be applied to the framed greeting
	int pad ;
	std::string msg = "Please enter the padding for the "
	       "framed message: "	;
	
	// if prompt succeeds, ask for an username
	if ( prompt(std::cin, msg, pad) ) {
		
		std::string msg = "Please also enter your username: " ;
		std::string name ;

		// if prompt succeeds, print the framed greeting
		if ( prompt(std::cin, msg, name) ) 
			print(name, pad) ;
	}

	return 0 ;
}

void print(const std::string& name, const int& pad) {
	// prints the framed greeting with the requested padding

	// constructs the padding for the row where the greeting is shown
        std::string padding(pad, ' ') ;
        // initializes the greeting message
        std::string greeting = padding + "Hello, " + name + "!" + padding ;
        // constructs the spaces used elsewhere 
        std::string spaces(greeting.size(), ' ') ;
        // constructs the border (used for the top and bottom of the frame)
        std::string frame(greeting.size() + 2, '*') ;

        // displays framed greeting
        std::cout << frame << std::endl ;       // top border
        for (int i = 0 ; i != pad ; ++i)        // spaces
                std::cout << "*" + spaces   + "*" << std::endl ;

        std::cout << "*" + greeting + "*" << std::endl ;

        for (int i = 0 ; i != pad ; ++i)        // spaces
                std::cout << "*" + spaces   + "*" << std::endl ;
        std::cout << frame << std::endl ;       // bottom border

	return ;
}

