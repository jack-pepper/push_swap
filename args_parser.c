/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/21 21:40:33 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Stores args in int array. If the option 'r' is provided, reverse order. */
int	*store_args(int nb_elem, char **args, char opt)
{
	int	*array;
	int	i;
 
	array = (int *)malloc(sizeof(int) * (nb_elem));
	if (!array)
		return (NULL);
	ft_memset(array, 0, nb_elem);
	i = 0;
	while (i < nb_elem)
	{
		if (opt == 'r')
			array[i] = ft_atoi(args[(nb_elem - 1) - i]);
		else
			array[i] = ft_atoi(args[i]);
		i++;
	}
	return (array);
}

/* Parses args to check validity. int i: start from [i] index*/
int	parse_args(int nb_elem, char **args, int i)
{
	if (args_are_all_int(nb_elem, args, i) != 0)
	{
	//	ft_printf("Args are NOT all int!\n");
		return (1);
	}
	if (args_has_no_duplicate(nb_elem, args, i) != 0)
	{
	//	ft_printf("Args HAVE duplicates!\n");
		return (1);
	}
	//ft_printf("Args are all int and have no duplicate!\n"); // DEBUG
	return (0);
}

/* Checks if args are all int. */
int	args_are_all_int(int nb_elem, char **args, int i)
{
	int	j;

	while (i < nb_elem)
	{
		j = 0;
		if (args[i][0] == '\0' || (args[i][0] == '-' && args[i][1] == '\0'))
			return (1);
		if (args[i][0] == '-' && args[i][1] != '\0')
			j++;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j])) // Only digits
				return (1);
			j++;
			if (args[i][0] != '-' && j > 10) // Only < MAX_INT
				return (1);
			if (j == 10)
			{
				if (args[i][0] != '-' && ft_strncmp(args[i], "2147483647", ft_strlen(args[i])) > 0)
					return (1);
				if (args[i][0] == '-' && ft_strncmp(args[i], "-2147483648", ft_strlen(args[i])) > 0)	
					return (1);
			}
			if (j == 11)
			{
				if (args[i][0] == '-' && ft_strncmp(args[i], "-2147483648", ft_strlen(args[i])) > 0) // Only > MIN_INT			
					return (1);
			}
		}
		i++;
	}
	return (0);
}

/* Check if args has no duplicate. */
int	args_has_no_duplicate(int nb_elem, char **args, int i)
{
	int	j;
	int	res;

	res = 0;
	while (i < nb_elem)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			res = ft_strncmp(args[i], args[j], ft_strlen(args[i]));
			if (res == 0 
				&& (ft_strlen(args[i]) == ft_strlen(args[j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// DEBUG

/* Stores args in int array. If the option 'r' is provided, reverse order.
int	*store_args(int nb_elem, char **args, char opt)
{
	size_t	i;
	int	*array;
	size_t	arr_len;

	arr_len = (size_t)nb_elem - 1; 
	array = (int *)malloc(sizeof(int) * (nb_elem - 1));
	i = 0;
	if (!array)
	{
		ft_printf("Array not mallocated in ft_store_args!\n");
		return (NULL);
	}
	ft_memset(array, 0, nb_elem - 1);
	while (i < arr_len)
	{
		if (opt == 'r')
		{
			array[i] = ft_atoi(args[arr_len - i]);
			ft_printf("Copied to array[%d]: '%d'.\n", i, array[i]);
		}
		else
		{
			array[i] = ft_atoi(args[i + 1]);
			ft_printf("Copied to array[%d]: '%d'.\n", i, array[i]);	
		}
		i++;
	}
	return (array);
}
*/

/* Parses args to check validity.
int	parse_args(int nb_elem, char **args)
{
	if (args_are_all_int(nb_elem, args) != 0)
	{
		ft_printf("Args are NOT all int!\n");
		return (1);
	}
	if (args_has_no_duplicate(nb_elem, args) != 0)
	{
		ft_printf("Args HAS duplicate!\n");
		return (1);
	}
	ft_printf("Args are all int and have no duplicate!\n");
	return (0);
}
*/
/* Checks if args are all int.
int	args_are_all_int(int nb_elem, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (i < nb_elem)
	{
		j = 0;
		if (args[i][0] == '\0' || (args[i][0] == '-' && args[i][1] == '\0'))
			return (1);
		if (args[i][0] == '-' && args[i][1] != '\0')
			j++;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j])) // Only digits
			{
				//ft_printf("args[%d][0] \'%c\' is not a digit!\n", i, args[i][0]);
				return (1);
			}
			j++;
			if (args[i][0] != '-' && j > 10) // Only < MAX_INT
			{
				//ft_printf("args[%d] '%s' exceeds int limits!\n", i, args[i]);
				return (1);
			}
			if (j == 10)
			{
				if (args[i][0] != '-' && ft_strncmp(args[i], "2147483647", ft_strlen(args[i])) > 0)
				{
				//	ft_printf("args[%d] '%s' is higher than MAX_INT!\n", i, args[i]);
					return (1);
				}
				if (args[i][0] == '-' && ft_strncmp(args[i], "-2147483648", ft_strlen(args[i])) > 0)
				{	
				//	ft_printf("args[%d] '%s' is lower than MIN_INT!!\n", i, args[i]);
					return (1);
				}
			}
			if (j == 11)
			{
				if (args[i][0] == '-' && ft_strncmp(args[i], "-2147483648", ft_strlen(args[i])) > 0) // Only > MIN_INT
				{
				//	ft_printf("args[%s] lower than MIN_INT!\n", args[i]);
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
int	args_has_no_duplicate(int nb_elem, char **args)
{
	int	i;
	int	j;
	int	res;

	i = 1;
	res = 0;
	while (i < nb_elem)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			res = ft_strncmp(args[i], args[j], ft_strlen(args[i]));
			//ft_printf("Res args[%d] and args[%d]: \"%s\" - \"%s\" = %d\n", i, j, args[i], args[j], res);
			if (res == 0)
			{
			//	ft_printf("args[%d] \"%s\" et args[%d] \"%s\" are duplicate!\n", i, args[i], j, args[j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
*/
