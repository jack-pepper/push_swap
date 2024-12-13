
#include "push_swap.h"
#include "./libft/libft.h"

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
		stk_dst[nb_src] = stk_src[nb_src - 1];
		nb_dst++;
		stk_src[nb_src - 1] = 0;
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

