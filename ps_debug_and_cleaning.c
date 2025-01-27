/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_debug_and_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:05:55 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/27 12:41:19 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Show the stacks' i_map content.
void	show_stks(t_stk *stk_a, t_stk *stk_b, char *msg)
{
	int	i;
	int	*i_map_a;
	int	*i_map_b;

	i = stk_a->len - 1;
	i_map_a = stk_a->i_map;
	i_map_b = stk_b->i_map;
	ft_printf("%s\n", msg);
	while (i >= 0)
	{
		ft_printf("[a%i]: %d  [b%i]: %d \n", i, i_map_a[i], i, i_map_b[i]);
		i--;
	}
	ft_printf("==============================================\n");
}

// Return a value with "return" after displaying a message.
int	ft_ret(int return_val, char *msg)
{
	int	fd;

	if (msg == NULL)
		return (return_val);
	if (return_val == 0)
		fd = 1;
	else
		fd = 2;
	ft_putendl_fd(msg, fd);
	return (return_val);
}

// Free arr and each element
void	ps_free_all(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

void	ps_exit(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int depth)
{
	if (depth >= 2)
		free(stk_a->content);
	if (depth >= 3)
		free(stk_b->content);
	if (depth >= 4)
		free(stk_a->i_map);
	if (depth >= 5)
		free(stk_b->i_map);
	if (depth >= 6)
		free(cmd_list);
}
