
/* TO DO:
 * - do last parsing tests
 * - store input as an int array?
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

	if (argc < 3)
	{
		return (1);
	}
	else
	{
		res = parse_args(argc, argv);
		if (res != 0)
		{
			write(2, "Error\n", 7);
			return (1);
		}
		write(1, "Input is OK!\n", 14);
		stack_a.content = store_args(argc, argv, 'r');
		if (!stack_a.content)
		{
			ft_printf("stack_a not mallocated: terminating...\n");
			return (1);
		}
		stack_a.len = argc - 1;
		ft_printf("Stack size: %d\n", stack_a.len);
		stack_a.nb_elem = stack_a.len;
		stack_b.content = (int *)ft_calloc(stack_a.len, sizeof(int));
		if (!stack_b.content)
		{
			ft_printf("stack_b not mallocated: terminating...\n");
			return (1);
		}
		stack_b.len = stack_a.len;
		stack_b.nb_elem = 0;
		// TEST
		int *stk_a = stack_a.content;
		int *stk_b = stack_b.content;
		ft_printf("Before operation: \n");
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);


		rotater(stack_a);
		rotater(stack_b);
		pusher(stack_b, stack_a);
		pusher(stack_b, stack_a);
		pusher(stack_b, stack_a);
		rotater(stack_b);
		
		ft_printf("After operation:\n");
		ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
		ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
		ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
		ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
		ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);
		// END TEST
	}
	free(stack_a.content);
	free(stack_b.content);
	return (0);
}

// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
