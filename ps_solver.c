/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/23 23:34:28 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*void	show_stacks(t_stack *stack_a, t_stack *stack_b, char *msg) // DEBUG
{
      	int *stk_a = stack_a->content;
	int *stk_b = stack_b->content;
        	ft_printf("%s\n", msg);
        	ft_printf("nb_elem a: %d - nb_elem b: %d\n ", stack_a->nb_elem, stack_b->nb_elem);
        	ft_printf("[a9]: %d    [b9]: %d   \n", stk_a[9], stk_b[9]);
        	ft_printf("[a8]: %d    [b8]: %d   \n", stk_a[8], stk_b[8]);
        	ft_printf("[a7]: %d    [b7]: %d   \n", stk_a[7], stk_b[7]);
        	ft_printf("[a6]: %d    [b6]: %d   \n", stk_a[6], stk_b[6]);
      	 	ft_printf("[a5]: %d    [b5]: %d   \n", stk_a[5], stk_b[5]);
        	ft_printf("[a4]: %d    [b4]: %d   \n", stk_a[4], stk_b[4]);
        	ft_printf("[a3]: %d    [b3]: %d   \n", stk_a[3], stk_b[3]);
        	ft_printf("[a2]: %d    [b2]: %d   \n", stk_a[2], stk_b[2]);
        	ft_printf("[a1]: %d    [b1]: %d   \n", stk_a[1], stk_b[1]);
        	ft_printf("[a0]: %d    [b0]: %d   \n", stk_a[0], stk_b[0]);
		ft_printf("==============================================\n");
}*/

int	test_easy_cases(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	t_list	*new_cmd;
	size_t	i;

	i = 1;
	if (is_ordered(stack_a) == 0)
		return (0);
	if (stack_a->nb_elem <= 3)
	{
		handle_small_stack(cmd_list, stack_a, stack_b);
		return (0);
	}
	while (i <= (stack_a->nb_elem))
	{
		rotater(stack_a);
		if (is_ordered(stack_a) == 0)
		{
			while (i > 0)
			{
        			new_cmd = ft_lstnew("ra");
				if (!new_cmd)
					return (-1);
				ft_lstadd_back(&cmd_list, new_cmd);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

t_list	*ps_solver(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	int	*stk_b;
	int	res;

	stk_b = stack_b->content;
	res = test_easy_cases(cmd_list, stack_a, stack_b);
	if (res == 0) // if -1: ERROR
	{
		return (cmd_list);
	}
	while ((is_ordered(stack_a) != 0))
	{
		rotate_lowest_and_push(stack_a, stack_b, cmd_list);
		if ((stack_b->nb_elem > 1)
			&& (stk_b[stack_b->nb_elem - 1] < stk_b[stack_b->nb_elem - 2]))
			sb(stack_b, cmd_list);
	}
	while (stack_b->nb_elem > 0)
		pa(stack_a, stack_b, cmd_list);
	return (cmd_list);
}

void	rotate_lowest_and_push(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
	size_t	len_i;

	len_i = stack_a->nb_elem - 1; // to make it more readable
	while (is_ordered(stack_a) != 0)
	{
		if (stack_a->lowest_pos == len_i) // LOWEST at top
		{
			pb(stack_b, stack_a, cmd_list);
			find_lowest(stack_a);
			len_i--;
			if (stack_a->nb_elem == 3 && (is_ordered(stack_a) != 0))
				handle_small_stack(cmd_list, stack_a, stack_b);
		}
		else if (stack_a->lowest_pos == 0) // LOWEST at [0]
		{
			rra(stack_a, cmd_list);
			stack_a->lowest_pos = len_i;
		}
		else if ((len_i / 2) < stack_a->lowest_pos)
		{
			while (stack_a->lowest_pos != len_i)
			{
				ra(stack_a, cmd_list);
				stack_a->lowest_pos++;
			}
		}
		else if ((len_i / 2) >= stack_a->lowest_pos)
		{
			while (stack_a->lowest_pos != 0)
			{
				rra(stack_a, cmd_list);
				stack_a->lowest_pos--;
			}
			rra(stack_a, cmd_list);
			stack_a->lowest_pos = len_i;
		}
	}
}

int	is_ordered(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < (stack->nb_elem - 1))
	{
		if (stack->content[i] < stack->content[i + 1])
			return (1);
		i++;
	}
	return (0);
}

/* NB: This function is called only if the stack is not ordered. */
void	handle_small_stack(t_list *cmd_list, t_stack *stack_a, t_stack *stack_b)
{
	stack_b->content[0] = stack_b->content[0];// USELESS (STACK_B is not needed)
	find_highest(stack_a);
	if (stack_a->nb_elem == 2)
		sa(stack_a, cmd_list);
	else if (stack_a->nb_elem == 3)
	{
		if (stack_a->highest_pos == 0)
			sa(stack_a, cmd_list);
		else if (stack_a->highest_pos == 1)
			rra(stack_a, cmd_list);
		else if (stack_a->highest_pos == 2)
			ra(stack_a, cmd_list);
	}
	//ft_printf("stack_a highest_pos: %d - lowest_pos: %d\n", stack_a->highest_pos, stack_a->lowest_pos);
	if ((stack_a->highest_pos == 1 && stack_a->lowest_pos == 2)
		|| (stack_a->highest_pos == 2 && stack_a->lowest_pos == 0))
		sa(stack_a, cmd_list);
	//if (stack_a->highest_pos == 0 && stack_a->lowest_pos == 1)
	//	sa(stack_a, cmd_list);
}
