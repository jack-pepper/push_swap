/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:38:43 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 08:15:52 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap.h"

/* Each command function expects a char **cmd.
 * If cmd is "" (empty string), the command will be simply executed. 
 * If cmd is "~a" or "~b" (where '~' is s/p/r/rr depending on the cmd,
 * 	the cmd will be added to the cmd_list.
 */
int	swapper(t_stk *stk, t_list *cmd_list, char *cmd)
{
	size_t	nb;

	nb = stk->nb_elem;
	if (nb < 2)
		return (0);
	ft_swap_ints((&stk->i_map[nb - 1]), &(stk->i_map[nb - 2]));
	if (cmd[0] != '\0')
	{
		if (add_cmd(cmd, cmd_list) != 0)
			return (1);
	}
	return (0);
}

int	pusher(t_stk *stk_dst, t_stk *stk_src, t_list *cmd_list, char *cmd)
{
	size_t	nb_dst;
	size_t	nb_src;

	nb_dst = stk_dst->nb_elem;
	nb_src = stk_src->nb_elem;
	if (nb_src != 0)
	{
		stk_dst->i_map[nb_dst] = stk_src->i_map[nb_src - 1];
		stk_dst->nb_elem++;
		stk_src->i_map[nb_src - 1] = 0;
		stk_src->nb_elem--;
	}
	if (cmd[0] != '\0')
	{
		if (add_cmd(cmd, cmd_list) != 0)
			return (1);
	}
	return (0);
}

int	rotater(t_stk *stk, t_list *cmd_list, char *cmd)
{
	size_t	nb;
	int		*i_map;
	int		temp;

	nb = stk->nb_elem;
	i_map = stk->i_map;
	temp = i_map[nb - 1];
	while (nb > 1)
	{
		i_map[nb - 1] = i_map[nb - 2];
		nb--;
	}
	i_map[0] = temp;
	if (cmd[0] != 0)
	{
		if (add_cmd(cmd, cmd_list) != 0)
			return (1);
	}
	return (0);
}

int	reverse_rotater(t_stk *stk, t_list *cmd_list, char *cmd)
{
	size_t	*nb;
	int		*i_map;
	int		temp;
	size_t	i;

	nb = (&stk->nb_elem);
	i_map = stk->i_map;
	temp = i_map[0];
	i = 0;
	while (i < (*nb - 1))
	{
		i_map[i] = i_map[i + 1];
		i++;
	}
	i_map[*nb - 1] = temp;
	if (cmd[0] != 0)
	{
		if (add_cmd(cmd, cmd_list) != 0)
			return (1);
	}
	return (0);
}

int	add_cmd(char *cmd, t_list *cmd_list)
{
	t_list	*new_cmd;

	new_cmd = ft_lstnew(cmd);
	if (!new_cmd)
		return (1);
	ft_lstadd_back(&cmd_list, new_cmd);
	return (0);
}
