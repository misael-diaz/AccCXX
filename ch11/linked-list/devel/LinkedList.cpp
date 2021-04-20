/*
 * source: LinkedList.cpp
 * author: misael-diaz
 * 
 * Synopsis:
 * Defines the LinkedList class.
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include <iostream>
#include "LinkedList.h"

node** empty(node* ptrs[2]) {
        // creates an empty linked-list
        
	ptrs[0] = ptrs[1] = NULL ;
        return ptrs;
}

node** create(node* ptrs[2], const int& data) {
        // creates a list with a node initialized by the given data value
	/* WARNING:                                                     */
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

void uncreate(node* head, node* tail) {
        // frees memory allocated for linked-list from back to front

        node* it ;
        while(head -> next != tail) {
                it = head ;
                while(it -> next != tail)
                        it = it -> next ;
                delete tail ;   tail = NULL ;
                tail = it ;
        }

        // deletes remaining pair
        delete tail ;   tail = NULL ;
        delete head ;   head = NULL ;

        return  ;
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
        node* it = tail -> next ;       tail -> next = NULL ;
        it -> data = data ;
        it -> next = head ;
        head = it ;

        return head ;
}

