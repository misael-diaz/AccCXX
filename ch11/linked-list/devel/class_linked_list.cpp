/* 
 * source: class_linked_list.cpp
 * author: misael-diaz
 * date:   April 20, 2021
 *
 * Synopsis:
 * My initial implementation of a singly linked-list class.
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
 * 			[x] define _avail and _limit
 * 			[x] end() must return _avail
 * 			[x] define begin(), end(), and size() members
 * 			[x] copy constructor
 * 			[x] assignment operator
 * 			[x] add support for growing
 * 			[x] push back
 * 			[ ] insert at the front
 * 			[ ] insert at position
 * 			[ ] insertion sort 
 * 			[ ] doubly linked-lists
 *
 * Revisions:
 * TO ADD
 *
 */

#include <iostream>
#include "LinkedList.h"

class LinkedList {
	public:
		/* interface */

		// typedefs
		typedef node* iter ;
		typedef const node* const_iter ;

		// constructors
		LinkedList() { create() ; }
		explicit LinkedList(const int& value) { create(value) ; }
		explicit LinkedList(const size_t& n, const int& value) {
			create(n, value) ;
		}
		LinkedList(const LinkedList& ls) { /* copy constructor */
			create(ls.begin(), ls.end()) ; 
		}
		~LinkedList() { destroyer() ; }

		// operators
		LinkedList& operator=(const LinkedList&) ;

		// iterator
		iter begin() { return _beg ; }
		const_iter begin() const { return _beg ; }
		iter end() { return _end ; }
		const_iter end() const { return _avail ; }

		// size
		size_t size() const { return _avail - _beg ; }
		size_t numel() ;

		// insert
		void push_back(const int& value) { insert_back(value) ; }

		// output
		void display() ;
	private:
		/* implementation */
		node* _beg ;		// beginning
		node* _end ;		// one past last element
		node* head ;		// beginning
		node* tail ;		// last element
		node* _avail ;
		node* _limit ;
		bool preallocated ;	// true for lists using new[size]

		// memory allocation
		void create() ;
		void create(const int&) ;
		void create(const size_t&, const int&) ;
		void create(const_iter, const_iter) ;
		void create_works(const size_t&, const int&) ;	//TO REMOVE

		// insert
		iter* copy(const_iter, const_iter, iter ptr[2]) ;
		void grow() ;
		void insert_avail(const int&) ;
		void uninitialized_insert(const int&) ;
		void insert_back(const int&) ;

		// destructor, memory deallocation
		void destroyer() ;
		void destroy() ;
		void undo() ;
		void uncreate() ;
		void deallocate() ;
} ;

int main() {
	// creates and populates singly linked-lists

	LinkedList list(8, 255) ;
	std::cout << "original: " << std::endl ;
	list.display() ;
	std::cout << "size: " << list.numel() << "\t" << "size: "
	       << list.size() << std::endl ;

	// invokes copy constructor
	//LinkedList copy = list ;
	// invokes assignment operator
	//copy = list ;
	// inserts
	LinkedList copy ;	/* *CRASHES* */
	copy.push_back(0) ;
	copy.push_back(0) ;
	copy.push_back(0) ;
	copy.push_back(0) ;
	copy.push_back(0) ;
	std::cout << "copy: " << std::endl ;
	copy.display() ;
	std::cout << "size: " << copy.numel() << "\t" << "size: "
	       << copy.size() << std::endl ;

	return 0 ;
}

//iter& iter&::operator=(const iter& iterator) {
//	// defines the assignment operator for the linked-list iterator
//
//	if (&iterator != this) {
//		it = iterator.it ;
//	}
//
//	return *this ;
//}

void LinkedList::create() {
	// creates an empty linked-list object
	tail = head = _avail = _limit = _end = _beg = NULL ;
	preallocated = false ;
}

void LinkedList::create(const int& value) {
	// creates a linked-list object having a single value

	tail  = head  = _beg = new node ;
	_avail = _limit = _end = _beg + 1 ;
	// assigns value to node and nullifies the linked-list
        tail -> data = value ;
        tail -> next = NULL ;
	
	preallocated = false ;

	return ;
}

void LinkedList::create(const size_t& n, const int& value) {
	// creates a linked-list having multiple copies of the same value
        _beg = new node[n] ;
	_end = _avail = _limit = _beg + n ;
	tail = head = _beg ;

        iter it = head ;
        iter last = _beg + (n - 1) ;	// marks placement of tail
        while (it != last) {
                // populates list in the range [head, tail)
		tail = it ;
                tail -> data = value ;
                tail -> next = ++it ;
        }
	// defines tail and nullifies the linked-list
	tail = it ;
        tail -> data = value ;
        tail -> next = NULL ;

        preallocated = true ;
	return ;
}

void LinkedList::create(const_iter b, const_iter e) {
	// copy constructor proxy
	// creates a linked-list from the values stored in another

	// allocates memory for copying into
	size_t sz = e - b ;
	_beg = new node[sz] ;
	_end = _avail = _limit = _beg + sz ;

	tail = head = _beg ;
	const_iter it   = b ;
	const_iter last = --e ;
	while(it != last) {
		// copies data in the range [head, tail) from original
		tail -> data = it -> data ;
		tail -> next = (tail + 1) ;	// linking
		tail += 1 ;	it++ ;
	}
	// copies last data into tail and nullifies the linked-list
	tail -> data = it -> data ;
	tail -> next = NULL ;

	preallocated = true ;
	return ;
}

