/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/22 22:43:11 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Test easy cases:
 * - stack_a already ordered
 * - 3 elem or less in stack_a
 * - stack_a already ordered after rotations
 */
int	test_easy_cases(t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;
	size_t	i;

	i = 1;
	if (is_ordered(stack_a, 'd') == 0)
		return (0);
	if (stack_a->nb_elem <= 3)
	{
		sort_three_a(stack_a, cmd_list);
		return (0);
	}
	while (i <= (stack_a->nb_elem))
	{
		rotater(stack_a, cmd_list, "");
		if (is_ordered(stack_a, 'd') == 0)
		{
			while (i > 0)
			{
				new_cmd = ft_lstnew("ra");
				if (!new_cmd)
					return (-1);
				ft_lstadd_back(&cmd_list, new_cmd);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

/* Main push_swap algorithm:
 *
 * 	** PUSH_TO_B **
 * - Define mid_val. 
 * - Find the shortest dist (from top/bottom) to any nb < mid_val.
 * - ra or rra until it is on top stack_a, then pb.
 * - When all nb < mid_val has been pushed to stack_b, define next_mid_val.
 * - Stop and sort stack_a when only 3 elements left.
 * -
 * 	** PUSH_TO_A **
 * - If top stack_b is the next val needed (top stack_a - 1), pa
 * - If it's top stack_b - 1: sb, pa
 * - If not: get_shortest_dist, rb/rrb, pa
 * - Stop and sort stack_b when 3 elements left, then push them to stack_a.
 */
void	ps_sort(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
//	show_stacks(stack_a, stack_b, "A/// Before ps_to_b"); // DEBUG
	ps_to_b(stack_a, stack_b, cmd_list);
//	show_stacks(stack_a, stack_b, "B/// After ps_to_b"); // DEBUG
	ps_to_a(stack_a, stack_b, cmd_list);
//	show_stacks(stack_a, stack_b, "C/// After ps_to_a"); // DEBUG
	return ;
}

int	is_ordered(t_stack *stack, char opt)
{
	size_t	i;

	i = 0;
	if (opt == 'd' && stack->nb_elem > 1)
	{
		while (i < (stack->nb_elem - 1))
		{
			if (stack->index_map[i] < stack->index_map[i + 1])
				return (1);
			i++;
		}
	}
	else if (opt == 'a' && stack->nb_elem > 1)
	{
		while (i < (stack->nb_elem - 1))
		{
			if (stack->index_map[i] > stack->index_map[i + 1])
				return (1);
			i++;
		}
	}
	return (0);
}

// While rotating, check if the next target is on the way. If it is,
// push it to stack_b, then swap.
/* Returns the shortest distance. Its sign indicates the direction:
 * - pos val: from the end of array
 * - neg val: from the start of array
 * This function should NOT be relied on if there is no more nb to be found.
 */
int	get_shortest_dist(t_stack *stack, int min, int max)
{
	int	dist_from_end;
	int	dist_from_start;
	size_t	i;
	int	j;

	i = 1;
//      ft_printf("min = %d - max = %d - stack->index_map[stack->nb_elem - %d]: %d\n", min, max, i, stack->index_map[stack->nb_elem - i]);
	while ((i <= stack->nb_elem) && ((stack->index_map[stack->nb_elem - i] < min) || (stack->index_map[stack->nb_elem - i] >= max)))
	{
//		ft_printf("stack->index_map[stack->nb_elem - %d]: %d\n", i, stack->index_map[stack->nb_elem - i]);
		i++;
	}
	dist_from_end = i - 1;
	if (dist_from_end == 0)
		return (0);
	j = 0;
	while ((j < dist_from_end) && ((stack->index_map[j] < min) || (stack->index_map[j] >= max)))
		j++;
	dist_from_start = j + 1;
//	ft_printf("dist_from_end: %d - dist_from_start: %d\n", dist_from_end, dist_from_start);
	if (dist_from_end < dist_from_start)
		return (dist_from_end);
	else
		return (dist_from_start * (-1));
}
