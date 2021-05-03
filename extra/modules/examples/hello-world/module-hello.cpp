/*
 * source: module-hello.cpp
 * author: misael-diaz
 * date:   2021/05/03
 *
 * Synopsis:
 * Defines module Hello, based on the referenced tutorial.
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
 * https://accu.org/journals/overload/28/159/sidwell/
 *
 */

module ;

#include <iostream>
export module Hello ;

export void greet() { 
	std::cout << "hello, world!" << std::endl ; 
}
