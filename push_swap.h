/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:27:23 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/17 23:39:59 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* Libraries */
# include "./libft/libft.h"
# include <stdio.h> // DEBUG
# include <unistd.h>

/* Struct */
typedef struct s_stack
{
        size_t  len;
        int                    *content; // the actual content
	int			*index_map; // a copy with index instead
        size_t  nb_elem;
	int	highest;
	int	lowest;
	size_t	highest_pos;
	size_t	lowest_pos;
	char	last_cmd[4];
}                               t_stack;

/* Prototypes */

	// Main logic (push_swap.c)
int	ft_ret(int return_val, char *msg);
int	handle_args(int argc, char **argv, t_stack *stack_a, t_stack *stack_b);
int	init_stacks(t_stack *stack_a, t_stack *stack, int argc, char **argv);
t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b);
void	display_solution(t_list *cmd_list);

	// Parsing logic (ps_args_parser.c)
int     parse_args(int nb_elem, char **args, int i);
int     args_are_all_int(int nb_elem, char **args, int i);
int     args_has_no_duplicate(int nb_elem, char **args, int i);
int     *store_args(int nb_elem, char **args, char opt);

	// push_swap commands (ps_cmd.c)
int    swapper(t_stack *stack, t_list *cmd_list, char *cmd);
int    pusher(t_stack *stack_dst, t_stack *stack_src, t_list *cmd_list, char *cmd);
int    rotater(t_stack *stack, t_list *cmd_list, char *cmd);
int    reverse_rotater(t_stack *stack, t_list *cmd_list, char *cmd);
int    add_cmd(char *cmd, t_list *cmd_list);

	// Solving logic (ps_solver.c)
int	test_easy_cases(t_stack *stack_a, t_list *cmd_list);
void	sort_three_a(t_stack *stack_a, t_list *cmd_list);
void	sort_three_b(t_stack *stack_b, t_list *cmd_list);
void	ps_sort(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list); // Custom sorting algo
void	push_to_b(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list);
void	push_to_a(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list);
int		get_shortest_dist(int *arr, size_t len, int mid_val);

// Utils (ps_utils.c)
int		count_tokens(char const *s, char delim);
int		is_ordered(t_stack *stack);
int		conv_to_index(int *conv_array, int *src_arr, size_t len);
void	find_lowest(t_stack *stack);
void	find_highest(t_stack *stack);


#endif
