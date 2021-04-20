#ifndef GUARD_MD_LINKED_LIST_H
#define GUARD_MD_LINKED_LIST_H

/*
 * source: LinkedList.h
 * author: misael-diaz
 * 
 * Synopsis:
 * Declares the LinkedList class.
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

struct node {
        int   data = 0 ;
        node* next = NULL ;
} ;

node** empty(node* ptrs[2]) ;
node** create(node* ptrs[2], const int& data) ;
void uncreate(node*, node*) ;

size_t size(node*) ;
void display(node*) ;

node* insert_back(node*, const int&) ;
node* insert_front(node*, node*, const int&) ;

#endif
