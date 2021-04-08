// author: Misael Diaz-Maldonado          March 30, 2021
// Synopsis:
// Defines the generic function median which operates on vectors, and other
// containers, of arithmetic-supporting types (int, float, etc.).
//
// Revisions:
// [1] adds container-oblivious implementation of the median. April 8, 2021

#include <stdexcept>
#include <vector>

template <class T>
T median(std::vector<T> vector) { /* vector passed by value */
	// computes the median of given vector
	
	const typename std::vector<T>::size_type size = vector.size() ;
	const typename std::vector<T>::size_type mid = size / 2 ;
	
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

template <class In, class T>
T median(In begin, In end, T dummy) {
        // Computes median of object delimited by the range [begin, end).
	// The median function shouldn't change the contents of the
	// container this is why the function expects input iterators.

	// Note:
	// I do not know if there's a better way to write a
	// container-oblivious implementation of the median function
	// without passing the dummy argument. As it is defined,
	// the compiler can deduce the type of the data pointed to by the
	// iterators from the type of the dummy argument.

	std::vector<T> vector(begin, end) ; /* copies into vector */
        const typename std::vector<T>::size_type size = vector.size() ;
        const typename std::vector<T>::size_type mid = size / 2 ;

        // finds the median of vector
        if (size == 0) {
                throw std::domain_error("cannot compute the median "
                                "of an empty vector") ;
        }

        // sorts vector and finds the middle value
        std::sort(vector.begin(), vector.end()) ;

        return (size % 2) == 0 ? (vector[mid] + vector[mid - 1])/2 :
                vector[mid] ;
}

