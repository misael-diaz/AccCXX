/*
 * source: nested.cpp
 * author: misael-diaz
 * date:   2021/05/05
 *
 * Synopsis:
 * Demonstration program that parallelizes nested loops.
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
 * Notes:
 * When the nested loop has more iterations than the outer loop,
 * as in this demo, it's preferable to swap the loops (if possible)
 * followed by parallelization of the outer (former nested) loop.
 * Note that there are OpenMP directives available to solve this
 * problem with ease.
 *
 * This demo shows a possible solution when swapping is not "doable",
 * and when the programmer decides not to use the OpenMP directives.
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

int& loop(const int&, const int&, int&) ;	// outer-loop
int& nest(const int&, const int&, int&) ;	// nested-loop

void greet(int, int) ;
void greet(int, int, int) ;

/* global constants */
const int n_threads = 16 ;		// number of threads
const int loop_size = 2 ;		// outer-loop size
const int nest_size = 256 ;		// nested-loop size
const int size = loop_size * nest_size ;// total
 
int main() {

	// shared placeholder for intermediate data
	int workspace[n_threads] ;	

	#pragma omp parallel num_threads(n_threads) shared(workspace)
	{
		int thread  = omp_get_thread_num() ;
		int threads = omp_get_num_threads() ;

		int count = 0 ;
		workspace[thread] = loop(thread, threads, count) ;

		#pragma omp critical
		{
			// states designation and intermediate result
			greet(thread, threads, workspace[thread]) ;
		}
		
	}

	// obtains the running total 	/serial code/
	int total = 0 ;
	int* b = workspace ;
	int* e = workspace + sizeof(workspace) / sizeof(*workspace) ;
	total = std::accumulate(b, e, total) ;

	// shows that parallelization has succeeded (even distribution)
	std::cout << "total: " << total << std::endl ;
	std::cout << "exact: " << size  << std::endl ;

	return 0 ;
}

void greet(int thread, int threads) {
	// prints designation (Borg-style) and partial sum

	std::string greeting = "hello world, my designation is " ;

	// stores the ostream width and defines the maximum
	std::streamsize m = std::to_string(threads).size() ;
	std::streamsize w = std::cout.width() ;
	std::cout << greeting << std::setw(m) << std::right << thread
	          << " of "   << std::setw(m) << std::right << threads
		  << std::endl ;
	std::cout.width(w) ;
}

void greet(int thread, int threads, int sum) {
        // Borg greeting, prints thread id and total number of threads

	std::string greeting = "hello world, my designation is " ;

	std::streamsize m = std::to_string(threads).size() ;
	std::streamsize w = std::cout.width() ;
	std::cout << greeting << std::setw(m) << std::right << thread
	          << " of "   << std::setw(m) << std::right << threads
                  << " and my sum yields " << sum << std::endl ;
	std::cout.width(w) ;
}


int& loop(const int& thread, const int& threads, int& count) {
	// executes nested loop (effectively unrolls this loop)

	// distributes evenly
	const int load = size / threads ;	
	// defines the (global) asymmetric range to be processed by thread
	int b = thread * load ;
	int e = b + load ;

	// maps (global) range to that of the nested loop: [b, e)
	b =  b % nest_size ;
	e = (e % nest_size == 0)? nest_size: (e % nest_size) ;
 
	return nest(b, e, count) ;

}

int& nest(const int& b, const int& e, int& count) {
        // performs computations /.../ and increments counter by (e - b)

        for(int i = b ; i != e ; ++i) {
		/* ... */
                ++count ;
	}

        return count ;
}

