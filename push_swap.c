/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 00:43:16 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	t_list	*cmd_list;

	if (argc == 1)
		return (1);
	if (handle_args(argc, argv, &stack_a, &stack_b) != 0)
		return (ft_ret(1, "Error"));
	cmd_list = ft_lstnew("HEAD");
	if (!cmd_list)
		return (ft_ret(1, "Error"));
	ps_solver(cmd_list, &stack_a, &stack_b);
	if (cmd_list->next != NULL)
		display_solution(cmd_list);
	free(stack_a.content);
	free(stack_a.index_map);
	free(stack_b.content);
	free(stack_b.index_map);
	free(cmd_list);
	//while(cmd_list != NULL)
	//{
	//	free(cmd_list->content);
	//	cmd_list = cmd_list->next;
	//}	
	return (0);
}

/* Parse the arguments to check their validity (a list of int without double)
 * and call init_stacks with the right parameters, depending on the format of
 * the input (numbers or a string of numbers).
 */
int	handle_args(int argc, char **argv, t_stack *stack_a, t_stack *stack_b)
{
	char	**tmp;
	int		res;
	int		tkn;

	if (argc == 1)
		return (1);
	if (argc == 2)
	{
		tkn = count_tokens(argv[1], ' ');
		tmp = ft_split(argv[1], ' ');
		if (parse_args(tkn, tmp, 0) != 0)
			return (1);
	}
	else if (argc > 2 && (parse_args(argc, argv, 1) != 0))
		return (1);
	stack_a->content = 0;
	if (argc == 2)
		res = init_stacks(stack_a, stack_b, tkn, tmp);
	else if (argc > 2)
		res = init_stacks(stack_a, stack_b, argc - 1, &argv[1]);
	if (res != 0)
		return (1);
	return (0);
}

int	init_stacks(t_stack *stack_a, t_stack *stack_b, int len, char **str)
{
	stack_a->content = store_args(len, str, 'r');
	if (!stack_a->content)
		return (1);
	stack_a->len = len;
	stack_a->nb_elem = (size_t)stack_a->len;
	stack_b->content = (int *)ft_calloc(stack_a->len, sizeof(int));
	if (!stack_b->content)
		return (1);
	stack_b->len = stack_a->len;
	stack_b->nb_elem = 0;
	stack_a->index_map = (int *)ft_calloc(stack_a->len, sizeof(int));
	if (!stack_a->index_map)
		return (1);
	conv_to_index(stack_a->index_map, stack_a->content, stack_a->len);
	if (!stack_a->index_map)
		return (1);
	find_highest(stack_a);
	find_lowest(stack_a);
	stack_b->index_map = (int *)ft_calloc(stack_b->len, sizeof(int));
	if (!stack_b->index_map)
		return (1);
	return (0);
}

// res : -1 (malloc error) / 0 (sorted) / 1 (tested, still to be sorted)
t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	int	res;

	res = test_easy_cases(stack_a, cmd_list);
	if (res == 0)
		return (cmd_list);
	else if (res == -1)
		return (NULL);
	ps_sort(stack_a, stack_b, cmd_list);
	return (cmd_list);
}

void	display_solution(t_list *cmd_list)
{
	char	*cmd;
	char	*next_cmd;
	char	temp_cmd[4];

	cmd_list = cmd_list->next;
	cmd = (char *)(cmd_list->content);
	while (cmd_list != NULL)
	{
		cmd = (char *)(cmd_list->content);
		if (cmd_list->next != NULL)
		{
			next_cmd = (char *)(cmd_list->next)->content;
			if ((cmd[0] == next_cmd[0]) && (cmd[0] != 'p'))
			{
				ft_memset(temp_cmd, '0', 4);
				if (cmd[1] != next_cmd[1])
				{
					temp_cmd[0] = cmd[0];
					temp_cmd[1] = cmd[0];
					temp_cmd[2] = '\0';
					ft_printf("%s\n", temp_cmd);
					cmd_list = cmd_list->next->next;
				}
				else if ((cmd[1] == 'r') && (cmd[2] != next_cmd[2]))
				{
					ft_printf("%s\n", "rrr");
					cmd_list = cmd_list->next->next;
				}
				else
				{
				//temp = ft_lstnew(temp_cmd);
				//if (!temp)
				//	return; // ERROR TO MANAGE WITH A RET VAL!
				//temp->next = (cmd_list->next)->next;
					ft_printf("%s\n", cmd);
					cmd_list = cmd_list->next;
				}
			}
			else
			{
				ft_printf("%s\n", cmd);
				cmd_list = cmd_list->next;
			}
		}
		else
		{
			ft_printf("%s\n", cmd);
			cmd_list = cmd_list->next;
		//free(cmd);
		//temp = cmd_list;	
		//cmd_list = cmd_list->next;
                //free(temp);
		}
	}
}
