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
 * [3] (software.intel.com/content/www/us/en/develop/articles/
 *      avoiding-and-identifying-false-sharing-among-threads.html)
 * [4] stackoverflow.com/questions/4802565/multiple-threads-and-cpu-cache
 * [5] en.cppreference.com/w/cpp/language/alignof
 *
 * Notes:
 * Caf's reply to inquiry in stackoverflow (ref 4) was instructive,
 * especially the comments on memory alignment. The alignof operator (since
 * c++11) can be used to find the alignment for any type (ref 5).
 *
 * Revisions:
 * 2021/05/06		pads shared placeholder to mitigate false sharing
 *
 */

#include <iostream>
#include <iomanip>
#include <numeric>
#include <omp.h>

const int pad = 128 ;
const int n_threads = 4 ;
const int numel = pad * n_threads ;

int sum(int, int) ;
void greet(int, int) ;
void greet(int, int, int) ;
void zeros(int array[numel]) ;

const int size = 256 ;		// global total of ints

int main() {

	// shared placeholder for intermediate data
	int workspace[numel] ;	zeros(workspace) ;
	/*      verifies that /workspace/ has a 4-byte alignment       */
	//std::cout << "alignment: " << alignof(workspace) << std::endl ;

	#pragma omp parallel num_threads(4) shared(workspace)
	{
		int thread  = omp_get_thread_num() ;
		int threads = omp_get_num_threads() ;

		// thread stores partial sum
		workspace[pad * thread] = sum(thread, threads) ;
		#pragma omp critical
		{
			// states designation and intermediate result
			greet(thread, threads, workspace[pad * thread]) ;
		}
		
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

void zeros(int array[numel]) {
	// fills array with zeros
	for (int i = 0 ; i != numel ; ++i)
		array[i] = 0 ;
}

void greet(int thread, int threads) {
	// Borg greeting, prints thread id and total number of threads

	std::cout << "hello world, my designation is " << thread << " "
		  << "of "  << threads << std::endl ;
}

void greet(int thread, int threads, int sum) {
        // Borg greeting, prints thread id and total number of threads

        std::cout << "hello world, my designation is " << thread << " "
                  << "of "  << threads << " and my sum yields "
		  << sum << std::endl ;
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
