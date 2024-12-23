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
        int                    *content;
        size_t  nb_elem;
	int	highest;
	int	lowest;
	size_t	highest_pos;
	size_t	lowest_pos;
	char	last_cmd[4];
}                               t_stack;

/* Prototypes */

// Parsing logic
int     error_check(int argc, char **argv);
int     parse_args(int nb_elem, char **args, int i);
int     *store_args(int nb_elem, char **args, char opt);
int     args_are_all_int(int nb_elem, char **args, int i);
int     args_has_no_duplicate(int nb_elem, char **args, int i);

// Swap logic
void	swapper(t_stack *stack);
void	sa(t_stack *stack_a, t_list *cmd_list);
void	sb(t_stack *stack_b, t_list *cmd_list);
void	ss(t_stack *stack_a, t_stack *stack_b);

// Push logic
void	pusher(t_stack *stack_dst, t_stack *stack_src);
void	pa(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list);
void	pb(t_stack *stack_b, t_stack *stack_a, t_list *cmd_list);

// Rotate logic
void	rotater(t_stack *stack);
void	ra(t_stack *stack_a, t_list *cmd_list);
void	rb(t_stack *stack_b, t_list *cmd_list);

// Reverse rotate logic
void	reverse_rotater(t_stack *stack);
void	rra(t_stack *stack_a, t_list *cmd_list);
void	rrb(t_stack *stack_b, t_list *cmd_list);
void	rrr(t_stack *stack_a, t_stack *stack_b);

// Utils
int		count_tokens(char const *s, char delim);
int	init_stacks(t_stack *stack_a, t_stack *stack, int argc, char **argv);
void	find_highest(t_stack *stack);
void	find_lowest(t_stack *stack);
void	display_solution(t_list *cmd_list);

// Solver
t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b);
int		is_ordered(t_stack *stack);
void	handle_small_stack(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b);
void	rotate_lowest_and_push(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list);

#endif
