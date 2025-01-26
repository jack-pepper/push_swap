/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/26 20:46:05 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sort_three_b(t_stk *stk_b, t_list *cmd_list)
{
	int	res;
	
	res = 0;
	find_highest(stk_b);
	find_lowest(stk_b);
	if (stk_b->nb_elem == 2 && stk_b->i_map[0] > stk_b->i_map[1])
		res = swapper(stk_b, cmd_list, "sb");
	else if (stk_b->nb_elem == 3)
	{
		if (stk_b->lowest_pos == 0)
			res = swapper(stk_b, cmd_list, "sb");
		else if (stk_b->lowest_pos == 1)
			res = reverse_rotater(stk_b, cmd_list, "rrb");
		else if (stk_b->lowest_pos == 2)
			res = rotater(stk_b, cmd_list, "rb");
	}
	if (res != 0)
		return (1);
	if ((stk_b->lowest_pos == 1 && stk_b->highest_pos == 2)
		|| (stk_b->lowest_pos == 2 && stk_b->highest_pos == 0))
		res = swapper(stk_b, cmd_list, "sb");
	return (res);
}

int	optimal_rot_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int tgt_i)
{
	int	top_i;
	int	next_highest;

	top_i = (stk_b->nb_elem - 1);
	next_highest = (stk_b->highest - 1);
	if (tgt_i >= (top_i / 2))
	{
		if (rot_and_push(stk_a, stk_b, cmd_list, tgt_i) != 0)
			return (1);
	}
	else
	{
		while (tgt_i > -1)
		{
			if (stk_b->i_map[stk_b->nb_elem - 1] == next_highest)
			{	
				if (pusher(stk_a, stk_b, cmd_list, "pa") != 0)
					return (1);
			}
			if (reverse_rotater(stk_b, cmd_list, "rrb") != 0)
				return (1);
			tgt_i--;
		}
	}
	return (0);
}

int	rot_and_push(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int tgt_i)
{
	int	top_i;
	int	next_highest;

	top_i = (stk_b->nb_elem - 1);
	next_highest = (stk_b->highest - 1);
	while (tgt_i < top_i)
	{
		if (stk_b->i_map[stk_b->nb_elem - 1] == next_highest)
		{
			if (pusher(stk_a, stk_b, cmd_list, "pa") != 0)
				return (1);
			top_i--;
		}
		if (stk_b->i_map[stk_b->nb_elem - 1] != stk_b->highest)
		{
			if (rotater(stk_b, cmd_list, "rb") != 0)
				return (1);
			tgt_i++;
		}
	}
	return (0);
}

void	find_highest(t_stk *stk)
{
	size_t	i;

	i = 0;
	stk->highest = stk->i_map[0];
	stk->highest_pos = i;
	while (i < stk->len)
	{
		if (stk->i_map[i] > stk->highest)
		{
			stk->highest = stk->i_map[i];
			stk->highest_pos = i;
		}
		i++;
	}
}

int	ps_to_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list)
{
	while (stk_b->nb_elem > 3)
	{
		find_highest(stk_b);
		if (optimal_rot_b(stk_a, stk_b, cmd_list, stk_b->highest_pos) != 0)
			return (1);
		if (pusher(stk_a, stk_b, cmd_list, "pa") != 0)
			return (1);
		if ((stk_a->nb_elem > 1)
			&& (stk_a->i_map[stk_a->nb_elem - 1]
				> stk_a->i_map[stk_a->nb_elem - 2]))
		{
			if (swapper(stk_a, cmd_list, "sa") != 0)
				return (1);
		}
	}
	if (is_ordered(stk_b, 'a') != 0)
	{	
		if (sort_three_b(stk_b, cmd_list) != 0)
			return (1);
	}
	while (stk_b->nb_elem > 0)
	{
		if (pusher(stk_a, stk_b, cmd_list, "pa") != 0)
			return (1);
	}
	return (0);
}
