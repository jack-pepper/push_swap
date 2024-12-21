/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:35:45 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/21 16:36:22 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"

void    swapper(t_stack *stack)
{
        size_t  *nb;
        int     *stk;

        nb = &stack->nb_elem;
        stk = stack->content;
        if (*nb < 2)
                return ;
        stk[*nb - 1] = stk[*nb - 1] ^ stk[*nb - 2];
        stk[*nb - 2] = stk[*nb - 1] ^ stk[*nb - 2];
        stk[*nb - 1] = stk[*nb - 1] ^ stk[*nb - 2];
}

// sa (swap a):  Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void    sa(t_stack *stack_a)
{
	swapper(stack_a);
	stack_a->last_cmd[0] = 's';
	stack_a->last_cmd[1] = 'a';
}

// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void	sb(t_stack *stack_b)
{
	swapper(stack_b);
	stack_b->last_cmd[0] = 's';
	stack_b->last_cmd[1] = 'b';
}

// ss : sa and sb at the same time.
void	ss(t_stack *stack_a, t_stack *stack_b)
{
	swapper(stack_a);
	swapper(stack_b);
}
