/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 08:11:51 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_a(t_stk *stk_a, t_list *cmd_list)
{
	find_highest(stk_a);
	find_lowest(stk_a);
	if (stk_a->nb_elem == 2)
		swapper(stk_a, cmd_list, "sa");
	else if (stk_a->nb_elem == 3)
	{
		if (stk_a->highest_pos == 0)
			swapper(stk_a, cmd_list, "sa");
		else if (stk_a->highest_pos == 1)
			reverse_rotater(stk_a, cmd_list, "rra");
		else if (stk_a->highest_pos == 2)
			rotater(stk_a, cmd_list, "ra");
	}
	if ((stk_a->highest_pos == 1 && stk_a->lowest_pos == 2)
		|| (stk_a->highest_pos == 2 && stk_a->lowest_pos == 0))
		swapper(stk_a, cmd_list, "sa");
}

/* Find the optimal rotation or reverse rotation to bring the given target
 * to the top of the current stk.
 */
void	optimal_rot_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int dist)
{
	if (dist == 0)
		return ;
	while (dist != 0)
	{
		find_highest(stk_b);
		if (dist > 0)
		{
			rotater(stk_a, cmd_list, "ra");
			if ((stk_b->nb_elem > 1)
				&& (stk_b->highest_pos != stk_b->nb_elem -1)
				&& (stk_b->highest_pos < ((stk_b->nb_elem - 1) - dist)))
				rotater(stk_b, cmd_list, "rb");
			dist--;
		}
		else if (dist < 0)
		{
			reverse_rotater(stk_a, cmd_list, "rra");
			if (((stk_b->nb_elem) > 1)
				&& (stk_b->highest_pos != stk_b->nb_elem -1)
				&& ((int)stk_b->highest_pos < (dist * -1)))
				reverse_rotater(stk_b, cmd_list, "rrb");
			dist++;
		}
	}
}

void	find_lowest(t_stk *stk)
{
	size_t	i;

	stk->lowest = stk->i_map[0];
	stk->lowest_pos = 0;
	i = 1;
	while (i < stk->nb_elem)
	{
		if (stk->i_map[i] < stk->lowest)
		{
			stk->lowest = stk->i_map[i];
			stk->lowest_pos = i;
		}
		i++;
	}
}

void	ps_to_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list)
{
	int	pivot;
	int	max;
	int	dist;

	pivot = (int)ft_sqrt_newton((double)stk_a->nb_elem) - 1;
	find_lowest(stk_a);
	max = stk_a->lowest + pivot;
	while ((stk_a->nb_elem > 3) && (is_ordered(stk_a, 'd') != 0))
	{
		while (stk_a->lowest < max)
		{
			dist = get_shortest_dist(stk_a, stk_a->lowest, max);
			optimal_rot_a(stk_a, stk_b, cmd_list, dist);
			pusher(stk_b, stk_a, cmd_list, "pb");
			find_lowest(stk_a);
		}
		max = stk_a->lowest + pivot;
		if (max > (int)stk_a->len - 1)
			max = stk_a->len - 1;
	}
	if (is_ordered(stk_a, 'd') != 0)
		sort_three_a(stk_a, cmd_list);
	return ;
}
