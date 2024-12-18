/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/18 09:52:40 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Stores args in int array. If the option 'r' is provided, reverse order. */
int	*store_args(int argc, char **argv, char opt)
{
	size_t	i;
	int	*array;
	size_t	arr_len;

	arr_len = (size_t)argc - 1; 
	array = (int *)malloc(sizeof(int) * (argc - 1));
	if (!array)
		return (NULL);
	ft_memset(array, 0, argc - 1);
	i = 0;
	while (i < arr_len)
	{
		if (opt == 'r')
			array[i] = ft_atoi(argv[arr_len - i]);
		else
			array[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	return (array);
}

/* Parses args to check validity. */
int	parse_args(int argc, char **argv)
{
	if (args_are_all_int(argc, argv) != 0)
	{
		//ft_printf("Args are NOT all int!\n");
		return (1);
	}
	if (args_has_no_duplicate(argc, argv) != 0)
	{
		//ft_printf("Args HAVE duplicates!\n");
		return (1);
	}
	//ft_printf("Args are all int and have no duplicate!\n"); // DEBUG
	return (0);
}

/* Checks if args are all int. */
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
				return (1);
			j++;
			if (argv[i][0] != '-' && j > 10) // Only < MAX_INT
				return (1);
			if (j == 10)
			{
				if (argv[i][0] != '-' && ft_strncmp(argv[i], "2147483647", ft_strlen(argv[i])) > 0)
					return (1);
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0)	
					return (1);
			}
			if (j == 11)
			{
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0) // Only > MIN_INT			
					return (1);
			}
		}
		i++;
	}
	return (0);
}

/* Check if args has no duplicate. */
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
			if (res == 0 
				&& (ft_strlen(argv[i]) == ft_strlen(argv[j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// DEBUG

/* Stores args in int array. If the option 'r' is provided, reverse order.
int	*store_args(int argc, char **argv, char opt)
{
	size_t	i;
	int	*array;
	size_t	arr_len;

	arr_len = (size_t)argc - 1; 
	array = (int *)malloc(sizeof(int) * (argc - 1));
	i = 0;
	if (!array)
	{
		ft_printf("Array not mallocated in ft_store_args!\n");
		return (NULL);
	}
	ft_memset(array, 0, argc - 1);
	while (i < arr_len)
	{
		if (opt == 'r')
		{
			array[i] = ft_atoi(argv[arr_len - i]);
			ft_printf("Copied to array[%d]: '%d'.\n", i, array[i]);
		}
		else
		{
			array[i] = ft_atoi(argv[i + 1]);
			ft_printf("Copied to array[%d]: '%d'.\n", i, array[i]);	
		}
		i++;
	}
	return (array);
}
*/

/* Parses args to check validity.
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
*/
/* Checks if args are all int.
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
				//ft_printf("argv[%d][0] \'%c\' is not a digit!\n", i, argv[i][0]);
				return (1);
			}
			j++;
			if (argv[i][0] != '-' && j > 10) // Only < MAX_INT
			{
				//ft_printf("argv[%d] '%s' exceeds int limits!\n", i, argv[i]);
				return (1);
			}
			if (j == 10)
			{
				if (argv[i][0] != '-' && ft_strncmp(argv[i], "2147483647", ft_strlen(argv[i])) > 0)
				{
				//	ft_printf("argv[%d] '%s' is higher than MAX_INT!\n", i, argv[i]);
					return (1);
				}
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0)
				{	
				//	ft_printf("argv[%d] '%s' is lower than MIN_INT!!\n", i, argv[i]);
					return (1);
				}
			}
			if (j == 11)
			{
				if (argv[i][0] == '-' && ft_strncmp(argv[i], "-2147483648", ft_strlen(argv[i])) > 0) // Only > MIN_INT
				{
				//	ft_printf("argv[%s] lower than MIN_INT!\n", argv[i]);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
*/
/* Check if args has no duplicate.
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
			//ft_printf("Res argv[%d] and argv[%d]: \"%s\" - \"%s\" = %d\n", i, j, argv[i], argv[j], res);
			if (res == 0)
			{
			//	ft_printf("argv[%d] \"%s\" et argv[%d] \"%s\" are duplicate!\n", i, argv[i], j, argv[j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
*/
