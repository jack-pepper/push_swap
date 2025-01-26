/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/26 23:45:09 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Parse args to check validity, starting from [i] index.
int	parse_args(int nb_elem, char **args, int i, char ***trimmed_args)
{
	if (*args == NULL)
		return (1);
	*trimmed_args = (char **)malloc(sizeof(char *) * nb_elem);
	if (!trimmed_args)
		return (1);
	if ((ps_trim_all(*trimmed_args, args, nb_elem, i) == NULL)
		|| (args_are_all_int(nb_elem, *trimmed_args) != 0)
		|| (args_has_no_duplicate(nb_elem, *trimmed_args, 0) != 0))
	{
		return (1);
	}
	return (0);
}

long long	ps_atoll(const char *nptr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*nptr))
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
		{
			sign = -1;
		}
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

// Return 0 if args are all int, else 1.
int	args_are_all_int(int nb_elem, char **args)
{
	char	*unsigned_val;
	int		i;

	i = 0;
	while (i < nb_elem)
	{
		unsigned_val = &args[i][0];
		if (args[i][0] == '-')
			unsigned_val = &args[i][1];
		if ((ft_strnopbrk(unsigned_val, "0123456789") != NULL))
			return (1);
		if (ft_strlen(args[i]) >= 10)
		{
			if ((ps_atoll(args[i]) < -2147483648)
				|| (ps_atoll(args[i]) > 2147483647))
				return (1);
		}
		i++;
	}
	return (0);
}

// Return 1 if args have duplicate, else 0.
int	args_has_no_duplicate(int nb_elem, char **args, int i)
{
	int	j;

	while (i < nb_elem)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			if ((ft_strncmp(args[i], args[j], ft_strlen(args[i])) == 0)
				&& (ft_strlen(args[i]) == ft_strlen(args[j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
void	ft_set_ints(char op, int val, int *var, ...)
{
	va_list	args;

	va_start(args, val);
	if (!op || !val)
		return ;	
	if (op == 'i')
		// Set all to val (ex: i, 0)
	else if (op == '+')
		// increment all by val
	else if (op == '-')
		// decrement all by val
	else if (op == '*')
		// multiply all by val
	else if (op == '/')
		// divide all by val
	else if (op == '%')
		// modulo... or percent?
	va_end(args);
}
*/

// Store args in int array. If the option 'r' is provided, reverse order.
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
		{
			array[i] = ft_atoi(args[(nb_elem - 1) - i]);
			free(args[(nb_elem - 1) - i]);
		}
		else
		{
			array[i] = ft_atoi(args[i]);
			free(args[i]);
		}
		i++;
	}
	free(args);
	return (array);
}
