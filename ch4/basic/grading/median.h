#ifndef GUARD_MEDIAN_H
#define GUARD_MEDIAN_H

// author: Misael Diaz-Maldonado          March 30, 2021
// Synopsis:
// Defines the the generic function median which operates on vectors
// of arithmetic-supporting types (int, float, etc.). 

#include <vector>
template <class T>
T median(std::vector<T>) ;
template <class In, class T>
T median(In, In, T) ;
#include "median.cpp"
#endif
