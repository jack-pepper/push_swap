/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/28 12:27:33 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
 * push_swap algorithm:
 *
 * - ps_solver_a.c:
 *	- Calc pivot (sqrt of nb of elem).
 *	- Find lowest and set max at lowest + pivot.
 *	- While stack is unsorted and elements > 3:
 *		- calc shortest dist to any nb in [min, max] range
 *		- calc the optimal move and rotate accordingly to bring
 *			the target to the top of stack_a		
 *			(and push the next lowest if it's on the way)
 *		- push to b
 *	- Sort the remaining 3 elements.
 *
 * - ps_solver_b.c:
 *	- While stack_b > 3 elements: 
 *		- find the highest in stack_b
 *		- calc the optimal move and rotate accordingly to bring
 *			the target to the top of stack_b
 *		 	(and push the next highest if it's ont the way)
 *		- swap stack_a if the new elem is lower than the prev
 *	- Sort the remaining 3 elements, then push them to stack_a.
 *
 */

int	main(int argc, char **argv)
{
	t_stk	stk_a;
	t_stk	stk_b;
	t_list	*cmd_list;

	if ((argc == 1) || (argc == 2 && argv[1][0] == '\0'))
		return (0);
	if ((argc == 2) && ((ft_strnopbrk(argv[1], " -+0123456789") != NULL)
			|| (ft_strnopbrk(argv[1], " ") == NULL)
			|| (argv[1][(int)ft_strlen(argv[1]) - 1] == '-')
		|| (argv[1][(int)ft_strlen(argv[1]) - 1] == '+')))
		return (ft_ret(1, "Error"));
	if (handle_args(argc, argv, &stk_a, &stk_b) != 0)
		return (ft_ret(1, "Error"));
	cmd_list = ft_lstnew("HEAD");
	if (!cmd_list)
	{
		ps_exit(&stk_a, &stk_b, cmd_list, 4);
		return (ft_ret(1, "Error"));
	}
	if (ps_solver(cmd_list, &stk_a, &stk_b) == NULL)
		return (ft_ret(1, "Error"));
	if (cmd_list->next != NULL)
		display_solution(cmd_list);
	ps_exit(&stk_a, &stk_b, cmd_list, 6);
}

/* Parse the arguments to check their validity (a list of int without double)
 * and call init_stks with the right parameters, depending on the format of
 * the input (numbers or a string of numbers).
 */
int	handle_args(int argc, char **argv, t_stk *stk_a, t_stk *stk_b)
{
	char	**tmp;
	char	**trimmed_args;
	int		res;
	int		tkn;

	trimmed_args = NULL;
	if ((argc > 2) && (parse_args(argc - 1, &argv[1], 0, &trimmed_args) != 0))
		return (1);
	stk_a->content = 0;
	if (argc == 2)
	{
		tkn = count_tokens(argv[1], ' ');
		tmp = ft_split(argv[1], ' ');
		if (parse_args(tkn, tmp, 0, &trimmed_args) != 0)
		{
			ps_free_all(tmp);
			return (1);
		}
		res = init_stks(stk_a, stk_b, tkn, trimmed_args);
		ps_free_all(tmp);
	}
	else
		res = init_stks(stk_a, stk_b, argc - 1, trimmed_args);
	return (res);
}

int	init_stks(t_stk *stk_a, t_stk *stk_b, int len, char **trimmed_args)
{
	stk_a->content = store_args(len, trimmed_args, 'r');
	if (!stk_a->content)
		return (1);
	stk_a->len = len;
	stk_a->nb_elem = (size_t)stk_a->len;
	stk_b->content = (int *)ft_calloc(stk_a->len, sizeof(int));
	if (!stk_b->content)
		return (2);
	stk_b->len = stk_a->len;
	stk_b->nb_elem = 0;
	stk_a->i_map = (int *)ft_calloc(stk_a->len, sizeof(int));
	if (!stk_a->i_map)
		return (3);
	conv_to_index(stk_a->i_map, stk_a->content, stk_a->len);
	find_highest(stk_a);
	find_lowest(stk_a);
	stk_b->i_map = (int *)ft_calloc(stk_b->len, sizeof(int));
	if (!stk_b->i_map)
		return (4);
	return (0);
}

// res : -1 (malloc error) / 0 (sorted) / 1 (tested, still to be sorted)
t_list	*ps_solver(t_list *cmd_list, t_stk *stk_a, t_stk *stk_b)
{
	int	res;

	res = test_easy_cases(stk_a, cmd_list, 1);
	if (res == 0)
		return (cmd_list);
	else if (res == -1)
	{
		ps_exit(stk_a, stk_b, cmd_list, 6);
		return (NULL);
	}
	if (ps_sort(stk_a, stk_b, cmd_list) != 0)
	{
		ps_exit(stk_a, stk_b, cmd_list, 6);
		return (NULL);
	}
	return (cmd_list);
}

void	display_solution(t_list *cmd_list)
{
	char	*cmd;
	char	*next_cmd;

	cmd_list = cmd_list->next;
	cmd = (char *)(cmd_list->content);
	while (cmd_list != NULL)
	{
		cmd = (char *)(cmd_list->content);
		if (cmd_list->next != NULL)
		{
			next_cmd = (char *)(cmd_list->next)->content;
			if ((cmd[0] == next_cmd[0]) && (cmd[0] != 'p'))
				try_merge_cmds(&cmd_list, cmd, next_cmd);
			else
			{
				ft_printf("%s\n", cmd);
				clean_cmd_and_set_next(&cmd_list, 0);
			}
		}
		else
		{
			ft_printf("%s\n", cmd);
			clean_cmd_and_set_next(&cmd_list, 0);
		}
	}
}
