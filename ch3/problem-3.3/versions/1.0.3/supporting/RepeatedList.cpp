/*
 * source: RepeatedList.cpp
 * author: misael-diaz
 * date:   2021/04/27
 *
 * Synopsis:
 * Supporting program that generates a list/dictionary of repeated words.
 *
 * Comments:
 * Dictionary of English words was downloaded from github (see references).
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
#include <random>
#include <ios>

void read(std::vector<std::string>&) ;
void write(const std::vector<std::string>&) ;

int main() {
	// produces a dictionary of repeated words

	// reads words into vector
	std::vector<std::string> words ;
	for(int reads = 0 ; reads != 256 ; ++reads) {
		try {
			read(words) ;
		} catch (std::runtime_error err) {
			std::cout << err.what() << std::endl ;
			return 1 ;
		}
	}
	std::cout << "vector size: " << words.size() << std::endl ;

	// writes (sorted) words to dictionary
	std::sort(words.begin(), words.end()) ;
	try {
		write(words) ;
	} catch (std::runtime_error err) {
                        std::cout << err.what() << std::endl ;
                        return 1 ;
	}

	return 0 ;
}

void read(std::vector<std::string>& words) {
	// randomly reads words from "dictionary"

	std::random_device randev ; 
        std::default_random_engine generator( randev() ) ;
        std::uniform_int_distribution<int> distribution(1024, 2048) ;

	// opens "dictionary" for reading
	const std::string filename = "words_alpha.txt" ;
	std::ifstream dict ;
	dict.open(filename, std::ios::in) ;

        if ( dict.is_open() ) {

                int count = 0 ;	// line counter
		int urand = distribution(generator) ;
                std::string word ;
                while (dict >> word) {
			// pushes a word to vector every [urand] lines
                        if (count % urand == 0) {
                                words.push_back(word) ;
				urand = distribution(generator) ;
                        }
                        ++count ;
                }

        } else {
		throw std::runtime_error("I/O Error: " + filename) ;
        }

	dict.close() ;

	return ;
}

void write(const std::vector<std::string>& words) {
	// writes words vector to "dictionary"

        // opens "dictionary" for writing
        const std::string filename = "words_random.txt" ;
        std::ofstream dict ;
	dict.open(filename, std::ios::out) ;

	if ( dict.is_open() ) {
		for (auto& word: words)
			dict << word << std::endl ;
	} else {
		throw std::runtime_error("I/O Error: " + filename) ;
	}

	dict.close() ;
	return ;
}
