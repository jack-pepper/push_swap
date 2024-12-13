
#include "push_swap.h"
#include "./libft/libft.h"

/* Rotate function */
void	rotater(t_stack stack)
{
	size_t	nb;
	int	*stk;
	int	temp;

	nb = stack.nb_elem;
	stk = stack.content;
	temp = stk[nb - 1];
	
	while (nb > 1)
	{
		stk[nb - 1] = stk[nb - 2];
		nb--;
	}
	stk[0] = temp;
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

void	rr(t_stack stack_a, t_stack stack_b)
{
	rotater(stack_a);
	rotater(stack_b);
}
