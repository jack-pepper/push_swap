/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/22 23:22:44 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_b(t_stack *stack_b, t_list *cmd_list)
{
	find_highest(stack_b);
	find_lowest(stack_b);
	if (stack_b->nb_elem == 2 && stack_b->index_map[0] > stack_b->index_map[1])
		swapper(stack_b, cmd_list, "sb");
	else if (stack_b->nb_elem == 3)
	{
		if (stack_b->lowest_pos == 0)
			swapper(stack_b, cmd_list, "sb");
		else if (stack_b->lowest_pos == 1)
			reverse_rotater(stack_b, cmd_list, "rrb");
		else if (stack_b->lowest_pos == 2)
			rotater(stack_b, cmd_list, "rb");
	}
	if ((stack_b->lowest_pos == 1 && stack_b->highest_pos == 2)
		|| (stack_b->lowest_pos == 2 && stack_b->highest_pos == 0))
		swapper(stack_b, cmd_list, "sb");
}

void	optimal_rot_b(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list, int tgt_i)
{
	int	top_i;
	int	next_highest;

	top_i = (stack_b->nb_elem - 1);
	next_highest = (stack_b->highest - 1);
	if (tgt_i >= (top_i / 2))
	{
		while (tgt_i < top_i)
		{
			if (stack_b->index_map[stack_b->nb_elem - 1] == next_highest)
			{
				pusher(stack_a, stack_b, cmd_list, "pa");
				top_i--;
			}
			if (stack_b->index_map[stack_b->nb_elem - 1] != stack_b->highest)
			{
				rotater(stack_b, cmd_list, "rb");
				tgt_i++;
			}
		}
	}
	else
	{
		while (tgt_i > -1)
		{	
			if (stack_b->index_map[stack_b->nb_elem - 1] == next_highest)
				pusher(stack_a, stack_b, cmd_list, "pa");
			reverse_rotater(stack_b, cmd_list, "rrb");
			tgt_i--;
		}
	}
}

void	find_highest(t_stack *stack)
{
	size_t	i;

	i = 0;
	stack->highest = stack->index_map[0];
	stack->highest_pos = i;
	while (i < stack->len)
	{
		if (stack->index_map[i] > stack->highest)
		{
			stack->highest = stack->index_map[i];
			stack->highest_pos = i;
		}
		i++;
	}
}

void	ps_to_a(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{	
	while (stack_b->nb_elem > 3)
	{
		find_highest(stack_b);
		optimal_rot_b(stack_a, stack_b, cmd_list, stack_b->highest_pos);
		pusher(stack_a, stack_b, cmd_list, "pa");
		if ((stack_a->nb_elem > 1 && (stack_a->index_map[stack_a->nb_elem - 1]) > (stack_a->index_map[stack_a->nb_elem - 2]))) 
			swapper(stack_a, cmd_list, "sa"); // swap top b and next b if the next one has been found
	}	
	if (is_ordered(stack_b, 'a') != 0)
		sort_three_b(stack_b, cmd_list);
	while (stack_b->nb_elem > 0)
		pusher(stack_a, stack_b, cmd_list, "pa");
	return ;
}
