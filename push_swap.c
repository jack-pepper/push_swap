/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/22 20:26:25 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO NEXT:
 * -  
 * -
 * */

#include "push_swap.h"
/*
#include "./libft/libft.h"
#include <unistd.h>
*/


int	main(int argc, char **argv)
{
	int	res;
	char	**tmp;
	int	tkn;
	t_stack	stack_a;
	t_stack	stack_b;
	t_list	*cmd_list;

	if (argc == 1)
		return (1); // or error?
	if (argc == 2)
	{
		tkn = count_tokens(argv[1], ' ');
		if (tkn < 2)
			return (1); // or error?
		tmp = ft_split(argv[1], ' ');
		res = parse_args(tkn, tmp, 0);
	}
	else if (argc > 2)
		res = parse_args(argc, argv, 1);
	if (res != 0)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	stack_a.content = 0;
	if (argc == 2)
		res = init_stacks(&stack_a, &stack_b, tkn, tmp); // with tmp
	else if (argc > 2)
		res = init_stacks(&stack_a, &stack_b, argc - 1, &argv[1]); // with argv`v
	if (res != 0)
	{
		write(2, "Error\n", 7);
		//if (res == 2)
		//	free(stack_a.content);
		return (1);
	}
	cmd_list = ft_lstnew("HEAD");
	if (!cmd_list)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	ps_solver(cmd_list, &stack_a, &stack_b);
	display_solution(cmd_list);
	//free(stack_a.content);
	//free(stack_b.content);
	//free(cmd_list);
	return (0);
}

// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
