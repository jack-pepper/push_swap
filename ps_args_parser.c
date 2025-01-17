/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/17 15:04:25 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Parses args to check validity. int i: start from [i] index*/
int	parse_args(int nb_elem, char **args, int i)
{
	if (args_are_all_int(nb_elem, args, i) != 0)
		return (ft_ret(1, "Error\nArgs are NOT all int\n"));
	if (args_has_no_duplicate(nb_elem, args, i) != 0)
		return (ft_ret(1, "Error\nArgs have duplicates\n"));
	return (0);
}

/* Checks if args are all int. */
int	args_are_all_int(int nb_elem, char **args, int i)
{
	int	j;

	while (i < nb_elem)
	{
		j = 0;
		if ((args[i][0] == '\0')
			|| ((args[i][0] == '-') && (args[i][1] == '\0')))
			return (1);
		if (args[i][0] == '-' && args[i][1] != '\0')
			j++;
		while (args[i][j] != '\0')
		{
			if (!ft_isdigit(args[i][j]))
				return (1);
			j++;
			if (args[i][0] != '-' && j > 10)
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
