/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/17 21:20:36 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	t_list	*head;
	t_list	*new_cmd;

	new_cmd = ft_lstnew("XXX");
	if (!new_cmd)
		return (NULL);
	ft_lstadd_back(&cmd_list, new_cmd);
	head = cmd_list;
	while (head != NULL)
        {
                ft_printf("%s\n", (char *)head->content);
                head = head->next;
        }
	ft_printf("stack_a.len: %d - stack_b.len: %d\n", stack_a->len, stack_b->len);
	return (cmd_list);
}
