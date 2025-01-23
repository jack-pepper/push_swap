/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:17:07 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/23 10:32:43 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_ret(int return_val, char *msg)
{
	int	fd;

	if (msg == NULL)
		return (return_val);
	if (return_val == 0)
		fd = 1;
	else
		fd = 2;
	ft_putendl_fd(msg, fd);
	return (return_val);
}

int	count_tokens(char const *s, char delim)
{
	int	nb_tokens;
	int	i;

	nb_tokens = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == delim && s[i] != '\0')
			i++;
		if (s[i] != delim && s[i] != '\0')
		{
			nb_tokens++;
			while (s[i] != delim && s[i] != '\0')
				i++;
		}
	}
	return (nb_tokens);
}

/* Take a src_arr of int (here: stk->content), convert and store it to
 * conv_arr. Each nb will be converted to their index if the array was sorted.
 * Can take a pointer to a NULL conv_arr or already defined. 
 */
int	conv_to_index(int *conv_arr, int *src_arr, size_t len)
{
	int		*sorted_arr;
	size_t	i;
	size_t	j;

	if (!conv_arr)
	{
		conv_arr = malloc(sizeof(int) * len);
		if (!conv_arr)
			return (1);
	}
	sorted_arr = malloc(sizeof(int) * len);
	if (!sorted_arr)
		return (1);
	ft_cpy_arr_int(sorted_arr, src_arr, len);
	// Final version:
	/*
	if (len < 20) // bub/ins/sel
		ft_bub_srt(sorted_arr, len, 'd'); / can be removed
	//else if (len >= 20 && len < 1000) // qck: 100-1000
		//ft_qck_srt(sorted_arr, len, 'd'); // NOT DONE YET!
	else if (len >= 1000)  // && len < 10000) // mrg: 1000+
		ft_mrg_srt(sorted_arr, len, 'd'); 
	//else if (len >= 10000) // hep: 10000+ elems / can be removed
	//	ft_hep_srt();	
	*/
	// For testing at the moment:
	ft_mrg_srt(sorted_arr, len, 'd');
	ft_rev_arr_int(sorted_arr, len);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (sorted_arr[i] != src_arr[j])
			j++;
		conv_arr[j] = i;
		i++;
	}
	free(sorted_arr);
	return (0);
}

/* Get the square root of a number (using Newton method).
 * Return -1 if the number is negative.
 */
double	ft_sqrt_newton(double number)
{
	double	guess;
	double	epsilon;
	double	next_guess;
	double	fabs;

	if (number < 0)
	{
		return (-1);
	}
	guess = number / 2.0;
	epsilon = 0.000001;
	while (1)
	{
		next_guess = (guess + number / guess) / 2.0;
		if ((next_guess - guess) < 0)
			fabs = -(next_guess - guess);
		else
			fabs = (next_guess - guess);
		if (fabs < epsilon)
		{
			return (next_guess);
		}
		guess = next_guess;
	}
}

void	clean_cmd_and_set_next(t_list **cmd_list, int jump)
{
	t_list *temp;
	t_list *temp_next;

	temp = *cmd_list;
	temp_next = (*cmd_list)->next;
	if (jump == 0)
	{
		*cmd_list = (*cmd_list)->next;
		free(temp);
	}
	else if (jump == 1)
	{
		*cmd_list = (*cmd_list)->next->next;
		free(temp);
		free(temp_next);
	}
}

// Show the stks' content (for debugging or vizualisation).
/*
void	show_stks(t_stk *stk_a, t_stk *stk_b, char *msg)
{
	int	i;
	int	*i_map_a;
	int	*i_map_b;

	i = stk_a->len - 1;
	i_map_a = stk_a->i_map;
	i_map_b = stk_b->i_map;
	ft_printf("%s\n", msg);
	while (i >= 0)
	{
		ft_printf("[a%i]: %d  [b%i]: %d \n", i, i_map_a[i], i, i_map_b[i]);
		i--;
	}
	ft_printf("==============================================\n");
}
*/
