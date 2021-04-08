// author: Misael Diaz-Maldonado          March 30, 2021
// Synopsis:
// Defines the the generic function median which operates on vectors
// of arithmetic-supporting types (int, float, etc.). 

#include <stdexcept>
#include <vector>

template <class T>
T median(std::vector<T> vector) {
	// computes the median of given vector (passed by value)
	
	typedef typename std::vector<T>::size_type vecSize ;
	const vecSize size = vector.size() ; 
	const vecSize mid = size / 2 ;
	
	// finds the median of given vector
	if (size == 0) {
		throw std::domain_error("cannot compute the median "
				"of an empty vector") ;
	}

	// sorts vector and finds the middle value
	std::sort(vector.begin(), vector.end()) ;

	return (size % 2) == 0 ? (vector[mid] + vector[mid - 1])/2 : 
		vector[mid] ;
}

