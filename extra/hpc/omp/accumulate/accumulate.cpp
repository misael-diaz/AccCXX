/*
 * source: accumulate.cpp
 * author: misael-diaz
 * date:   2021/05/04
 *
 * Synopsis:
 * Demonstration program that accumulates numbers in parallel.
 * Program assumes that the work can be evenly distributed among threads.
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
#include <iomanip>
#include <numeric>
#include <omp.h>

int sum(int, int) ;
void greet(int, int) ;

const int size = 256 ;		// global total of ints

int main() {

	int workspace[4] ;	// shared placeholder for intermediate data

	#pragma omp parallel num_threads(4) shared(workspace)
	{
		int thread  = omp_get_thread_num() ;
		int threads = omp_get_num_threads() ;
		#pragma omp critical
		{
			greet(thread, threads) ; // states designation
		}
		
		// thread stores partial sum
		workspace[thread] = sum(thread, threads) ;
	}

	// obtains the running total 	/serial code/
	int total = 0 ;
	int* b = workspace ;	// defines begin and end iterators
	int* e = workspace + sizeof(workspace) / sizeof(*workspace) ;
	total = std::accumulate(b, e, total) ;

	// shows that the computation has succeeded
	std::cout << std::endl << "total: " << total << std::endl ;
	std::cout << "exact: " << (size - 1) * size / 2 << std::endl ;

	return 0 ;
}

void greet(int thread, int threads) {
	// Borg greeting, prints thread id and total number of threads

	std::cout << "hello world, my designation is " << thread << " "
		  << "of "  << threads << std::endl ;
}

int sum(int thread, int threads) {
	// accumulates integers in the (computed) asymmetric range [b, e)

	// number of integers processed by (this) thread
	const int load = size / threads ;	
	const int b = thread * load ;
	const int e = b + load ;

	int total = 0 ;
	for(int i = b ; i != e ; ++i)
		total += i ;

	return total ;
}
