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
 *
 * Revisions:
 * April 19, 2021	adds empty, create, display, insert_front,
 * 			and uncreate (iterator variant) functions
 *
 */

#include <iostream>

struct node {
	int   data = 0 ;
	node* next = NULL ;
} ;

node** empty(node* ptrs[2]) ;
node** create(node* ptrs[2], const int& data) ;

void display(node*) ;
size_t size(node*) ;
node* insert_back(node*, const int&) ;
node* insert_front(node*, node*, const int&) ;
void uncreate(node*) ;	// deprecated in favor of its newest version
void uncreate(node*, node*) ;

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

node** empty(node* ptrs[2]) {
	// creates an empty linked-list
	ptrs[0] = ptrs[1] = NULL ;
	return ptrs;
}

node** create(node* ptrs[2], const int& data) {
	// creates a list with a node initialized by the given data value
	/* DO NOT USE FUNCTION FOR INSERTING VALUES TO AN EXISTING LIST */
	node *head, *tail ;

	/*  unpacks  */
	head = ptrs[0] ;
	tail = ptrs[1] ;

	tail = head = new node ;
	tail -> data = data ;
	tail -> next = NULL ;

	/*   packs   */
	ptrs[0] = head ;
	ptrs[1] = tail ;
	return ptrs;
}

void display(node* head) {
	// displays elements of linked-list to standard output

	node* it = head ;
	while(it != NULL) {
		std::cout << it -> data << std::endl ;
		it = it -> next ;
	}

	return ;
}

node* insert_back(node* tail, const int& data) {
	// inserts a node at the back of the list

	tail -> next = new node ;
	tail = tail -> next ;
	tail -> data = data ;
	tail -> next = NULL ;

	return tail ;
}

node* insert_front(node* head, node* tail, const int& data) {
        // inserts a node at the front of the linked-list

	tail -> next = new node ;
	node* it = tail -> next ;	tail -> next = NULL ;
	it -> data = data ;
	it -> next = head ;
	head = it ;

	return head ;
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
	// initial implementation (deprecated)

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
	head = NULL ;
	return ;
}

void uncreate(node* head, node* tail) {
	// frees memory allocated for linked-list from back to front

	node* it ;
	while(head -> next != tail) {
		it = head ;
		while(it -> next != tail)
			it = it -> next ;
		delete tail ;	tail = NULL ;
		tail = it ;
	}

	// deletes remaining pair
	delete tail ;	tail = NULL ;
	delete head ;	head = NULL ;

	return  ;
}