void LinkedList::create_works(const size_t& n, const int& value) {
	// creates a linked-list having multiple copies of the same value

	head = new node[n] ;
	iter last = head + (n - 1) ;

	tail = head ;
	while (tail != last) {
		// populates list with values while linking them
		tail -> data = value ;
		tail -> next = (1 + tail) ;
		tail += 1 ;
	}
	tail -> data = value ;
	tail -> next = NULL ;
	
	preallocated = true ;

	return ;
}

void LinkedList::destroyer() {
	// destroys linked-list objects

	if (head != NULL) {
		if (preallocated)
			deallocate() ;	// deallocates preallocated list
		else
			destroy() ;	// destroys dynamic list
	}

	return  ;
}

void LinkedList::deallocate() {
	// destroys preallocated (constant-size) linked-lists
	delete [] _beg ;
	tail = head = _end = _beg = NULL ;
}


void LinkedList::destroy() {
	// destroys dynamic (variable-size) linked-lists
	
	if (head -> next != NULL)
        	// destroys list having two or more elements
                uncreate() ;
        else
        	// destroys list having a single element
           	undo() ;
}

void LinkedList::undo() {
	// destroys list having a single element
	delete tail ; 
	tail = head = _end = _beg = NULL ;

}

void LinkedList::uncreate() {
        // frees memory allocated from back to front

        iter it ;
        while(head -> next != tail) {
                it = head ;
                while(it -> next != tail)
                        it = it -> next ;
                delete tail ;   tail = NULL ;
                tail = it ;
        }

        // deletes remaining pair
        delete tail ;   tail = NULL ; 	_end = NULL ;
        delete head ;   head = NULL ;	_beg = NULL ;

        return  ;
}

size_t LinkedList::numel() {
	// obtains the size (number of elements) of the linked-list
	
	iter it = head ;
	size_t n = 0 ;
        while(it != NULL) {
                it = it -> next ;
                ++n ;
        }
	return n ;
}

void LinkedList::display() {
        // displays elements of linked-list to standard output

        iter it = head ;
        while(it != NULL) {
                std::cout << it -> data << std::endl ;
                it = it -> next ;
        }

        return ;
}

LinkedList::iter* LinkedList::copy(const_iter ls_beg, const_iter ls_end,
		                   iter ptr[2]) {
	// copies values of original linked-list in the range [beg, end)
	// into destination and returns head and tail.

	// unpacks destination head and tail, respectively
	iter h = ptr[0] ;
	iter t = ptr[1] ;

	// original head and tail
	const size_t sz = ls_end - ls_beg ;
	const_iter last = ls_beg + (sz - 1) ;
	
	const_iter it = ls_beg ;
	while (it != last) {
                // copies data in the range [head, tail) from original
                t -> data = it -> data ;
                t -> next = (t + 1) ;
                t += 1 ;     it++ ;
        }
        // copies last data element and nullifies the destination
        t -> data = it -> data ;
        t -> next = NULL ;
	
	// packs and returns head and tail
	ptr[0] = h ;	ptr[1] = t ;
	return ptr ;

}

void LinkedList::grow() {
	// doubles the allocated space, accounts for an empty linked-list
	size_t new_size = std::max(2 * (_end - _beg), ptrdiff_t(1) ) ;

	// allocates memory for new data and creates new pointers
	iter new_beg   = new node[new_size] ;
	iter new_end   = new_beg + new_size ;
	iter new_head  = new_beg ;
	iter new_tail  = new_beg ;
	iter new_avail = NULL ;		/* to be determined */

	// if not empty, copy existing values and free allocated memory
	if (head != NULL) {
		iter  ptr[] = {new_head, new_tail} ;
		// copies existing values into list
		iter* ret = copy(_beg, _end, ptr) ;
		new_head = ret[0] ;	new_tail = ret[1] ;
		new_avail = new_tail + 1 ;	/* sets avail */
		deallocate() ;		// frees allocated memory
	} else {
		// accounts for empty (unallocated) linked-lists
		new_avail = new_tail ;		/* sets avail*/
	}

	// resets pointers
	head = new_head ;
	tail = new_tail ;
	_beg   = new_beg ;
	_avail = new_avail ;
	_limit = _end = new_end ;

	preallocated = true ;

}

void LinkedList::uninitialized_insert(const int& value) {
	// inserts in an "uninitialized" list at the head = tail = begin
	// applies to lists having no existing values

	tail -> data = value ;
        tail -> next = NULL ;
        _avail = _limit ;

	return ;
}

void LinkedList::insert_avail(const int& value) {
 	// inserts at the available position ---
	// applies to lists having at least one value

	tail -> next = _avail++ ;
        tail = tail -> next ;
        tail -> data = value ;
        tail -> next = NULL ;

	return ;
}

void LinkedList::insert_back(const int& value) {
	// inserts values at the back of the linked-list

	if (_avail == _limit) {
		// grows in size as needed
		grow() ;
	}

	// inserts value, depends on the "state" of the list
	if (_end - _beg == 1) 	
		/* defines a single-value list */
		uninitialized_insert(value) ;
	else 	/* inserts in an existing list */
		insert_avail(value) ;
}

LinkedList& LinkedList::operator=(const LinkedList& ls) {
	// defines the assignment operator

	// accounts for self-assignment
	if (this != &ls) {
		// obliterates existing values and copies into linked-list
		deallocate() ;
		create(ls.begin(), ls.end()) ;
	}

	return *this ;

}

