/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 00:39:56 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_a(t_stack *stack_a, t_list *cmd_list)
{
	find_highest(stack_a);
	find_lowest(stack_a);
	if (stack_a->nb_elem == 2)
		swapper(stack_a, cmd_list, "sa");
	else if (stack_a->nb_elem == 3)
	{
		if (stack_a->highest_pos == 0)
			swapper(stack_a, cmd_list, "sa");
		else if (stack_a->highest_pos == 1)
			reverse_rotater(stack_a, cmd_list, "rra");
		else if (stack_a->highest_pos == 2)
			rotater(stack_a, cmd_list, "ra");
	}
	if ((stack_a->highest_pos == 1 && stack_a->lowest_pos == 2)
		|| (stack_a->highest_pos == 2 && stack_a->lowest_pos == 0))
		swapper(stack_a, cmd_list, "sa");
}

/* Find the optimal rotation or reverse rotation to bring the given target
 * to the top of the current stack.
 */
void	optimal_rot_a(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list, int dist)
{
	if (dist == 0)
		return ;
	while (dist != 0)
	{
		find_highest(stack_b);
		if (dist > 0)
		{
			rotater(stack_a, cmd_list, "ra");
			if ((stack_b->nb_elem > 1)
				&& (stack_b->highest_pos != stack_b->nb_elem -1)
				&& (stack_b->highest_pos < ((stack_b->nb_elem - 1) - dist)))
				rotater(stack_b, cmd_list, "rb");
			dist--;
		}
		else if (dist < 0)
		{
			reverse_rotater(stack_a, cmd_list, "rra");
			if (((stack_b->nb_elem) > 1)
				&& (stack_b->highest_pos != stack_b->nb_elem -1)
				&& ((int)stack_b->highest_pos < (dist * -1)))
				reverse_rotater(stack_b, cmd_list, "rrb");
			dist++;
		}
	}
}

void	find_lowest(t_stack *stack)
{
	size_t	i;

	stack->lowest = stack->index_map[0];
	stack->lowest_pos = 0;
	i = 1;
	while (i < stack->nb_elem)
	{
		if (stack->index_map[i] < stack->lowest)
		{
			stack->lowest = stack->index_map[i];
			stack->lowest_pos = i;
		}
		i++;
	}
}

void	ps_to_b(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
	int	pivot;
	int	max;
	int	dist;

	pivot = (int)ft_sqrt_newton((double)stack_a->nb_elem) - 1;
	find_lowest(stack_a);
	max = stack_a->lowest + pivot;
	while ((stack_a->nb_elem > 3) && (is_ordered(stack_a, 'd') != 0))
	{
		while (stack_a->lowest < max)
		{
			dist = get_shortest_dist(stack_a, stack_a->lowest, max);
			optimal_rot_a(stack_a, stack_b, cmd_list, dist);
			pusher(stack_b, stack_a, cmd_list, "pb");
			find_lowest(stack_a);
		}
		max = stack_a->lowest + pivot;
		if (max > (int)stack_a->len - 1)
			max = stack_a->len - 1;
	}
	if (is_ordered(stack_a, 'd') != 0)
		sort_three_a(stack_a, cmd_list);
	return ;
}
