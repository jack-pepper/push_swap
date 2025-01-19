/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/19 15:49:46 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// MOVE TO LIBFT!!!
int     ft_ret(int return_val, char *msg)
{
	int	fd;

	if (msg == NULL)
		return (return_val);
	if (return_val == 0)
		fd = 1;
	else
		fd = 2;
        ft_putstr_fd(msg, fd);
        return (return_val);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	t_list	*cmd_list;

	if (handle_args(argc, argv, &stack_a, &stack_b) != 0)
		return (ft_ret(1, "Error\nhandle_args() failed [main]\n"));
//      show_stacks(&stack_a, &stack_b, "[main, after handle_args]"); // DEBUG
	cmd_list = ft_lstnew("HEAD");
	if (!cmd_list)
		return (ft_ret(1, "Error\nft_lstnew() failed [main]\n"));
//	ft_printf("[main, after init, before ps_solver] b_nb_elem: %s\n", stack_b.nb_elem);
	ps_solver(cmd_list, &stack_a, &stack_b);
	if (cmd_list->next != NULL)
		display_solution(cmd_list);
	//free(stack_a.content);
	//free(stack_b.content);
	//free(cmd_list);
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
		return (ft_ret(1, "Error\nargc c == 1 (req: 2+) [handle_args]\n"));
	if (argc == 2)
	{
		tkn = count_tokens(argv[1], ' ');
		if (tkn < 2)
			return (ft_ret(1, "Error\ntokens < 2 (req: >= 2) [handle_args]\n"));
		tmp = ft_split(argv[1], ' ');
		if (parse_args(tkn, tmp, 0) != 0)
			return (ft_ret(1, "Error\nparse_args failed [handle_args]\n"));
	}
	else if (argc > 2 && (parse_args(argc, argv, 1) != 0))
		return (ft_ret(1, "Error\nparse_args failed [handle_args]\n"));
	stack_a->content = 0;
	if (argc == 2)
		res = init_stacks(stack_a, stack_b, tkn, tmp); // with tmp
	else if (argc > 2)
		res = init_stacks(stack_a, stack_b, argc - 1, &argv[1]); // with argv`v
	if (res != 0)
		return (ft_ret(1, "Error\nstacks not initiated [handle_args]\n"));
//	show_stacks(stack_a, stack_b, "[end handle_args]"); // DEBUG
//      ft_printf("[end handle_args, after init] b_nb_elem: %d\n", stack_b->nb_elem);	
	return (0);
}

int     init_stacks(t_stack *stack_a, t_stack *stack_b, int len, char **str)
{
        stack_a->content = store_args(len, str, 'r');
        if (!stack_a->content)
                return (ft_ret(1, "Error\nstack_a not mallocated\n"));
        stack_a->len = len;
        stack_a->nb_elem = (size_t)stack_a->len;
        stack_b->content = (int *)ft_calloc(stack_a->len, sizeof(int));
        if (!stack_b->content)
                return (ft_ret(2, "Error\nstack_b not mallocated\n"));
        stack_b->len = stack_a->len;
        stack_b->nb_elem = 0;
	stack_a->index_map = (int *)ft_calloc(stack_a->len, sizeof(int));
	if (!stack_a->index_map)
		return (ft_ret(3, "Error\nstack_a->index_map not mallocated\n"));
	conv_to_index(stack_a->index_map, stack_a->content, stack_a->len);
	if (!stack_a->index_map)
		return (ft_ret(4, "Error\nstack_a->index_map not mallocated\n"));	
        find_highest(stack_a);
        find_lowest(stack_a); 
	stack_b->index_map = (int *)ft_calloc(stack_b->len, sizeof(int));
	if (!stack_b->index_map)
		return (ft_ret(5, "Error\nstack_b->index_map not mallocated\n"));
//	ft_printf("[end init] b_nb_elem: %d\n", stack_b->nb_elem);

	return (0);
}

// res : -1 (malloc error) / 0 (sorted) / 1 (tested, still to be sorted)
t_list  *ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
        int     res;

//	show_stacks(stack_a, stack_b, "[ps_solver]"); // DEBUG
        res = test_easy_cases(stack_a, cmd_list);
        if (res == 0)
                return (cmd_list);
	else if (res == -1)
		return (NULL);
//	conv_to_index(stack_a->index_map, stack_a->content, stack_a->len);
//	if (!stack_a->index_map)
//		return (NULL);
	//while ((is_ordered(stack_a, 'd') != 0))
	//{
	ps_sort(stack_a, stack_b, cmd_list);
	//}
	return (cmd_list);
}

void    display_solution(t_list *cmd_list)
{
        char    *cmd;
        char    *next_cmd;

        //ft_printf("cmd 1: %s - cmd 2: %s\n", cmd_list->content, (cmd_list->next)->content);
        cmd_list = cmd_list->next;
        //ft_printf("cmd 1: %s - cmd 2: %s\n", cmd_list->content, (cmd_list->next)->content); // CORRECT! :o
        cmd = (char *)(cmd_list->content);
        while (cmd_list != NULL)
        {
                cmd = (char *)(cmd_list->content);
                if (cmd_list != NULL && cmd_list->next != NULL)
                {
                        next_cmd = (char *)(cmd_list->next)->content;
                        if ((cmd[0] == next_cmd[0])
                                && (cmd[0] != 'p')) // Commands start by same letter except push
                        {
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


// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
