/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:17:07 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/21 21:21:10 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int      count_tokens(char const *s, char delim)
{
        int     nb_tokens;
        int     i;

        nb_tokens = 0;
        i = 0;
        while (s[i] != '\0')
        {
                while (s[i] == delim && s[i] != '\0')
                        i++;
                if (s[i] != delim && s[i] != '\0')
                {
                        nb_tokens++;
                        while (s[i] != delim && s[i] != '\0')
                                i++;
                }
        }
        return (nb_tokens);
}

int	init_stacks(t_stack *stack_a, t_stack *stack_b, int len, char **str) // len = nb of elem
{
	stack_a->content = store_args(len, str, 'r');
	if (!stack_a->content)
	{
		ft_printf("stack_a not mallocated: terminating...\n");
		return (1);
	}
	stack_a->len = len;
	ft_printf("Stack size: %d\n", stack_a->len);
	stack_a->nb_elem = (size_t)stack_a->len;
	stack_b->content = (int *)ft_calloc(stack_a->len, sizeof(int));
	if (!stack_b->content)
	{
		ft_printf("stack_b not mallocated: terminating...\n");
		return (2);
	}
	stack_b->len = stack_a->len;
	stack_b->nb_elem = 0;
	find_highest(stack_a);
	find_lowest(stack_a);
	return (0);

}

void    find_highest(t_stack *stack)
{
        size_t  i;

        i = 0;
        stack->highest = stack->content[0];
        stack->highest_pos = i;
        while (i < stack->len)
        {
                if (stack->content[i] > stack->highest)
                {
                        stack->highest = stack->content[i];
                        stack->highest_pos = i;
                }
                i++;
        }
        //ft_printf("Highest: %d - index: %d\n", stack->highest, stack->highest_pos); // D*EBUG
}

void    find_lowest(t_stack *stack)
{
        size_t  i;

        i = 0;
        stack->lowest = stack->content[0];
        stack->lowest_pos = i;
        while (i < stack->len)
        {
                if (stack->content[i] < stack->lowest)
                {
                        stack->lowest = stack->content[i];
                        stack->lowest_pos = i;
                }
                i++;
        }
        //ft_printf("Lowest: %d - index: %d\n", stack->lowest, stack->lowest_pos); // DEBUG
}

void    display_solution(t_list *cmd_list)
{
        cmd_list = cmd_list->next;
        while (cmd_list != NULL)
        {
                ft_printf("%s\n", cmd_list->content);
                cmd_list = cmd_list->next;
        }
}
