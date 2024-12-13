
#include "push_swap.h"
#include <stdio.h> // DEBUG!!!
#include <unistd.h>

void    swapper(t_stack stack)
{
        size_t  nb;
        int     *stk;

        nb = stack.nb_elem;
        stk = stack.content;
        if (nb < 2)
                return ;
        stk[nb - 1] = stk[nb - 1] ^ stk[nb - 2];
        stk[nb - 2] = stk[nb - 1] ^ stk[nb - 2];
        stk[nb - 1] = stk[nb - 1] ^ stk[nb - 2];
        ft_printf("stk[nb - 1] = %d - stk[nb - 2] = %d\n", stk[nb - 1], stk[nb - 2]);
}

// sa (swap a):  Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void    sa(t_stack stack_a)
{
	swapper(stack_a);
}

// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void	sb(t_stack stack_b)
{
	swapper(stack_b);
}

// ss : sa and sb at the same time.
void	ss(t_stack stack_a, t_stack stack_b)
{
	swapper(stack_a);
	swapper(stack_b);
}

void	pusher(t_stack stack_dst, t_stack stack_src)
{
	size_t	nb_dst;
	size_t	nb_src;
	int	*stk_dst;
	int	*stk_src;

	stk_dst = stack_dst.content;
	stk_src = stack_src.content;
	nb_dst = stack_dst.nb_elem;
	nb_src = stack_src.nb_elem;
	if (nb_src != 0)
	{
		stk_dst[nb_b] = stk_src[nb_b - 1];
		nb_dst++;
		stk_src[nb_b - 1] = 0;
		nb_src--;
	}
}
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
void	pa(t_stack stack_a, t_stack stack_b)
{
	pusher(stack_a, stack_b);
}

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.


void	pb(t_stack stack_b, t_stack stack_a)
{
	pusher(stack_b, stack_a);
}

void	rotater(t_stack stack)
{

}
// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.
void	ra(t_stack stack_a)
{
	rotater(stack_a);
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.
void	rb(t_stack stack_b)
{
	rotater(stack_b);
}

//rr : ra and rb at the same time.

void	rr()
{
	rotater(stack_a);
	rotater(stack_b);
}


void	reverse_rotater(t_stack stack)
{

}
// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.
void	rra(t_stack stack_a)
{
	reverse_rotater(stack_a);
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.
void	rrb()
{
	reverse_rotater(stack_b);
}

// rrr : rra and rrb at the same time.
void	rrr()
{	
	reverse_rotater(stack_a);
	reverse_rotater(stack_b);
}


// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
