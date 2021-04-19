/* source: linked-list.cpp
 * author: misael-diaz
 * date:   April 18, 2021
 *
 * Synopsis:
 * My initial (yet rudimentary) implementation of a singly linked-list.
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
 * [ ] partition the code
 * [ ] add functionality: insert at the front, insert at position,
 *                        and other useful utilities for manipulation.
 */

#include <iostream>

struct node {
	int   data = 0 ;
	node* next = NULL ;
} ;

node* insert_back(node*, const int&) ;
size_t size(node*) ;
void uncreate(node*) ;

int main() {
	
	// first node
	node* ptr = new node ;
	node* head ;
	node* tail ;
	node* it ;		// iterator

	// points both head and tail to node
	tail = head = ptr ;
	tail -> data = 0 ;	// defines a value for node
	tail -> next = NULL ;	

	// creates a new node bound to next
	tail -> next = new node ;
	tail = tail -> next ;	// tail now points to new node
	head -> next = tail ;	// links head to new node
	tail -> data = 1 ;
	tail -> next = NULL ;	

	for(int i = 2; i != 8; ++i)
		// insert values at the back of list
		tail = insert_back(tail, i) ;

	it = head ;
	while(it != NULL) {
		// display values
		std::cout << it -> data << std::endl ;
		it = it -> next ;
	}

	// report the size of the list
	std::cout << "size: " << size(head) << std::endl ;
	// frees allocated memory
	uncreate(head) ;

	return 0 ;
}

node* insert_back(node* tail, const int& data) {
        // inserts a node at the back of the list
        tail -> next = new node ;
        tail = tail -> next ;   // advances tail to new node
        tail -> data = data ;
        tail -> next = NULL ;

	return tail ;		// returns new pointer to caller
}

size_t size(node* head) {
	// determines the number of elements in linked-list
	node* it = head ;
	size_t size = 0 ;
        while(it != NULL) {
                it = it -> next ;
                ++size ;
        }
	return size ;
}

void uncreate(node* head) {
	node* it ;
	while(size(head) != 1) {
		// deletes elements in the asymetric range (head, tail]
		it = head ;
		// advances to the node just before tail
		for(int n = 0; n != (size(head) - 2); ++n)
			it = it -> next ;
		// deletes and nullifies tail
		delete it -> next ;
		it -> next = NULL ;
	}
	delete head ;	// deletes the remaining one
	return ;
}
