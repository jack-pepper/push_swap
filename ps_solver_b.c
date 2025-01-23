/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 14:04:33 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_b(t_stk *stk_b, t_list *cmd_list)
{
	find_highest(stk_b);
	find_lowest(stk_b);
	if (stk_b->nb_elem == 2 && stk_b->i_map[0] > stk_b->i_map[1])
		swapper(stk_b, cmd_list, "sb");
	else if (stk_b->nb_elem == 3)
	{
		if (stk_b->lowest_pos == 0)
			swapper(stk_b, cmd_list, "sb");
		else if (stk_b->lowest_pos == 1)
			reverse_rotater(stk_b, cmd_list, "rrb");
		else if (stk_b->lowest_pos == 2)
			rotater(stk_b, cmd_list, "rb");
	}
	if ((stk_b->lowest_pos == 1 && stk_b->highest_pos == 2)
		|| (stk_b->lowest_pos == 2 && stk_b->highest_pos == 0))
		swapper(stk_b, cmd_list, "sb");
}

void	optimal_rot_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int tgt_i)
{
	int	top_i;
	int	next_highest;

	top_i = (stk_b->nb_elem - 1);
	next_highest = (stk_b->highest - 1);
	if (tgt_i >= (top_i / 2))
	{
		while (tgt_i < top_i)
		{
			if (stk_b->i_map[stk_b->nb_elem - 1] == next_highest)
			{
				pusher(stk_a, stk_b, cmd_list, "pa");
				top_i--;
			}
			if (stk_b->i_map[stk_b->nb_elem - 1] != stk_b->highest)
			{
				rotater(stk_b, cmd_list, "rb");
				tgt_i++;
			}
		}
	}
	else
	{
		while (tgt_i > -1)
		{
			if (stk_b->i_map[stk_b->nb_elem - 1] == next_highest)
				pusher(stk_a, stk_b, cmd_list, "pa");
			reverse_rotater(stk_b, cmd_list, "rrb");
			tgt_i--;
		}
	}
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

void	ps_to_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list)
{
	while (stk_b->nb_elem > 3)
	{
		find_highest(stk_b);
		optimal_rot_b(stk_a, stk_b, cmd_list, stk_b->highest_pos);
		pusher(stk_a, stk_b, cmd_list, "pa");
		if ((stk_a->nb_elem > 1)
			&& (stk_a->i_map[stk_a->nb_elem - 1]
				> stk_a->i_map[stk_a->nb_elem - 2]))
			swapper(stk_a, cmd_list, "sa");
	}
	if (is_ordered(stk_b, 'a') != 0)
		sort_three_b(stk_b, cmd_list);
	while (stk_b->nb_elem > 0)
		pusher(stk_a, stk_b, cmd_list, "pa");
	return ;
}
