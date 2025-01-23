/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 10:28:14 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Test easy cases:
 * - stk_a already ordered
 * - 3 elem or less in stk_a
 * - stk_a already ordered after rotations
 * i must be initialized to 1. It's passed as a parameter to keep the function
 * shorter than 25 lines (norm).
 */
int	test_easy_cases(t_stk *stk_a, t_list *cmd_list, size_t i)
{
	if (is_ordered(stk_a, 'd') == 0)
		return (0);
	if (stk_a->nb_elem <= 3)
	{
		sort_three_a(stk_a, cmd_list);
		return (0);
	}
	while (i <= (stk_a->nb_elem))
	{
		rotater(stk_a, cmd_list, "");
		if (is_ordered(stk_a, 'd') == 0)
		{
			while (i > 0)
			{
				if (add_cmd("ra", cmd_list) != 0)
					return (-1);
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
 * - ra or rra until it is on top stk_a, then pb.
 * - When all nb < mid_val has been pushed to stk_b, define next_mid_val.
 * - Stop and sort stk_a when only 3 elements left.
 * -
 * 	** PUSH_TO_A **
 * - If top stk_b is the next val needed (top stk_a - 1), pa
 * - If it's top stk_b - 1: sb, pa
 * - If not: get_shortest_dist, rb/rrb, pa
 * - Stop and sort stk_b when 3 elements left, then push them to stk_a.
 */
void	ps_sort(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list)
{
//	show_stks(stk_a, stk_b, "A/// Before ps_to_b"); // DEBUG
	ps_to_b(stk_a, stk_b, cmd_list);
//	show_stks(stk_a, stk_b, "B/// After ps_to_b"); // DEBUG
	ps_to_a(stk_a, stk_b, cmd_list);
//	show_stks(stk_a, stk_b, "C/// After ps_to_a"); // DEBUG
	return ;
}

int	is_ordered(t_stk *stk, char opt)
{
	size_t	i;

	i = 0;
	if (opt == 'd' && stk->nb_elem > 1)
	{
		while (i < (stk->nb_elem - 1))
		{
			if (stk->i_map[i] < stk->i_map[i + 1])
				return (1);
			i++;
		}
	}
	else if (opt == 'a' && stk->nb_elem > 1)
	{
		while (i < (stk->nb_elem - 1))
		{
			if (stk->i_map[i] > stk->i_map[i + 1])
				return (1);
			i++;
		}
	}
	return (0);
}

// While rotating, check if the next target is on the way. If it is,
// push it to stk_b, then swap.
/* Returns the shortest distance. Its sign indicates the direction:
 * - pos val: from the end of array
 * - neg val: from the start of array
 * This function should NOT be relied on if there is no more nb to be found.
 */
int	get_shortest_dist(t_stk *stk, int min, int max)
{
	int		dist_from_end;
	int		dist_from_start;
	size_t	i;
	int		j;

	i = 1;
	while ((i <= stk->nb_elem)
		&& ((stk->i_map[stk->nb_elem - i] < min)
			|| (stk->i_map[stk->nb_elem - i] >= max)))
		i++;
	dist_from_end = i - 1;
	if (dist_from_end == 0)
		return (0);
	j = 0;
	while ((j < dist_from_end)
		&& ((stk->i_map[j] < min)
			|| (stk->i_map[j] >= max)))
		j++;
	dist_from_start = j + 1;
	if (dist_from_end < dist_from_start)
		return (dist_from_end);
	else
		return (dist_from_start * (-1));
}

void	try_merge_cmds(t_list **cmd_list, char *cmd, char *next_cmd)
{
	char	temp_cmd[4];

	ft_memset(temp_cmd, '0', 4);
	if (cmd[1] != next_cmd[1])
	{
		temp_cmd[0] = cmd[0];
		temp_cmd[1] = cmd[0];
		temp_cmd[2] = '\0';
		ft_printf("%s\n", temp_cmd);
		clean_cmd_and_set_next(cmd_list, 1);
		//*cmd_list = (*cmd_list)->next->next;
	}
	else if ((cmd[1] == 'r') && (cmd[2] != next_cmd[2]))
	{
		ft_printf("%s\n", "rrr");	
		clean_cmd_and_set_next(cmd_list, 1);
	//	*cmd_list = (*cmd_list)->next->next;
	}
	else
	{
		ft_printf("%s\n", cmd);
		clean_cmd_and_set_next(cmd_list, 0);
		//*cmd_list = (*cmd_list)->next;
	//	free(cmd);
	}
}
