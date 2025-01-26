/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/26 17:52:57 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ps_trim(char *trimmed_arg, char *arg, int len, int k)
{
	int	is_neg;
	int	i;

	i = 0;
	is_neg = 0;
	if ((ft_strnopbrk(arg, "0") == NULL) 
		|| (ft_strnopbrk(arg, "-0") == NULL)
		|| (ft_strnopbrk(arg, "+0") == NULL))
		return (ft_strdup("0"));
	if (arg[i] == '-')
		is_neg = 1;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	trimmed_arg = (char *)malloc((len - i + is_neg) + 1);
	if (!trimmed_arg)
		return (NULL);
	if (is_neg == 1)
		trimmed_arg[k++] = '-';
	while (i < len)
		trimmed_arg[k++] = arg[i++];
	trimmed_arg[k] = '\0';
	return (trimmed_arg);
}

char	**ps_trim_all(char **trimmed_args, char **args, int nb_args, int i)
{
	char	*trimmed_arg;
	int	k;
	size_t	arg_len;

	k = 0;
	while (i < nb_args)
	{
		if (args[i][(int)ft_strlen(args[i]) - 1] == '-')
			return (NULL);
		trimmed_arg = NULL;
		arg_len = ft_strlen(args[i]);
		trimmed_arg = ps_trim(trimmed_arg, args[i], arg_len, 0);
		if (!trimmed_arg)
			return (NULL);
		trimmed_args[k] = ft_strdup(trimmed_arg);
		free(trimmed_arg);
		if (!trimmed_args[k])
			return (NULL);
		i++;
		k++;
	}
	return (trimmed_args);
}

// Parse args to check validity, starting from [i] index.
int	parse_args(int nb_elem, char **args, int i)
{
	char	**trimmed_args;

	if (*args == NULL)
		return (1);
	trimmed_args = (char **)malloc(sizeof(char *) * nb_elem);	
	//if (i > 0)
	//	nb_elem = nb_elem + i;
	if (!trimmed_args)
		return (1);
	if (ps_trim_all(trimmed_args, args, nb_elem, i) == NULL)
		return (1);
	if (args_are_all_int(nb_elem, trimmed_args) != 0)
		return (1);
	if (args_has_no_duplicate(nb_elem, trimmed_args, 0) != 0)
		return (1);
	return (0);
}

long long    ft_atoll(const char *nptr)
{
        long long     result;
        int     sign;

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
	int	i;
	char	*unsigned_val;

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
			if ((ft_atoll(args[i]) < -2147483648)
				|| (ft_atoll(args[i]) > 2147483647))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
// Return 0 is the string at the given index is in int bounds, else 1.
int	check_int_limits(char **args, int i, int j)
{
	if ((j > 11)
		|| ((j > 10) && (args[i][0] != '-' && args[i][0] != '+')))
		return (1);
	if (j == 10)
	{
		if ((args[i][0] != '-' && args[i][0] != '+')
			&& (ft_strncmp(args[i], "2147483647", 10) > 0))
			return (1);
	}
	if (j == 11)
	{
		if ((args[i][0] == '-')
			&& (ft_strncmp(args[i], "-2147483648", 11) > 0))
			return (1);
		if ((args[i][0] == '+')
			&& (ft_strncmp(args[i], "+2147483647", 11) > 0))
			return (1);
	}
	return (0);
}
*/

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
			array[i] = ft_atoi(args[(nb_elem - 1) - i]);
		else
			array[i] = ft_atoi(args[i]);
		i++;
	}
	return (array);
}
