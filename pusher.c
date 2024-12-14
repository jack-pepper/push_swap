
#include "push_swap.h"
#include "./libft/libft.h"

void	pusher(t_stack *stack_dst, t_stack *stack_src)
{
	size_t	nb_dst;
	size_t	nb_src;
	
	nb_dst = stack_dst->nb_elem;
	nb_src = stack_src->nb_elem;
	//ft_printf("stk_src[*nb_src] = %d\n", stack_src.content[nb_src_i]);
	if (nb_src != 0)
	{
		//ft_printf("1: nb_dst: %d - nb_src: %d\n", *nb_dst, *nb_src);
		stack_dst->content[nb_dst] = stack_src->content[nb_src - 1];
		//ft_printf("2");
		stack_dst->nb_elem++;
		//ft_printf("[PUSHER] nb_dst: %d\n", nb_dst);
		stack_src->content[nb_src - 1] = 0;
		//ft_printf("4");
		stack_src->nb_elem--;
		//ft_printf("[PUSHER] nb_src: %d\n", nb_src);

	}
}
// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
void	pa(t_stack *stack_a, t_stack *stack_b)
{
	pusher(stack_a, stack_b);
}

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.


void	pb(t_stack *stack_b, t_stack *stack_a)
{
	pusher(stack_b, stack_a);
}

