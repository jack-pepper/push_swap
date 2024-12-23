/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:35:45 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/23 20:01:11 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swapper(t_stack *stack)
{
	size_t	*nb;
	int		*stk;

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
void	sa(t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;

	swapper(stack_a);
	new_cmd = ft_lstnew("sa");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void	sb(t_stack *stack_b, t_list *cmd_list)
{
	t_list	*new_cmd;

	swapper(stack_b);
	new_cmd = ft_lstnew("sb");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// ss : sa and sb at the same time.
void	ss(t_stack *stack_a, t_stack *stack_b)
{
	swapper(stack_a);
	swapper(stack_b);
}
