/*
 * source: main_distinct.cpp
 * author: misael-diaz
 * date:   2021/04/27
 *
 * Synopsis:
 * Solves problem 3-3, counts number of distinct words read from a stream,
 * and reports the number of repetitions for each word.
 *
 * Comments:
 * Dictionary of English words was derived from another hosted in github 
 * (see references).
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 * https://github.com/dwyl/english-words
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ios>

void read(std::vector<std::string>&) ;
std::string::size_type strsz(const std::string&) ;

int main() {
	// counts instances of the same word

	// reads words into vector
	std::vector<std::string> words ;
	try {
		read(words) ;
	} catch (std::runtime_error err) {
		std::cout << err.what() << std::endl ;
		return 1 ;
	}

	std::vector<std::string::size_type> w_sizes ;
	
	// obtains the maximum string size in vector of words
	std::transform(
	    words.begin(), words.end(), std::back_inserter(w_sizes), strsz
	) ;

	std::vector<std::string::size_type>::iterator
		max = std::max_element( w_sizes.begin(), w_sizes.end() ) ;

	// counts number of repeated instances of each word
	std::map<std::string, int> map ;
	for (const auto& word: words)
		++map[word] ;

	// displays results in tabulated format
	for (const auto& x: map) {
		
		std::string word = x.first ;	int reps = x.second ;
		
		// applies padding for vertical alignment
		std::string spaces(*max - word.size() + 1, ' ') ;
		word += (":" + spaces) ;

		std::cout << word  << "\t" << reps << std::endl ;

	}

	std::cout << std::endl << "#distinct words: " << map.size()
		<< std::endl ;

	return 0 ;
}

std::string::size_type strsz(const std::string& string) {
	return string.size() ;
}

void read(std::vector<std::string>& words) {
	// reads words from "dictionary" into vector

	// opens "dictionary" for reading
	const std::string filename = "words_random.txt" ;
	std::ifstream dict ;
	dict.open(filename, std::ios::in) ;

        if ( dict.is_open() ) {

                std::string word ;
                while (dict >> word)
                	words.push_back(word) ;

        } else {
		throw std::runtime_error("I/O Error: " + filename) ;
        }

	dict.close() ;

	return ;
}

