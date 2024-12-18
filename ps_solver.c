/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/18 10:33:55 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_ordered(t_stack *stack);
void	handle_small_stacks(t_list *cmd_list, t_stack *stack_a);

t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{	
	if (is_ordered(stack_a) == 0)
		return (cmd_list);
	if (stack_a->len <= 3)
	{
		handle_small_stacks(cmd_list, stack_a);
		return (cmd_list);
	}
	stack_b->len = stack_a->len; // Only for compil (variable non used), delete after using stack_b)
	return (cmd_list);
}

int	is_ordered(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < (stack->len - 1))
	{
		if (stack->content[i] < stack->content[i + 1])
		{
		//	ft_printf("is NOT ordered!\n");
			return (1);
		}
		i++;
	}
	ft_printf("is ordered!\n");
	return (0);
}

/* NB: This function is called only if the stack is not ordered. */
void	handle_small_stacks(t_list *cmd_list, t_stack *stack_a)
{
	t_list	*new_cmd;

	if (stack_a->len == 2)
		new_cmd = ft_lstnew("sa");
	else if (stack_a->len == 3)
	{
		if (stack_a->highest_pos == 0)
			new_cmd = ft_lstnew("sa");
		else if (stack_a->highest_pos == 1)
			new_cmd = ft_lstnew("rra");
		else if (stack_a->highest_pos == 2) 
			new_cmd = ft_lstnew("ra");
	}
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if ((stack_a->highest_pos == 1 && stack_a->lowest_pos == 2) 
		|| (stack_a->highest_pos == 2 && stack_a->lowest_pos == 0))
	{
		new_cmd = ft_lstnew("sa");	
		ft_lstadd_back(&cmd_list, new_cmd);
		if (!new_cmd)
			return ;
	}	
}
