/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:05:34 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/17 23:06:00 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO NEXT:
 * - Define other cases for handling small stacks 
 * -
 * */

#include "push_swap.h"
/*
#include "./libft/libft.h"
#include <stdio.h> // DEBUG!!!
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
	// write(1, "Input is OK!\n", 14);
	stack_a.content = 0; // INIT FOR DEBUG
	stack_a.highest_pos = 0; // INIT FOR DEBUG
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
	while (cmd_list != NULL)
	{
		ft_printf("%s\n", cmd_list->content);
		cmd_list = cmd_list->next;
	}
//	ft_printf("stack_a.highest_pos: %d\n", stack_a.highest_pos);
	
//	ft_printf("cmd_list.content[0]: %s\n", (char *)cmd_list->content[0]);

	//cmd_list = ft_lstnew("");
	//if (!cmd_list)
	//{
		//	ft_printf("cmd_list not mallocated: terminating...\n");
		//	return (1);
		//}
		// TEST
	
		int *stk_a = stack_a.content;
		int *stk_b = stack_b.content;
		ft_printf("Before operation: \n");
		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("rra! ");
		rra(stack_a);

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);	
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);
/*
		ft_printf("push b! ");	
		pb(&stack_b, &stack_a);
		
		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("push b! ");
		pb(&stack_b, &stack_a);

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("push a! ");
		pusher(&stack_a, &stack_b);

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("swap a! ");
		swapper(stack_a);	

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("swap a! ");
		swapper(stack_a);	
		
		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("swap b! ");
		swapper(stack_b);

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("rotate a! ");
		rotater(stack_a);	

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("rotate b! ");
		rotater(stack_b);
	
		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);

		ft_printf("reverse_rotate b!");
		reverse_rotater(stack_b);

		ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a.nb_elem, stack_b.nb_elem);
		ft_printf("After operation:\n");
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);
		// END TEST

	ft_printf("%s - %s - %s\n", cmd_list[0], cmd_list[1], cmd_list[2]);
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
