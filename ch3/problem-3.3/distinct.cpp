/* 
 * Synopsis:
 * Solves part of problem 3-3, counts the number of distinct elements of
 * a vector of strings.
 *
 * Reference:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
 * Author: Misael Diaz-Maldonado             March 28, 2021
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
int main(){
	// program obtains the number of distinct elements in vector

	// defines abbreviation for the string type
	typedef std::string str ;
	// defines abbreviation for the size_type of a vector
	typedef std::vector<str>::size_type size ;
	
	// defines the vector size of eight, by design all vectors in this
	// program have the same number of elements
	const size n = 8 ;

	// creates and initializes a vector of zeros of size n
	std::vector<int> zeros(n, 0) ; // constructor-type initialization
	// creates an vector ranging from 0 to 8 (non-inclusive)
	std::vector<int> range{0, 1, 2, 3, 4, 5, 6, 7} ;
	// defines a vector having repeated values
	std::vector<int> repls{0, 0, 0, 1, 1, 2, 3, 4} ;
	// defines a vector of strings
	std::vector<str> strgs{"mom", "dad", 
		"sister", "brother", "grandfather", "grandmother",
		"uncle", "aunt"} ;


	// defines vector for code testing
	std::vector<str> vector ;
	//vector = range ; 
	//vector = repls ;
	vector = strgs ;

        // displays the (unsorted) elements of the vector
	std::cout << "unsorted vector: " << std::endl ;
        for (size i = 0; i != n ; ++i)
                std::cout << vector[i] << ' ' ;
        std::cout << std::endl ;

	// sorts the vector
	std::sort(vector.begin(), vector.end()) ;

	// displays the elements of the vector in nondescending order
	std::cout << "sorted vector: " << std::endl ;
        for (size i = 0; i != n ; ++i)
                std::cout << vector[i] << ' ' ;
        std::cout << std::endl ;

	// obtains the number of distinct elements in vector
	size i = 0 ;
	size count = 0 ;
	size duplicates ;
	// loop invariant: 
	//     we have counted [i] elements of the vector and
	//     have found [count] distinct elements so far
	while (i != n) {
		duplicates = 0;
		// loop invariant: 
		// we have counted [duplicates] duplicates of the 
		// ith (or [i]) element of vector so far
		for (size j = i + 1; j != n; ++j) {
			if (vector[i] == vector[j])
				++duplicates ;
			else
				break ;
		}
		++i += duplicates ;
		++count ;
	}

	// displays number of distinct elements in vector
	std::cout << "#distinct elements: " << count << std::endl ;
	return 0 ;
}
