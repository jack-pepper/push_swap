/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:04:06 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/23 20:05:03 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotater(t_stack *stack)
{
	size_t	*nb;
	int		*stk;
	int		temp;
	size_t	i;

	nb = &stack->nb_elem;
	stk = stack->content;
	temp = stk[0];
	i = 0;
	while (i < *nb)
	{
		stk[i] = stk[i + 1];
		i++;
	}
	stk[*nb - 1] = temp;
}

// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.
void	rra(t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;

	reverse_rotater(stack_a);
	new_cmd = ft_lstnew("rra");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.
void	rrb(t_stack *stack_b, t_list *cmd_list)
{
	t_list	*new_cmd;

	reverse_rotater(stack_b);
	new_cmd = ft_lstnew("rrb");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// rrr : rra and rrb at the same time.
void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	reverse_rotater(stack_a);
	reverse_rotater(stack_b);
}
