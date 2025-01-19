/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:17:07 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/19 23:35:27 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int      count_tokens(char const *s, char delim)
{
        int     nb_tokens;
        int     i;

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

int     is_ordered(t_stack *stack, char opt)
{
        size_t  i;

        i = 0;
	if (opt == 'd')
	{
        	while (i < (stack->nb_elem - 1))
        	{
                	if (stack->index_map[i] < stack->index_map[i + 1])
                        	return (1);
                	i++;
        	}
	}
	else if (opt == 'a')
	{
        	while (i < (stack->nb_elem - 1))
        	{
                	if (stack->index_map[i] > stack->index_map[i + 1])
                        	return (1);
                	i++;
        	}
	}
	return (0);
}

void    find_highest(t_stack *stack)
{
        size_t  i;

        i = 0;
        stack->highest = stack->index_map[0];
        stack->highest_pos = i;
        while (i < stack->len)
        {
                if (stack->index_map[i] > stack->highest)
                {
                        stack->highest = stack->index_map[i];
                        stack->highest_pos = i;
                }
                i++;
        }
}

void    find_lowest(t_stack *stack)
{
        size_t  i;

        stack->lowest = stack->index_map[0];
        stack->lowest_pos = 0;
	i = 1;
        while (i < stack->nb_elem)
        {
                if (stack->index_map[i] < stack->lowest)
                {
                        stack->lowest = stack->index_map[i];
                        stack->lowest_pos = i;
                }
                i++;
        }
}

// Take an array of int and convert each nb to its index if the array was sorted 
int	conv_to_index(int *conv_arr, int *src_arr, size_t len)
{
	int	*sorted_arr;
	size_t	i;
	size_t	j;
	
	if (!conv_arr) // so it can take an array already ready OR just a pointer
	{
		conv_arr = malloc(sizeof(int) * len);
		if (!conv_arr)
			return (1);
			//return (ft_ret(1, "Error\n"));
	}
	sorted_arr = malloc(sizeof(int) * len);
	if (!sorted_arr)
		return (1);
		//return (ft_ret(1, "Error\n"));
	ft_cpy_arr_int(sorted_arr, src_arr, len);
	// Some functions not written yet. Final result:

	/*
	if (len < 20) // bub, ins, sel: less than 10-20 elems : can be removed
		ft_bub_srt(sorted_arr, len, 'd');
	//else if (len >= 20 && len < 1000) // qck: 100-1000 : KEEP if a choice is to be made
		//ft_qck_srt(sorted_arr, len, 'd'); // NOT DONE YET!
	else if (len >= 1000)  // && len < 10000) // mrg: 1000+ : KEEP if a choice is to be made
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
//		ft_printf("conv_arr[%d] = %d (sorted_arr[%d] = %d) (src_arr[%d] = %d)\n", j, i, i, sorted_arr[i], j, src_arr[j]);	
	i++;
	}
	free(sorted_arr);
	return (0);
}

// Temporary
void  show_stacks(t_stack *stack_a, t_stack *stack_b, char *msg) // DEBUG
{
	int	i = stack_a->len - 1;
        int *stk_a = stack_a->index_map;
        int *stk_b = stack_b->index_map;
        ft_printf("%s\n", msg);
	while (i >= 0)
	{
                ft_printf("[a%i]: %d    [b%i]: %d   \n", i, stk_a[i], i, stk_b[i]);
		i--;
        } 
	       ft_printf("==============================================\n");
}
