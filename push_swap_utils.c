/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:17:07 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/24 12:58:57 by mmalie           ###   ########.fr       */
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

int	init_stacks(t_stack *stack_a, t_stack *stack_b, int len, char **str)
{
	stack_a->content = store_args(len, str, 'r');
	if (!stack_a->content)
	{
		ft_printf("stack_a not mallocated: terminating...\n");
		return (1);
	}
	stack_a->len = len;
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
}

void    find_lowest(t_stack *stack)
{
        size_t  i;

        stack->lowest = stack->content[0];
        stack->lowest_pos = 0;
	i = 1;
        while (i < stack->nb_elem)
        {
                if (stack->content[i] < stack->lowest)
                {
                        stack->lowest = stack->content[i];
                        stack->lowest_pos = i;
                }
                i++;
        }
}

void	display_solution(t_list *cmd_list)
{
	char	*cmd;
	char	*next_cmd;
	
	//ft_printf("cmd 1: %s - cmd 2: %s\n", cmd_list->content, (cmd_list->next)->content);
	cmd_list = cmd_list->next;	
	//ft_printf("cmd 1: %s - cmd 2: %s\n", cmd_list->content, (cmd_list->next)->content); // CORRECT! :o
	cmd = (char *)(cmd_list->content);
	while (cmd_list != NULL)
	{
		//ft_printf("1\n");
		cmd = (char *)(cmd_list->content);
		if (cmd_list != NULL && cmd_list->next != NULL)
		{
			//ft_printf("2\n");
			next_cmd = (char *)(cmd_list->next)->content;
			if ((cmd[0] == next_cmd[0])
				&& (cmd[0] != 'p')) // Commands start by same letter except push
			{
				//ft_printf("3\n");
				if (cmd[1] != next_cmd[1]) // If diff second letters
				{
					cmd[1] = cmd[0]; // copy the first letter (s or r)
					cmd_list->next = (cmd_list->next)->next; // jump over next instruction
				}
				else if ((cmd[1] == 'r')
					&& (cmd[2] != next_cmd[2])) // reverse rotate case
				{
					cmd[2] = 'r';
					cmd_list->next = (cmd_list->next)->next;
				}
			}	
		}
		//cmd_list = cmd_list->next;
		ft_printf("%s\n", cmd);
		cmd_list = cmd_list->next;
	}
}
