/* 
 * source: main_linked_list.cpp
 * author: misael-diaz
 * date:   April 18, 2021
 *
 * Synopsis:
 * My initial (yet rudimentary) implementation of a singly linked-list.
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * References:
 * A Koenig and B Moo, Accelerated C++ Practical Programming by Example
 * 
 * References from the web:
 * https://www.codesdope.com/blog/article/\
 * inserting-a-new-node-to-a-linked-list-in-c/
 *
 * Note: 
 * There were many other web references but that's the main source
 * used for inspiration to write this code. 
 * 
 * Study:
 * Geeks-for-Geeks has a lot of example codes for implementing
 * linked-lists in C/C++ and possibly other languages. Invest
 * some time in studying them.
 *
 * TODO:
 * [x] partition code
 * [ ] extend code:	
 *
 * 			[x] insert at the front 
 * 			[ ] insert at position
 * 			[ ] insertion sort 
 * 			[ ] doubly linked-lists
 *
 * Revisions:
 * April 19, 2021	adds empty, create, display, insert_front,
 * 			and uncreate (iterator variant) functions
 *
 */

#include <iostream>
#include "LinkedList.h"

int main() {
	// creates and populates a singly linked-list
	
	node* head ;
	node* tail ;
	/* pack and unpack "containers" */
	node* ptrs[] = {head, tail} ;
	node** ret ;

	// creates an empty linked-list
	ret = empty(ptrs) ;
	head = ret[0] ;	tail = ret[1] ;

	// creates a linked-list with a single node
	ret = create(ptrs, 0) ;
	head = ret[0] ;	tail = ret[1] ;

	for(int i = 1; i != 16; ++i)
		// insert values at the back of list
		//tail = insert_back(tail, i) ;
		head = insert_front(head, tail, i) ;

	// displays elements of list
	display(head) ;

	// report the size of the list
	std::cout << "size: " << size(head) << std::endl ;
	// frees allocated memory
	uncreate(head, tail) ;

	return 0 ;
}

