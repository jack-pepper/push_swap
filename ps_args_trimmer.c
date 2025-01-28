/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_args_trimmer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:43:29 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/28 12:25:55 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Trim each arg (remove + sign and leading zeros)
char	*ps_trim(char *trimmed_arg, char *arg, int len, int k)
{
	int	i;

	i = 0;
	if (ft_strnopbrk(arg, "0") == NULL || ft_strnopbrk(arg, "-0") == NULL
		|| ft_strnopbrk(arg, "+0") == NULL)
	{
		trimmed_arg = (char *)malloc(1 + 1);
		if (!trimmed_arg)
			return (NULL);
		ft_strlcpy(trimmed_arg, "0", 1);
		return (trimmed_arg);
	}
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	trimmed_arg = (char *)malloc((len - i + (arg[0] == '-') + 1));
	if (!trimmed_arg)
		return (NULL);
	if (arg[0] == '-')
		trimmed_arg[k++] = '-';
	while (i < len)
		trimmed_arg[k++] = arg[i++];
	trimmed_arg[k] = '\0';
	return (trimmed_arg);
}

// Trim all args
char	**ps_trim_all(char **trimmed_args, char **args, int nb_args, int i)
{
	char	*trimmed_arg;
	int		k;
	size_t	arg_len;

	k = 0;
	while (i < nb_args)
	{
		if ((args[i][(int)ft_strlen(args[i]) - 1] == '-')
			|| (args[i][(int)ft_strlen(args[i]) - 1] == '+'))
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
	trimmed_args[k] = NULL;
	return (trimmed_args);
}
