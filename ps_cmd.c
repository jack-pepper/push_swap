/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:38:43 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/21 20:06:06 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap.h"

/* Each command function expects a char **cmd.
 * If cmd is "" (empty string), the command will be simply executed. 
 * If cmd is "~a" or "~b" (where '~' is s/p/r/rr depending on the cmd,
 * 	the cmd will be added to the cmd_list.
 */
int    swapper(t_stack *stack, t_list *cmd_list, char *cmd)
{
        size_t	nb;

        nb = stack->nb_elem;
        if (nb < 2)
                return (0);
        ft_swap_ints((&stack->index_map[nb - 1]), &(stack->index_map[nb - 2]));
	if (cmd[0] != '\0')
        	add_cmd(cmd, cmd_list);
	return (0);
}

int    pusher(t_stack *stack_dst, t_stack *stack_src, t_list *cmd_list, char *cmd)
{
        size_t  nb_dst;
        size_t  nb_src;

        nb_dst = stack_dst->nb_elem;
        nb_src = stack_src->nb_elem;
        if (nb_src != 0)
        {
                stack_dst->index_map[nb_dst] = stack_src->index_map[nb_src - 1];
                stack_dst->nb_elem++;
                stack_src->index_map[nb_src - 1] = 0;
                stack_src->nb_elem--;
        }
	if (cmd[0] != '\0')
        	add_cmd(cmd, cmd_list);
	return (0);
}

int    rotater(t_stack *stack, t_list *cmd_list, char *cmd)
{
        size_t  nb;
        int             *stk;
        int             temp;

        nb = stack->nb_elem;
        stk = stack->index_map;
        temp = stk[nb - 1];
        while (nb > 1)
        {
                stk[nb - 1] = stk[nb - 2];
                nb--;
        }
        stk[0] = temp;
	if (cmd[0] != 0)
	{
		if (add_cmd(cmd, cmd_list) != 0)
        		return (1);
	}
	return (0);
}

int    reverse_rotater(t_stack *stack, t_list *cmd_list, char *cmd)
{
        size_t  *nb;
        int             *stk;
        int             temp;
        size_t  i;

        nb = (&stack->nb_elem);
        stk = stack->index_map;
        temp = stk[0];
        i = 0;
        while (i < (*nb - 1))
        {
                stk[i] = stk[i + 1];
                i++;
        }
        stk[*nb - 1] = temp;
	if (cmd[0] != 0)
	{
        	if (add_cmd(cmd, cmd_list) != 0) // Do the same in each cmd_function!
			return (1);
	}
	return (0);
}

int	add_cmd(char *cmd, t_list *cmd_list)
{
	t_list *new_cmd;

	new_cmd = ft_lstnew(cmd);
	if (!new_cmd)
		return (1);
	ft_lstadd_back(&cmd_list, new_cmd);
	return (0);
}
