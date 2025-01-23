/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:27:23 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 14:32:10 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* Libraries */
# include "./libft/libft.h"
# include <stdio.h> // DEBUG
# include <unistd.h>

/* Struct */
typedef struct s_stk
{
	size_t	len;
	int		*content; // the actual content
	int		*i_map; // a copy with index instead
	size_t	nb_elem;
	int		highest;
	int		lowest;
	size_t	highest_pos;
	size_t	lowest_pos;
	char	last_cmd[4];
}		t_stk;

/* Prototypes */

	// Main logic (push_swap.c)
int		handle_args(int argc, char **argv, t_stk *stk_a, t_stk *stk_b);
int		init_stks(t_stk *stk_a, t_stk *stk, int argc, char **argv);
t_list	*ps_solver(t_list *cmd_list, t_stk *stk_a, t_stk *stk_b);
void	display_solution(t_list *cmd_list);

	// Parsing logic (ps_args_parser.c)
int		parse_args(int nb_elem, char **args, int i);
int		args_are_all_int(int nb_elem, char **args, int i);
int		check_int_limits(char **args, int i, int j);
int		args_has_no_duplicate(int nb_elem, char **args, int i);
int		*store_args(int nb_elem, char **args, char opt);

	// push_swap commands (ps_cmd.c)
int		swapper(t_stk *stk, t_list *cmd_list, char *cmd);
int		pusher(t_stk *stk_dst, t_stk *stk_src, t_list *cmd_list, char *cmd);
int		rotater(t_stk *stk, t_list *cmd_list, char *cmd);
int		reverse_rotater(t_stk *stk, t_list *cmd_list, char *cmd);
int		add_cmd(char *cmd, t_list *cmd_list);

	// Solving logic (ps_solver.c)
int		test_easy_cases(t_stk *stk_a, t_list *cmd_list, size_t i);
void	ps_sort(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list);
int		is_ordered(t_stk *stk, char opt);
int		get_shortest_dist(t_stk *stk, int min, int max);
void	try_merge_cmds(t_list **cmd_list, char *cmd, char *next_cmd);

	// Solving logic (ps_solver_a.c)
void	sort_three_a(t_stk *stk_a, t_list *cmd_list);
void	optimal_rot_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int dist);
void	find_lowest(t_stk *stk);
void	ps_to_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list);

	// Solving logic (ps_solver_b.c)
void	sort_three_b(t_stk *stk_b, t_list *cmd_list);
void	optimal_rot_b(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list, int tgt_i);
void	find_highest(t_stk *stk);
void	ps_to_a(t_stk *stk_a, t_stk *stk_b, t_list *cmd_list);

// Utils (ps_utils.c)
int		ft_ret(int return_val, char *msg);
int		count_tokens(char const *s, char delim);
int		conv_to_index(int *conv_array, int *src_arr, size_t len);
double	ft_sqrt_newton(double number);
void	clean_cmd_and_set_next(t_list **cmd_list, int jump);
//void	show_stks(t_stk *stk_a, t_stk *stk_b, char *msg);

#endif
