/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 10:32:57 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stk	stk_a;
	t_stk	stk_b;
	t_list	*cmd_list;

	if (argc == 1)
		return (1);
	if (handle_args(argc, argv, &stk_a, &stk_b) != 0)
		return (ft_ret(1, "Error"));
	cmd_list = ft_lstnew("HEAD");
	if (!cmd_list)
		return (ft_ret(1, "Error"));
	ps_solver(cmd_list, &stk_a, &stk_b);
	if (cmd_list->next != NULL)
		display_solution(cmd_list);
	free(stk_a.content);
	free(stk_a.i_map);
	free(stk_b.content);
	free(stk_b.i_map);
	free(cmd_list);
	//while(cmd_list != NULL)
	//{
	//	free(cmd_list->content);
	//	cmd_list = cmd_list->next;
	//}	
	return (0);
}

/* Parse the arguments to check their validity (a list of int without double)
 * and call init_stks with the right parameters, depending on the format of
 * the input (numbers or a string of numbers).
 */
int	handle_args(int argc, char **argv, t_stk *stk_a, t_stk *stk_b)
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
	stk_a->content = 0;
	if (argc == 2)
		res = init_stks(stk_a, stk_b, tkn, tmp);
	else if (argc > 2)
		res = init_stks(stk_a, stk_b, argc - 1, &argv[1]);
	if (res != 0)
		return (1);
	return (0);
}

int	init_stks(t_stk *stk_a, t_stk *stk_b, int len, char **str)
{
	stk_a->content = store_args(len, str, 'r');
	if (!stk_a->content)
		return (1);
	stk_a->len = len;
	stk_a->nb_elem = (size_t)stk_a->len;
	stk_b->content = (int *)ft_calloc(stk_a->len, sizeof(int));
	if (!stk_b->content)
		return (1);
	stk_b->len = stk_a->len;
	stk_b->nb_elem = 0;
	stk_a->i_map = (int *)ft_calloc(stk_a->len, sizeof(int));
	if (!stk_a->i_map)
		return (1);
	conv_to_index(stk_a->i_map, stk_a->content, stk_a->len);
	if (!stk_a->i_map)
		return (1);
	find_highest(stk_a);
	find_lowest(stk_a);
	stk_b->i_map = (int *)ft_calloc(stk_b->len, sizeof(int));
	if (!stk_b->i_map)
		return (1);
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
		return (NULL);
	ps_sort(stk_a, stk_b, cmd_list);
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
			{
				try_merge_cmds(&cmd_list, cmd, next_cmd);
				continue ;
			}
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
