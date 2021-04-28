        ! author: misael-diaz                               April 18, 2021
        ! source: class_LinkedList.f90
        !
        ! Synopsis:
        ! A basic linked-list implementation. Values can be inserted at
        ! the back of the list.
        !
        ! References:
        ! SJ Chapman, FORTRAN for scientists and engineers, 4th edition
        !
        ! *************************************************************** !
        ! Comments on Syntax:                                             !
        ! In C/C++, a pointer to a struct object is derefenced either by  !
        ! (*ptr).val or ptr -> val to get at the val member of the struct !
        ! object.                                                         !
        ! FORTRAN syntax might be confusing because it seems as if the    !
        ! pointer is the struct object itself.                            !
        ! *************************************************************** !
        !
        module alloc
                ! implements memory (de)allocation, failure, handlers
                use, intrinsic :: iso_fortran_env
                implicit none
                public
                
                contains
                subroutine dispAllocFailMSG(mstat)
                        integer(kind=int32), intent(in) :: mstat
                        if (mstat /= 0) then
                                write (*, *) "memory allocation failed"
                                write (*, *) "insufficient memory"
                                stop
                        end if
                end subroutine

                subroutine dispDeallocFailMSG(mstat)
                        integer(kind=int32), intent(in) :: mstat
                        if (mstat /= 0) then
                                write (*, *) "deallocation failed"
                                stop
                        end if
                end subroutine
        end module alloc

        module nodes
                ! defines the node derived-type and utility subroutines
                use, intrinsic :: iso_fortran_env
                use alloc
                implicit none

                type node
                        integer(kind=int32) :: val
                        type(node), pointer :: next
                end type
                
                private
                public node
                public create_node

                contains
                subroutine create_node(ptr, val)
                        ! Creates a new node initialized to val
                        ! meant to be placed either at the head or tail.

                        type(node), pointer, intent(inout) :: ptr
                        integer(kind=int32), intent(in) :: val

                        if ( .not. associated(ptr) ) then
                                call head(ptr, val)
                        else
                                call tail(ptr, val)
                        end if

                end subroutine

                subroutine head(ptr, val)
                        ! creates a node to be placed at the head
                        type(node), pointer, intent(inout) :: ptr
                        integer(kind=int32), intent(in) :: val
                        integer(kind=int32) :: mstat
                        
                        allocate(ptr, stat=mstat)
                        call dispAllocFailMsg(mstat)

                        ptr % val = val
                        ptr % next => null()
                end subroutine

                subroutine tail(ptr, val)
                        ! creates a node to be placed at the tail
                        type(node), pointer, intent(inout) :: ptr
                        integer(kind=int32), intent(in) :: val
                        integer(kind=int32) :: mstat

                        allocate(ptr % next, stat=mstat)
                        call dispAllocFailMsg(mstat)
                        
                        ptr => ptr % next
                        ptr % val = val
                        ptr % next => null()
                end subroutine
        end module nodes

        module lists
                ! implements subroutine for building linked-lists
                use alloc
                use nodes
                use, intrinsic :: iso_fortran_env
                implicit none

                type, public :: LinkedList
                        private
                        type(node), pointer :: it       ! iterator
                        type(node), pointer :: head     ! begin
                        type(node), pointer :: tail     ! end
                        contains
                        procedure, public :: push_back =>&
                                & back_inserter_method
                        procedure, public :: display =>&
                                & display_method
                        procedure, public :: begin => begin_method
                        procedure, public :: end => final_method
                        procedure, public :: next => next_method
                        procedure, public :: size => size_method
                        final :: destructor
                end type

                interface insert
                        procedure insert_at_position
                end interface
                
                interface linkedlist
                        procedure constructor
                end interface

                private
                
                contains
                function constructor()
                        type(LinkedList) :: constructor
                        constructor % head => null()
                        constructor % tail => null()
                end function
                        
                subroutine nullifies(head, tail)
                        ! nullifies "head" and "tail" pointers
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail

                        nullify(head)
                        nullify(tail)
                end subroutine

                subroutine initialize(head, tail, val)
                        ! initializes linked-list so that both head
                        ! and tail point at the same node
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail
                        integer(kind=int32), intent(in) :: val

                        call create_node(head, val)
                        tail => head
                end subroutine

                subroutine insert_back(tail, val)
                        ! inserts at the back (end) of the linked-list
                        type(node), pointer, intent(inout) :: tail
                        integer(kind=int32), intent(in) :: val

                        call create_node(tail, val)
                end subroutine

                subroutine insert_front(head, val)
                        ! inserts at the front (begin) of the linked-list
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer :: it => null()
                        integer(kind=int32), intent(in) :: val

                        ! creates a new head node
                        it => head
                        head => null()
                        call create_node(head, val)
                        head % next => it       ! links new to old head
                end subroutine

                subroutine insert_at_position(head, tail, pos, val)
                        ! inserts node at position indicated by [pos]
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail
                        type(node), pointer :: mid
                        type(node), pointer :: it

                        integer(kind=int32), intent(in) :: pos
                        integer(kind=int32), intent(in) :: val
                        integer(kind=int32) :: mstat
                        integer(kind=int32) :: n

                        n = 0
                        it => head
                        do while(n /= pos - 1)
                                ! advances iterator
                                it => it % next
                                n = n + 1
                        end do

                        ! spawns a node at the back of the list
                        allocate(tail % next, stat=mstat)
                        call dispAllocFailMsg(mstat)
                        mid => tail % next      ! associates ptr to node
                        tail % next => null()   ! unlinks node from list

                        ! inserts node between (left) pos-1 and (right) pos
                        mid % next => it % next ! links node on right
                        it  % next => mid       ! links node of left
                        
                end subroutine
                
                subroutine back_inserter(head, tail, val)
                        ! inserts node to linked-list, it either
                        ! initializes the linked-list or inserts
                        ! a node at the back (end).
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail
                        integer(kind=int32), intent(in) :: val
                        
                        if ( .not. associated(head) ) then
                                call initialize(head, tail, val)
                        else
                                call insert_back(tail, val)
                        end if

                end subroutine

                subroutine front_inserter(head, tail, val)
                        ! inserts node to linked-list, it either
                        ! initializes the linked-list or inserts
                        ! a node at the front (begin).
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail
                        integer(kind=int32), intent(in) :: val

                        if ( .not. associated(head) ) then
                                call initialize(head, tail, val)
                        else
                                call insert_front(head, val)
                        end if

                end subroutine

                subroutine display(head)
                        ! displays linked-list values
                        type(node), pointer, intent(in) :: head
                        type(node), pointer :: it => null()

                        it => head      ! associate iterator to head
                        do while( associated(it) )
                                print *, it % val
                                it => it % next
                        end do
                end subroutine

                function numel(head)
                        ! returns the size of the list
                        type(node), pointer, intent(in) :: head
                        type(node), pointer :: it => null()
                        integer(kind=int32) :: numel

                        numel = 0
                        it => head
                        do while( associated(it) )
                                it => it % next
                                numel = numel + 1
                        end do
                end function

                function empty(head)
                        ! returns true if list is empty, false otherwise
                        type(node), pointer, intent(in) :: head
                        logical(kind=int32) :: empty

                        if ( associated(head) ) then
                                empty = .false.
                        else
                                empty = .true.
                        end if
                end function

                function last(head)
                        ! returns index to last element in list
                        type(node), pointer, intent(in) :: head
                        type(node), pointer :: it => null()
                        integer(kind=int32) :: last

                        last = 0
                        if ( associated(head) ) then
                                it => head
                                do while( associated(it % next) )
                                        it => it % next
                                        last = last + 1
                                end do
                        end if
                end function

                subroutine free(head, tail)
                        ! frees memory allocated for the linked-list
                        type(node), pointer, intent(inout) :: head
                        type(node), pointer, intent(inout) :: tail
                        type(node), pointer :: it => null()
                        integer(kind=int32) :: mstat
                        integer(kind=int32) :: n

                        do while (numel(head) /= 1)
                                ! frees nodes in the range (head, tail]
                                n = 0
                                it => head
                                do while (n /= last(head) - 1)
                                        ! advances to (tail - 1)
                                        it => it % next
                                        n = n + 1
                                end do
                                ! deallocates and nullifies tail
                                deallocate(it % next, stat=mstat)
                                call dispDeallocFailMSG(mstat)
                                it % next => null()
                        end do

                        ! deallocates head
                        deallocate(head, stat=mstat)
                        call dispDeallocFailMSG(mstat)
                        ! destroys the list by nullifying its pointers
                        head => null()
                        tail => null()
                end subroutine

                subroutine begin_method(this)
                        ! sets the iterator at the beginning of the list
                        class(LinkedList) :: this

                        this % it => this % head
                end subroutine

                subroutine final_method(this)
                        ! sets the iterator on the final element
                        class(LinkedList) :: this

                        this % it => this % tail
                end subroutine

                function next_method(this)
                        ! advances the iterator to the next element
                        ! and returns its value
                        class(LinkedList) :: this
                        integer(kind=int32) :: next_method

                        next_method = this % it % val
                        this % it => this % it % next
                end function

                function size_method(this)
                        class(LinkedList) :: this
                        integer(kind=int32) :: size_method

                        size_method = numel(this % head)
                end function

                subroutine back_inserter_method(this, val)
                        ! inserts node to linked-list, it either
                        ! initializes the linked-list or inserts
                        ! a node at the back (end).
                        class(LinkedList) :: this
                        integer(kind=int32), intent(in) :: val

                        if ( .not. associated(this % head) ) then
                                call initialize(this % head,&
                                              & this % tail, val)
                        else
                                call insert_back(this % tail, val)
                        end if
                end subroutine

                subroutine display_method(this)
                        ! displays linked-list values
                        class(LinkedList) :: this
                        type(node), pointer :: it => null()

                        it => this % head
                        do while( associated(it) )
                                print *, it % val
                                it => it % next
                        end do
                end subroutine

                subroutine destructor(this)
                        type(LinkedList) :: this
                        call free(this % head, this % tail)
                end subroutine
        end module lists
      
        program main
                ! program uses linked-list implementation
                use, intrinsic :: iso_fortran_env
                use nodes
                use lists
                implicit none

                type(LinkedList) :: list

                integer(kind=int32) :: k        ! counter
                integer(kind=int32) :: n        ! counter
                integer(kind=int32) :: pos      ! position

                write (*, *) 'linked-list object:'
                ! instantiates an object of the linked-list class
                list = linkedlist()
                do k = 0, 7
                        ! pushes values at the back of the list
                        call list % push_back(k)
                end do
                ! displays all values to standard output
                call list % display()
                write (*, *)

                n = 0
                call list % begin()
                do while(n /= list % size())
                        ! gets at the values in linked-list
                        print *, list % next()
                        n = n + 1
                end do
        end program
