
/* TO DO:
 * - do last parsing tests
 * - store input as an int array?
 * */

#include "push_swap.h"
#include <stdio.h> // DEBUG!!!
#include <unistd.h>

typedef struct s_stack
{
	size_t	len;
	int                    *content;
        size_t	nb_elem;
}                               t_stack;

int	parse_args(int argc, char **argv);
int	*store_args(int argc, char **argv);
int	args_are_all_int(int argc, char **argv);
int	args_has_no_duplicate(int argc, char **argv);

/*
 * Beggining: 
 * - Stack a contains a random amount of negative and/or positive numbers which cannot be duplicated
 * - Stack b is empty
 *
 * Operations:
 * - sa (swap a): swaps the first 2 elements at the top of stack a. If elem = 1 or 0: do nothing
 * - sb (swap b): same for stack b
 * - ss : sa + sb at the same time
 * - pa (push a) : takes the first elem at top b and put it at top a. If b empty: do nothing
 * - pb (push b) : same with top a
 * - ra (rotate a) : shift up all elements of stack a by 1 (first elem becomes the last one)
 * - rb (rotate b) : same for b
 * - rr : ra + rb at the same time
 * - rra (reverse rotate a): shift down all elements of stack a by 1 (last elem becomes the first one))
 * - rrb (reverse rotate b): same for b
 * - rrr: rra + rrb at the same time
 *
 */


void    sa(t_stack stack_a)
{
	size_t	nb;
	int	*stk_a;
	
	nb = stack_a.nb_elem;
	stk_a = stack_a.content;
        if (nb < 2)
                return ;
        stk_a[nb - 1] = stk_a[nb - 1] ^ stk_a[nb - 2];
        stk_a[nb - 2] = stk_a[nb - 1] ^ stk_a[nb - 2];
        stk_a[nb - 1] = stk_a[nb - 1] ^ stk_a[nb - 2];
        ft_printf("stack_a[nb - 1] = %d - stack_a[nb - 2] = %d\n", stk_a[nb - 1], stk_a[nb - 2]);
}

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
		stack_a.content = store_args(argc, argv);
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
		sa(stack_a);
		ft_printf("Test: stack_a[last] {%d} stack_a[antelast] {%d}\n", stack_a.content[stack_a.nb_elem - 1], stack_a.content[stack_a.nb_elem - 2]);
	}
	free(stack_a.content);
	free(stack_b.content);
	return (0);
}

int	*store_args(int argc, char **argv)
{
	int	i;
	int	*array;

	i = 0;
	array = (int *)malloc(sizeof(int) * (argc - 1));
	if (!array)
	{
		ft_printf("Array not mallocated in ft_store_args!\n");
		return (NULL);
	}
	ft_memset(array, 0, argc - 1);
	while (i < argc - 1)
	{
		array[i] = ft_atoi(argv[i + 1]);
		ft_printf("Copied to array[%d]: '%d'.\n", i, array[i]);	
		i++;
	}
	return (array);
}

int	parse_args(int argc, char **argv)
{
	if (args_are_all_int(argc, argv) != 0)
	{
		ft_printf("Args are NOT all int!\n");
		return (1);
	}
	if (args_has_no_duplicate(argc, argv) != 0)
	{
		ft_printf("Args HAS duplicate!\n");
		return (1);
	}
	ft_printf("Args are all int and have no duplicate!\n");
	return (0);
}

int	args_are_all_int(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '\0' || (argv[i][0] == '-' && argv[i][1] == '\0'))
			return (1);
		if (argv[i][0] == '-' && argv[i][1] != '\0')
			j++;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j])) // Only digits
			{
				ft_printf("argv[%d][0] \'%c\' is not a digit!\n", i, argv[i][0]);
				return (1);
			}
			j++;
			if (argv[i][0] != '-' && j > 10) // Only < MAX_INT
			{
				ft_printf("argv[%d] '%s' exceeds int limits!\n", i, argv[i]);
				return (1);
			}
			if (j == 10)
			{
				if (argv[i][0] != '-' && ft_strncmp(argv[i], "2147483647", ft_strlen(argv[i])) > 0)
				{
					ft_printf("argv[%d] '%s' is higher than MAX_INT!\n", i, argv[i]);
					return (1);
				}
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0)
				{	
					ft_printf("argv[%d] '%s' is lower than MIN_INT!!\n", i, argv[i]);
					return (1);
				}
			}
			if (j == 11)
			{
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0) // Only > MIN_INT
				{
					ft_printf("argv[%s] lower than MIN_INT!\n", argv[i]);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

int	args_has_no_duplicate(int argc, char **argv)
{
	int	i;
	int	j;
	int	res;

	i = 1;
	res = 0;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			res = ft_strncmp(argv[i], argv[j], ft_strlen(argv[i]));
			ft_printf("Res argv[%d] and argv[%d]: \"%s\" - \"%s\" = %d\n", i, j, argv[i], argv[j], res);
			if (res == 0)
			{
				ft_printf("argv[%d] \"%s\" et argv[%d] \"%s\" are duplicate!\n", i, argv[i], j, argv[j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// arg: stack a formatted as a list of int (first argument will be at top of the stack)
// the prog must display the smallest list of instructions possible to sort the stack a, the smallest number being at the top
// instructions must be separated by a \n and nothing else
// if no param specified: the prog must not display anything and give the prompt back
// in case of error: display "Error" followed by a newline on the standard error (ex: some arg arent int, some args are bigger than an int and/or there are duplicates)
