/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/17 23:02:14 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_ordered(t_stack *stack);
void	handle_small_stacks(t_list *cmd_list, t_stack *stack_a);

t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	t_list	*head;
	t_list	*new_cmd;
	
	if (is_ordered(stack_a) == 0)
		return (cmd_list);
	if (stack_a->len <= 3)
	{
		handle_small_stacks(cmd_list, stack_a);
		return (cmd_list);
	}	

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

int	is_ordered(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < (stack->len - 1))
	{
		if (stack->content[i] < stack->content[i + 1])
		{
			ft_printf("is NOT ordered!\n");
			return (1);
		}
		i++;
	}
	ft_printf("is ordered!\n");
	return (0);
}

void	handle_small_stacks(t_list *cmd_list, t_stack *stack_a)
{
	t_list	*new_cmd;

	if (stack_a->len == 2) // If prev test passed, should not be ordered
		new_cmd = ft_lstnew("sa");
	else if (stack_a->len == 3)
	{
		if (stack_a->highest_pos == 0 && stack_a->lowest_pos == 1)
			new_cmd = ft_lstnew("sa");
		else if (stack_a->highest_pos == 1 && stack_a->lowest_pos == 0)
			new_cmd = ft_lstnew("rra");
	}
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
		return ;
}
