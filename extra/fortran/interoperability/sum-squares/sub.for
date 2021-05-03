#include "macros.h"
        !
        ! source: sub.f90
        ! author: misael-diaz
        ! date:   2021/05/03
        !
        ! Synopsis:
        ! Returns the sum of the squares of the elements of an array.
        !
        !
        ! Copyright (c) 2021 Misael Diaz-Maldonado
        !
        ! This file is released under the GNU General Public License as
        ! published by the Free Software Foundation, either version 3 of
        ! the License, or (at your option) any later version.
        !
        !
        ! References:
        ! SJ Chapman, Fortran for scientists and engineers, 4th edition
        !

        pure subroutine sum_squares(x, total) bind(c)
                use, intrinsic :: iso_c_binding
                implicit none
                real(kind=c_double), intent(in) :: x(N)
                real(kind=c_double), intent(out) :: total

                total = sum(x**2)
        end subroutine

