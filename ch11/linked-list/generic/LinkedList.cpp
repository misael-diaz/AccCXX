#include <iostream>

#define SIZE 16

template<typename T> class LinkedList
{
  class Node
  {
    public:

      T data;
      Node* next;

      Node () : data(), next(NULL) { }

      Node (const T& d) : data(d), next(NULL) { }

      void print () const
      {
	std::cout << this -> data << std::endl;
      }
  };

  private:

  Node* head;
  Node* tail;

  public:

  LinkedList<T> () : head(NULL), tail(NULL) { }

  ~LinkedList<T> ()
  {
    Node* node = this -> head;
    if (head == NULL)
    {
      return;
    }

    std::allocator<Node> alloc;
    Node* next = node -> next;
    alloc.deallocate(node, 1);

    while (next != NULL)
    {
      node = next;
      next = (node == NULL)? NULL : node -> next;
      alloc.deallocate(node, 1);
    }
  }


  void insert (T data)
  {
    std::allocator<Node> alloc;
    if (head == NULL)
    {
      head = alloc.allocate(1);
      *head = Node(data);
      tail = head;
      return;
    }

    tail -> next = alloc.allocate(1);
    Node* next = tail -> next;
    *next = Node(data);
    tail = next;
  }


  void print () const
  {
    Node* node = this -> head;

    if (node == NULL)
    {
      std::cout << "LinkedList: empty" << std::endl;
      return;
    }

    Node* next = node -> next;
    while (next != NULL)
    {
      node -> print();
      node = next;
      next = (node == NULL)? NULL : node -> next;
    }

    node -> print();
  }

};


int main ()
{
  LinkedList<int> list;
  for (int i = 0; i != SIZE; ++i)
  {
    list.insert(i);
  }

  list.print();
  return 0;
}


/*

Generic Linked-List						June 26, 2023

source: LinkedList.cpp
author: @misael-diaz

Synopsis:
Implements a generic linked-list class.

Copyright (c) 2023 Misael Diaz-Maldonado
This file is released under the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example
[1] https://en.cppreference.com/w/cpp/memory/allocator

*/
