/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/21 21:25:22 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	int	*stk_b;
	int	nb_el_b;

	stk_b = stack_b->content;
	nb_el_b = stack_b->nb_elem;
	if (is_ordered(stack_a) == 0)
		return (cmd_list);
	if (stack_a->nb_elem <= 3)
	{
		handle_small_stack(cmd_list, stack_a);
		return (cmd_list);
	}
	while (is_ordered(stack_a) != 0)
	{
		rotate_lowest_and_push(stack_a, stack_b);
		if ((nb_el_b > 1) 
			&& (stk_b[nb_el_b - 1] < stk_b[nb_el_b - 2]))
			sb(stack_b);
	}
	while (nb_el_b > 0)
		pa(stack_a, stack_b);
	return (cmd_list);
}

void	rotate_lowest_and_push(t_stack *stack_a, t_stack *stack_b)
{
	size_t	low_i;
	size_t	len_i;

	low_i = stack_a->lowest_pos;
	len_i = stack_a->len - 1; // to make it more readable
	if (low_i == len_i)
	{
		pb(stack_b, stack_a);
		return ;
	}
	else if ((len_i / 2) < low_i)
	{
		while (low_i > 0)
		{
			ra(stack_a);
			low_i--; 
		}
	}
	else
	{
		while (low_i < stack_a->nb_elem)
		{
			rra(stack_a);
			low_i++;
		}
	}
}

int	is_ordered(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < (stack->nb_elem - 1))
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
void	handle_small_stack(t_list *cmd_list, t_stack *stack_a)
{
	t_list	*new_cmd;

	if (stack_a->nb_elem == 2)
		new_cmd = ft_lstnew("sa");
	else if (stack_a->nb_elem == 3)
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
