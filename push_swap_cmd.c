
#include "push_swap.h"
#include <stdio.h> // DEBUG!!!
#include <unistd.h>

/*
 * Beggining: 
 * - Stack a contains a random amount of negative and/or positive numbers which cannot be duplicated
 * - Stack b is empty
 */

// sa (swap a):  Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void	sa(int *stack_a)
{
}

// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void	sb()
{
}

// ss : sa and sb at the same time.
void	ss()
{
}
	
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
void	pa()
{
}

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.

void	pb()
{
}

// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.
void	ra()
{
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.
void	rb()
{
}

//rr : ra and rb at the same time.

void	rr()
{
}

// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.
void	rra()
{
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.
void	rrb()
{
}

// rrr : rra and rrb at the same time.
void	rrr()
{
}


// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
