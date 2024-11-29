#define DEBUG 1 // DEBUG!!!

#include "push_swap.h"
#include <stdio.h> // DEBUG!!!
#include <unistd.h>

int	error_check(int argc, char **argv);

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

int	main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
		return (1); // ???
	else if (argc >= 3)
	{
		if (error_check(argc, argv) != 0)
		{
			write(2, "Error\n", 7);
			return (1);
		}
		write(1, "Input is OK!\n", 14);
	}
	return (0);
}

// Checks for incorrect input. Easier to loop through strings
int	error_check(int argc, char **argv)
{
	int	i;
	int	j;
	int	res;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!ft_isdigit(argv[i][0]) && argv[i][0] != '-')
		{
			if (DEBUG == 1)
				printf("argv[%d][0] \'%c\' is neither a digit or a minus sign!\n", i, argv[i][0]);
			return (1);
		}
		if (argv[i][0] == '-')
			j++;
		while (argv[i][j] != '\0')
		{
			if (DEBUG == 1)
				printf("argv[%d][%d] = %c\n", i, j, argv[i][j]);
			if (!ft_isdigit(argv[i][j]))
			{
				if (DEBUG == 1)
					printf("argv[%d][%d] \'%c\'is not a digit!\n", i, j, argv[i][j]);
				return (2);
			}
				if (j == 9 && ft_strncmp(argv[i], "2147483647", ft_strlen(argv[i])) > 0) // ADD HANDLER FOR NEGATIVE VALUES TOO!
			{
				if (DEBUG == 1)
					printf("argv[%s] isn't supported by int: %d!\n", argv[i], ft_strncmp(argv[i], "2147483647", ft_strlen(argv[i])));
				return (3);
			}

			j++;
		}
		i++;
	}
	i = 1;
	res = 1;
	while (i < argc)
	{
		j = i + 1;
		while (res != 0 && j < argc)
		{
			res = ft_strncmp(argv[i], argv[j], ft_strlen(argv[i]) != 0);
			if (DEBUG == 1)
				printf("Res argv[%d] and argv[%d]: %d\n", i, j, res);
			if (res == 0)
			{
				if (DEBUG == 1)
					printf("argv[%d] \"%s\" et argv[%d] \"%s\" are duplicate!\n", i, argv[i], j, argv[j]);
				return (4);
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
