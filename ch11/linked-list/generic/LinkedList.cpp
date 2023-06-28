#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>

#define SIZE 16

template<typename T> class LinkedList
{
  public:
    typedef std::size_t size_type;

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


    class Iterator
    {
      private:
	const Node* iter;

      public:
	// typedefs so that we can pass this iterator to STL algorithms, ref[2] and ref[3]
	typedef std::input_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	struct iterator_traits
	{
	  typedef Iterator::iterator_category iterator_category;
	  typedef Iterator::difference_type difference_type;
	  typedef Iterator::value_type value_type;
	  typedef Iterator::pointer pointer;
	  typedef Iterator::reference reference;
	};

	Iterator ()
	{
	  this -> iter = NULL;
	}

	Iterator (const Node* node)
	{
	  this -> iter = node;
	}

	const T& operator * () const
	{
	  return this -> iter -> data;
	}

	void operator ++ ()
	{
	  this -> iter = this -> iter -> next;
	}

	bool operator == (const Iterator& other) const
	{
	  return (this -> iter == other.iter);
	}

	bool operator != (const Iterator& other) const
	{
	  return (this -> iter != other.iter);
	}

	const T* operator -> () const
	{
	  const T* ptr = &(this -> iter -> data);
	  return ptr;
	}
    };

    typedef Iterator const_iterator;

  private:

    Node* head;
    Node* tail;
    size_type numel;

  public:

    LinkedList<T> () : head(NULL), tail(NULL), numel(0) { }

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


    void insert (const T& data)
    {
      std::allocator<Node> alloc;
      if (head == NULL)
      {
	head = alloc.allocate(1);
	*head = Node(data);
	head -> next = alloc.allocate(1);
	Node* next = head -> next;
	*next = Node();
	tail = next;
	++numel;
	return;
      }

      *tail = Node(data);
      tail -> next = alloc.allocate(1);
      Node* next = tail -> next;
      *next = Node();
      tail = next;
      ++numel;
    }


    void print () const
    {
      Node* node = this -> head;

      if (node == NULL)
      {
	std::cout << "LinkedList: empty" << std::endl;
	return;
      }

      while (node != tail)
      {
	node -> print();
	node = node -> next;
      }
    }

    size_type size () const
    {
      return this -> numel;
    }


    T& operator[] (size_type pos)
    {
      size_type i = 0;
      Node* node = head;
      while (i != pos)
      {
	node = node -> next;
	++i;
      }

      T& data = node -> data;
      return data;
    }


    const_iterator begin ()
    {
      return const_iterator(head);
    }


    const_iterator end ()
    {
      return const_iterator(tail);
    }

};


struct Point
{
  int x;
  int y;

  Point () : x(0), y(0) { }

  Point (int x, int y)
  {
   this -> x = x;
   this -> y = y;
  }
};


int main ()
{
  std::vector<int> vec;
  LinkedList<int> list;
  assert(list.size() == 0);
  std::cout << "test[0]: PASSED" << std::endl;
  for (int i = 0; i != SIZE; ++i)
  {
    list.insert(i);
    vec.push_back(i);
  }

  LinkedList<int>::size_type const size = SIZE;
  assert(list.size() == size);
  std::cout << "test[1]: PASSED" << std::endl;

  for (LinkedList<int>::size_type i = 0; i != list.size(); ++i)
  {
    assert(list[i] == vec[i]);
  }
  std::cout << "test[2]: PASSED" << std::endl;

  std::vector<int>::size_type i = 0;
  for (LinkedList<int>::const_iterator it = list.begin(); it != list.end(); ++it)
  {
    assert(*it == vec[i]);
    ++i;
  }
  std::cout << "test[3]: PASSED" << std::endl;

  i = 0;
  LinkedList<int>::const_iterator it = list.begin();
  while ( it != list.end() )
  {
    assert(*it == vec[i]);
    ++it;
    ++i;
  }
  std::cout << "test[4]: PASSED" << std::endl;

  assert( it == list.end() );
  std::cout << "test[5]: PASSED" << std::endl;

  for (int i = 0; i != SIZE; ++i)
  {
    LinkedList<int>::const_iterator iter = std::find(list.begin(), list.end(), i);
    assert(*iter == i);
  }
  std::cout << "test[6]: PASSED" << std::endl;

  int sum = 0;
  for (const auto& elem : list)
  {
    sum += elem;
  }
  assert(sum == SIZE * (SIZE - 1) / 2);
  std::cout << "test[7]: PASSED" << std::endl;

  LinkedList<Point> points;
  for (LinkedList<Point>::size_type i = 0; i != SIZE; ++i)
  {
    Point point(i, i);
    points.insert(point);
  }

  sum = 0;
  for (LinkedList<Point>::const_iterator it = points.begin(); it != points.end(); ++it)
  {
    sum += (it -> x);
  }
  assert(sum == SIZE * (SIZE - 1) / 2);
  std::cout << "test[8]: PASSED" << std::endl;

  sum = 0;
  for (const auto& point : points)
  {
    sum += (point.x + point.y);
  }
  assert(sum == SIZE * (SIZE - 1));
  std::cout << "test[9]: PASSED" << std::endl;

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
[2] https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
[3] https://en.cppreference.com/w/cpp/iterator/iterator_traits

*/
