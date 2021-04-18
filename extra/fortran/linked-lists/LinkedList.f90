        ! author: misael-diaz                               April 17, 2021
        ! source: LinkedList.f90
        !
        ! Synopsis:
        ! Basic linked-list implementation. Values can be inserted at
        ! the back or anywhere else in the list.
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
        ! TODO:
        ! [x] hide the implementation details, having users to create a
        !     node to be able to insert values to a linked-list is not
        !     ideal.
        !
        module alloc
                ! implements memory (de)allocation, failure, handlers
                use, intrinsic :: iso_fortran_env
                implicit none
                public
                
                contains
                subroutine dispAllocFailMsg(mstat)
                        integer(kind=int32), intent(in) :: mstat
                        if (mstat /= 0) then
                                write (*, *) "memory allocation failed"
                                write (*, *) "insufficient memory"
                                stop
                        end if
                end subroutine

                subroutine dispDeallocFailMsg(mstat)
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

                interface insert
                        module procedure inserter, insert_at_position
                end interface

                private
                public node
                public nullifies
                public insert
                public display

                contains
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
                
                subroutine inserter(head, tail, val)
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
        end module lists
      
        program main
                ! program uses linked-list implementation
                use, intrinsic :: iso_fortran_env
                use nodes
                use lists
                implicit none

                type(node), pointer :: head => null()
                type(node), pointer :: tail => null()
                type(node), pointer :: mid => null()    ! middle node

                integer(kind=int32) :: k        ! counter
                integer(kind=int32) :: pos      ! position

                ! initializes linked-list by nullifying pointers
                call nullifies(head, tail)
                do k = 1, 8
                        ! builds linked-list
                        call insert(head, tail, k)
                end do
                call display(head)      ! displays linked-list
                write (*, *)

                ! inserts node at position
                k = 0
                pos = 4
                call insert(head, tail, pos, k)
                call display(head)

        end program
