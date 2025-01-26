/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/26 20:47:07 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_three_a(t_stk *stk_a, t_list *cmd_list)
{
	int	res;

	find_highest(stk_a);
	find_lowest(stk_a);
	res = 0;
	if (stk_a->nb_elem == 2)
		res = swapper(stk_a, cmd_list, "sa");
	else if (stk_a->nb_elem == 3)
	{
		if (stk_a->highest_pos == 0)
			res = swapper(stk_a, cmd_list, "sa");
		else if (stk_a->highest_pos == 1)
			res = reverse_rotater(stk_a, cmd_list, "rra");
		else if (stk_a->highest_pos == 2)
			res = rotater(stk_a, cmd_list, "ra");
	}
	if (res != 0)
		return (1);
	if ((stk_a->highest_pos == 1 && stk_a->lowest_pos == 2)
		|| (stk_a->highest_pos == 2 && stk_a->lowest_pos == 0))
		res = swapper(stk_a, cmd_list, "sa");
	return (res);
}

/* Find the optimal rotation or reverse rotation to bring the given target
 * to the top of the current stk.
 */
int	optimal_rot_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int dist)
{
	if (dist == 0)
		return (0);
	while (dist != 0)
	{
		find_highest(stk_b);
		if (dist > 0)
		{
			if (rotater(stk_a, cmd_list, "ra") != 0)
				return (1);
			if ((stk_b->nb_elem > 1)
				&& (stk_b->highest_pos != stk_b->nb_elem -1)
				&& (stk_b->highest_pos < ((stk_b->nb_elem - 1) - dist)))
			{
				if (rotater(stk_b, cmd_list, "rb") != 0)
					return (1);
			}
			dist--;
		}
		else if (dist < 0)
		{
			if (reverse_rotater(stk_a, cmd_list, "rra") != 0)
				return (1);
			if (((stk_b->nb_elem) > 1)
				&& (stk_b->highest_pos != stk_b->nb_elem -1)
				&& ((int)stk_b->highest_pos < (dist * -1)))
			{
				if (reverse_rotater(stk_b, cmd_list, "rrb") != 0)
					return (1);
			}
			dist++;
		}
	}
	return (0);
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

/* The pivot 21 is the magic value that allows sorting in less than 700 moves
 * for an array of 100 numbers.
 */
int	ps_to_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list)
{
	int	pivot;
	int	max;
	int	dist;

	pivot = (int)ft_sqrt_newton((double)stk_a->nb_elem) - 1;
	if (stk_a->len >= 30 && stk_a->len <= 110)
		pivot = 21;
	find_lowest(stk_a);
	max = stk_a->lowest + pivot;
	while ((stk_a->nb_elem > 3) && (is_ordered(stk_a, 'd') != 0))
	{
		while (stk_a->lowest < max)
		{
			dist = get_shortest_dist(stk_a, stk_a->lowest, max);
			if ((optimal_rot_a(stk_a, stk_b, cmd_list, dist) != 0)
				|| (pusher(stk_b, stk_a, cmd_list, "pb") != 0))
				return (1);
			find_lowest(stk_a);
		}
		max = stk_a->lowest + pivot;
		if (max > (int)stk_a->len - 1)
			max = stk_a->len - 1;
	}
	if (is_ordered(stk_a, 'd') != 0)
	{
		if (sort_three_a(stk_a, cmd_list) != 0)
			return (1);
	}
	return (0);
}
