/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/18 09:41:34 by mmalie           ###   ########.fr       */
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
	t_stack	stack_a;
	t_stack	stack_b;
	t_list	*cmd_list;

	if (argc < 3)
		return (1);
	res = parse_args(argc, argv);
	if (res != 0)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	stack_a.content = 0;
	res = init_stacks(&stack_a, &stack_b, argc, argv);
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

	/* TEST
	int *stk_a = stack_a.content;
	int *stk_b = stack_b.content;
	ft_printf("Before operation: \n");
	ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
	ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
	ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
	ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
	ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
	ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);
	*/

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
