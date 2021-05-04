/*
 * source: hello-world.cpp
 * author: misael-diaz
 * date:   2021/05/04
 *
 * Synopsis:
 * OMP Hello World Program. Prints a Borg-style greeting.
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
 * [0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example
 * [1] gcc.gnu.org/onlinedocs/libgomp/
 * [2] (helloacm.com/simple-tutorial-with-openmp-how-to-use-
 *      parallel-block-in-cc-using-openmp/)
 *
 */

#include <iostream>
#include <omp.h>

void greet(int, int) ;

int main() {

	#pragma omp parallel num_threads(4)
	{
		int thread  = omp_get_thread_num() ;
		int threads = omp_get_num_threads() ;
		#pragma omp critical
		{
			greet(thread, threads) ;
		}
	}

	return 0 ;
}

void greet(int thread, int threads) {
	// Borg greeting, prints thread id and total number of threads

	std::cout << "hello world, my designation is " << thread << " "
		  << "of "  << threads << std::endl ;
}
