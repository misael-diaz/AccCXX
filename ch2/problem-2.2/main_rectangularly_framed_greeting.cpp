/* 
 * source: main_rectangularly_framed_greeting.cpp
 * author: misael-diaz
 * date:   2021/03/29
 *
 *
 * Synopsis:
 * Solves problem 2-2, produces a framed greeting of rectangular shape.
 * The user can request different paddings in the the horizontal and 
 * vertical directions.
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
#include "prompt.h"

std::string& trim(std::string&) ;
void print(const std::string&, const int&, const int&) ;

int main() {

	// horizontal and vertical padding, respectively
	int hpad ;
	int vpad ;
	// horizontal and vertical directions, respectively
	std::string hdir = "horizontal" ;
	std::string vdir = "vertical" ;

	/* prompts for the horizontal padding of the framed greeting */
	std::string msg = "Please enter the " + hdir + " padding "
		"for the framed message: " ;
	
	if ( padding(std::cin, msg, hpad) ) {
		
		/* prompts for the vertical padding */
		std::string msg = "Please enter the " + vdir + " padding "
			"for the framed message: " ;
		if ( padding(std::cin, msg, vpad) ) {
			
			/* prompts for the username */
			std::string msg = "Please also enter your "
			"username (up to 16 non-whitespace characters): " ;
			std::string name ;

			// if prompt succeeds, prints the framed greeting
			if ( prompt(std::cin, msg, name) )
				print(trim(name), hpad, vpad) ;
	
		}

	}

	return 0 ;
}

std::string& trim(std::string& name) {
	// trims username to a maximum of 16 characters.
	if (name.size() > 16) {
		std::string trimmed = name.substr(0, 16) ;
		name = trimmed ;
	}
	return name ;
}

void print(const std::string& name, const int& hpad, const int& vpad) {
	// prints the framed greeting with the requested padding

	// constructs the padding for the row where the greeting is shown
        std::string padding(hpad, ' ') ;
        // initializes the greeting message
        std::string greeting = padding + "Hello, " + name + "!" + padding ;
        // constructs the spaces used elsewhere 
        std::string spaces(greeting.size(), ' ') ;
        // constructs the border (used for the top and bottom of the frame)
        std::string frame(greeting.size() + 2, '*') ;


        // displays framed greeting
        std::cout << frame << std::endl ;	// top border
        for (int i = 0 ; i != vpad ; ++i)	// spaces
                std::cout << "*" + spaces + "*" << std::endl ;

        std::cout << "*" + greeting + "*" << std::endl ;

        for (int i = 0 ; i != vpad ; ++i)	// spaces
                std::cout << "*" + spaces + "*" << std::endl ;
        std::cout << frame << std::endl ;	// bottom border

	return ;
}

