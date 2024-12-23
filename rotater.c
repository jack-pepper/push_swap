/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:48:03 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/23 20:02:06 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Rotate function */
void	rotater(t_stack *stack)
{
	size_t	nb;
	int		*stk;
	int		temp;

	nb = stack->nb_elem;
	stk = stack->content;
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
void	ra(t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;

	rotater(stack_a);
	new_cmd = ft_lstnew("ra");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.
void	rb(t_stack *stack_b, t_list *cmd_list)
{
	t_list	*new_cmd;

	rotater(stack_b);
	new_cmd = ft_lstnew("rb");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

//rr : ra and rb at the same time.
void	rr(t_stack *stack_a, t_stack *stack_b)
{
	rotater(stack_a);
	rotater(stack_b);
}
