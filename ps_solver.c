/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/22 09:44:48 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	test_easy_cases(t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;
	size_t	i;

	i = 1;
	if (is_ordered(stack_a, 'd') == 0)
		return (0);
	if (stack_a->nb_elem <= 3)
	{
		sort_three_a(stack_a, cmd_list);
		return (0);
	}
	while (i <= (stack_a->nb_elem)) // Test if simple rotations may be enough to order.
	{
		rotater(stack_a, cmd_list, "");
		if (is_ordered(stack_a, 'd') == 0)
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

void    sort_three_a(t_stack *stack_a, t_list *cmd_list)
{
        find_highest(stack_a);
        find_lowest(stack_a);	
        if (stack_a->nb_elem == 2)
                swapper(stack_a, cmd_list, "sa");
        else if (stack_a->nb_elem == 3)
        {
                if (stack_a->highest_pos == 0)
                        swapper(stack_a, cmd_list, "sa");
                else if (stack_a->highest_pos == 1)
                        reverse_rotater(stack_a, cmd_list, "rra");
                else if (stack_a->highest_pos == 2)
                        rotater(stack_a, cmd_list, "ra");
        }
        if ((stack_a->highest_pos == 1 && stack_a->lowest_pos == 2)
                || (stack_a->highest_pos == 2 && stack_a->lowest_pos == 0))
                swapper(stack_a, cmd_list, "sa");
}

void    sort_three_b(t_stack *stack_b, t_list *cmd_list)
{
        find_highest(stack_b);
	find_lowest(stack_b);
        if (stack_b->nb_elem == 2 && stack_b->index_map[0] > stack_b->index_map[1])
                swapper(stack_b, cmd_list, "sb");
        else if (stack_b->nb_elem == 3)
        {
                if (stack_b->lowest_pos == 0)
                        swapper(stack_b, cmd_list, "sb");
                else if (stack_b->lowest_pos == 1)
                        reverse_rotater(stack_b, cmd_list, "rrb");
                else if (stack_b->lowest_pos == 2)
                        rotater(stack_b, cmd_list, "rb");
        }
        if ((stack_b->lowest_pos == 1 && stack_b->highest_pos == 2)
                || (stack_b->lowest_pos == 2 && stack_b->highest_pos == 0))
                swapper(stack_b, cmd_list, "sb");
}

/* Main push_swap algorithm:
 *
 * 	** PUSH_TO_B **
 * - Define mid_val. 
 * - Find the shortest dist (from top/bottom) to any nb < mid_val.
 * - ra or rra until it is on top stack_a, then pb.
 * - When all nb < mid_val has been pushed to stack_b, define next_mid_val.
 * - Stop and sort stack_a when only 3 elements left.
 * -
 * 	** PUSH_TO_A **
 * - If top stack_b is the next val needed (top stack_a - 1), pa
 * - If it's top stack_b - 1: sb, pa
 * - If not: get_shortest_dist, rb/rrb, pa
 * - Stop and sort stack_b when 3 elements left, then push them to stack_a.
 */


// While rotating, check if the next target is on the way. If it is,
// push it to stack_b, then swap.
/* Returns the shortest distance. Its sign indicates the direction:
 * - pos val: from the end of array
 * - neg val: from the start of array
 * This function should NOT be relied on if there is no more nb to be found.
 */
int     get_shortest_dist(t_stack *stack, int min, int max)
{
        int     dist_from_end;
        int     dist_from_start;
        size_t  i;
        int  j;

	i = 1; // I start at 1 for less calc
  //      ft_printf("min = %d - max = %d - stack->index_map[stack->nb_elem - %d]: %d\n", min, max, i, stack->index_map[stack->nb_elem - i]);
	while ((i <= stack->nb_elem) && ((stack->index_map[stack->nb_elem - i] < min) || (stack->index_map[stack->nb_elem - i] >= max)))
	{
//		ft_printf("stack->index_map[stack->nb_elem - %d]: %d\n", i, stack->index_map[stack->nb_elem - i]);
                i++;
	}
        dist_from_end = i - 1;
        if (dist_from_end == 0)
                return (0);
        j = 0;
        //dist_from_start = 1;
        while ((j < dist_from_end) && ((stack->index_map[j] < min) || (stack->index_map[j] >= max)))
                j++;
        dist_from_start = j + 1;
//	ft_printf("dist_from_end: %d - dist_from_start: %d\n", dist_from_end, dist_from_start);
        if (dist_from_end < dist_from_start)
                return (dist_from_end);
        else
                return (dist_from_start * (-1));
}

/* Find the optimal rotation or reverse rotation to bring the given target
 * to the top of the current stack.
 */
void	optimal_rot_a(t_stack *stack_a, t_list *cmd_list, int dist)
{
	if (dist == 0)
		return ; 
	while (dist != 0)
	{
		if (dist > 0)
		{
			rotater(stack_a, cmd_list, "ra");
			dist--;
		}
		else if (dist < 0)
		{
			reverse_rotater(stack_a, cmd_list, "rra");
			dist++;
		}
	}
}
void	optimal_rot_b(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list, int tgt_i)
{
	int	top_i;
	int	next_highest;

	top_i = (stack_b->nb_elem - 1);
	next_highest = (stack_b->highest - 1);
	if (tgt_i >= (top_i / 2))
	{
		while (tgt_i < top_i)
		{
			if (stack_b->index_map[stack_b->nb_elem - 1] == next_highest)
			{
				pusher(stack_a, stack_b, cmd_list, "pa");
				top_i--;
			}
			if (stack_b->index_map[stack_b->nb_elem - 1] != stack_b->highest)
			{
				rotater(stack_b, cmd_list, "rb");
				tgt_i++;
			}
		}
	}
	else
	{
		while (tgt_i > -1)
		{	
			if (stack_b->index_map[stack_b->nb_elem - 1] == next_highest)
				pusher(stack_a, stack_b, cmd_list, "pa");
			reverse_rotater(stack_b, cmd_list, "rrb");
			tgt_i--;
		}
	}
}

double	ft_sqrt_newton(double number) 
{
	if (number < 0)
	{
		return -1;  // Return -1 for negative input as square root isn't defined for negative numbers
	}
	double guess = number / 2.0;  // Initial guess
	double epsilon = 0.000001;    // Precision
	while (1)
	{
        	double next_guess = (guess + number / guess) / 2.0;
        	if (fabs(next_guess - guess) < epsilon)
		{
            		return next_guess;
        	}
        	guess = next_guess;
    	}
}

void	ps_to_b(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
	int	pivot;
	int	max;
	int	dist;

	pivot = (int)ft_sqrt_newton((double)stack_a->nb_elem);
	//pivot = 22;
//	ft_printf("stack_a->len: %d - pivot: %d\n", stack_a->nb_elem, pivot);
	find_lowest(stack_a);
	max = stack_a->lowest + pivot;
	while ((stack_a->nb_elem > 3) && (is_ordered(stack_a, 'd') != 0))
	{
//		show_stacks(stack_a, stack_b, "BEFORE push to b"); // DEBUG
		while (stack_a->lowest < max)
		{
		//	find_lowest(stack_a);
			dist = get_shortest_dist(stack_a, stack_a->lowest, max);
	//		ft_printf("lowest: %d - lowest_pos: %d - max: %d - dist: %d\n", stack_a->lowest, stack_a->lowest_pos, max, dist);
			optimal_rot_a(stack_a, cmd_list, dist);
			pusher(stack_b, stack_a, cmd_list, "pb");
	//		show_stacks(stack_a, stack_b, "AFTER push to b"); // DEBUG
//			ft_printf("stack_b->nb_elem: %d\n", stack_b->nb_elem);
			if (stack_b->nb_elem > 1 && ((stack_b->index_map[stack_b->nb_elem - 1]) < (stack_b->index_map[stack_b->nb_elem - 2]))) 
			{
				swapper(stack_b, cmd_list, "sb"); // swap top b and next b if the next one has been found
	//			show_stacks(stack_a, stack_b, "AFTER swap b"); // DEBUG
			}
			find_lowest(stack_a);
		}
		//find_lowest(stack_a);
		max = stack_a->lowest + pivot;
		if (max > (int)stack_a->len - 1)
			max = stack_a->len - 1;
	}
	if (is_ordered(stack_a, 'd') != 0)
		sort_three_a(stack_a, cmd_list);
	return ;
}

void	ps_to_a(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{	
	while (stack_b->nb_elem > 3)
	{
		find_highest(stack_b);
		optimal_rot_b(stack_a, stack_b, cmd_list, stack_b->highest_pos);
		pusher(stack_a, stack_b, cmd_list, "pa");
		if ((stack_a->nb_elem > 1 && (stack_a->index_map[stack_a->nb_elem - 1]) > (stack_a->index_map[stack_a->nb_elem - 2]))) 
			swapper(stack_a, cmd_list, "sa"); // swap top b and next b if the next one has been found
	}	
	if (is_ordered(stack_b, 'a') != 0)
		sort_three_b(stack_b, cmd_list);
	while (stack_b->nb_elem > 0)
		pusher(stack_a, stack_b, cmd_list, "pa");
	return ;
}


void	ps_sort(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{	
//	show_stacks(stack_a, stack_b, "A/// Before ps_to_b"); // DEBUG
	ps_to_b(stack_a, stack_b, cmd_list);
//	show_stacks(stack_a, stack_b, "B/// After ps_to_b"); // DEBUG
	ps_to_a(stack_a, stack_b, cmd_list);
//	show_stacks(stack_a, stack_b, "C/// After ps_to_a"); // DEBUG
	return ;
}
/*
	size_t	mid_val;
	size_t	i;

//	show_stacks(stack_a, stack_b, "Before sort"); // DEBUG
	while (stack_a->nb_elem > 3)
	{
		i = stack_a->nb_elem - 1;
		mid_val = get_median(stack_a);
	//	ft_printf("MID_VAL: %d\n", mid_val);	
		while (stack_a->lowest != (int)mid_val) //mid_val < stack_a->len && i < stack_a->nb_elem)
		{
			if (stack_a->index_map[stack_a->nb_elem - 1] < (int)mid_val)
			{
				pusher(stack_b, stack_a, cmd_list, "pb");
//				show_stacks(stack_a, stack_b, "PB"); // DEBUG
				if (stack_b->index_map[0] > stack_b->index_map[stack_b->nb_elem - 1])
				{	
					rotater(stack_b, cmd_list, "rb");
//					show_stacks(stack_a, stack_b, "RB"); // DEBUG
				}
				if (stack_b->nb_elem > 1 && stack_b->index_map[stack_b->nb_elem - 1] < stack_b->index_map[stack_b->nb_elem - 2])
				{
					swapper(stack_b, cmd_list, "sb");
//					show_stacks(stack_a, stack_b, "SB"); // DEBUG
				}
			}
			else
			{
				rotater(stack_a, cmd_list, "ra");
//				show_stacks(stack_a, stack_b, "RA"); // DEBUG
			}
			i++;
			find_lowest(stack_a);
	//		ft_printf("lowest: %d\n", stack_a->lowest);
			if (stack_a->lowest == (int)mid_val)
				break ;
		}
	}
	if (is_ordered(stack_a, 'd') != 0)
		sort_three_a(stack_a, cmd_list);
//	show_stacks(stack_a, stack_b, "After sorting 3a"); // DEBUG

	int nb_rot = 0;

	while (stack_b->nb_elem > 0)
	{
		nb_rot = 0;
	//	ft_printf("top b = %d - top a = %d", stack_b->index_map[stack_b->nb_elem - 1], stack_a->index_map[stack_a->nb_elem - 1]);
		if (stack_b->index_map[stack_b->nb_elem - 1] == ((stack_a->index_map[stack_a->nb_elem - 1] - 1)))
		{
			pusher(stack_a, stack_b, cmd_list, "pa");
			while (nb_rot > 1)
			{
				reverse_rotater(stack_b, cmd_list, "rrb");
				nb_rot--;	
			}
//			show_stacks(stack_a, stack_b, "PA"); // DEBUG
		}
		else
		{
			nb_rot++;
			rotater(stack_b, cmd_list, "rb");	
//			show_stacks(stack_a, stack_b, "RA"); // DEBUG
		}
		//if (stack_a->index_map[stack_a->nb_elem - 1] > stack_a->index_map[stack_a->nb_elem - 2])
		//{
		//	swapper(stack_a, cmd_list, "sa");
		//	show_stacks(stack_a, stack_b, "SA"); // DEBUG
		//}
	}
//	show_stacks(stack_a, stack_b, "End sort"); // DEBUG
}




	size_t	mid_val;
	int		dist;
	size_t	i;

	mid_val = get_median(stack_a);
	ft_printf("MID_VAL: %d\n", mid_val);
	
	// push to b
	while (is_ordered(stack_a, 'd') != 0 && stack_a->nb_elem > 3)
	{
		i = 0;
		while (i < stack_a->nb_elem)
		{
			if (stack_a->index_map[i] < (int)mid_val)
			{
				dist = get_shortest_dist(stack_a->index_map, stack_a->nb_elem, stack_a->index_map[i]);
				ft_printf("DIST: %d\n", dist); // DEBUG
				while (dist != 0) // get the abs, take the sign into account
				{
					if (dist > 0)
					{
						ft_printf("DIST > 0! cmd: ra\n"); // DEBUG
						rotater(stack_a, cmd_list, "ra");
						dist--;
					}
					else if (dist < 0)
					{	
						ft_printf("DIST < 0! cmd: rra\n"); // DEBUG
						reverse_rotater(stack_a, cmd_list, "rra");
						dist++;
					}
					ft_printf("DIST back to 0! cmd: pb\n");
				}
				pusher(stack_b, stack_a, cmd_list, "pb");
				show_stacks(stack_a, stack_b, "[ft_sort, after pb]"); // DEBUG
			}
			else
				rotater(stack_a, cmd_list, "ra");
			i++;
		}
		mid_val = get_median(stack_a);
		if (stack_a->nb_elem == 3)
		{
			ft_printf("3 ELEM IN A! TESTING ORDER...\n");
			ft_printf("is_ordered: %d\n", is_ordered(stack_a, 'd'));
			if (is_ordered(stack_a, 'd') != 0)
			{
				ft_printf("A NON ORDERED! Ordering...\n");
				sort_three_a(stack_a, cmd_list); // Need to review...
			}
			break ;
		}
		ft_printf("MID_VAL: %d\n", mid_val);
	}
	// push_to_a
	while (stack_b->nb_elem > 3)
	{
		i = (stack_b->nb_elem) - 1;
		while (i > 0 && stack_b->index_map[i] != (stack_a->index_map[stack_a->nb_elem - 1]) - 1)
			i--;
		ft_printf("top_a: %d - ind next in b: %d\n", stack_a->index_map[stack_a->nb_elem - 1], i); // DEBUG
      		while (stack_b->index_map[stack_b->nb_elem - 1] != (stack_a->index_map[stack_a->nb_elem - 1]) - 1)
		{
			if (stack_b->index_map[i] == stack_a->index_map[i] - 1)
                		swapper(stack_b, cmd_list, "sb");
			rotater(stack_b, cmd_list, "rb");
			i++;
		}
		show_stacks(stack_a, stack_b, "[ft_sort, during pa"); // DEBUG	
        	pusher(stack_a, stack_b, cmd_list, "pa");
		show_stacks(stack_a, stack_b, "[ft_sort, during pa]"); // DEBUG
	}
	if (is_ordered(stack_b, 'a') != 0 && stack_b->nb_elem > 1)
		sort_three_b(stack_b, cmd_list);
	show_stacks(stack_a, stack_b, "[ft_sort, after sort_3_b]"); // DEBUG
	while (stack_b->nb_elem > 0)
		pusher(stack_a, stack_b, cmd_list, "pa");
	show_stacks(stack_a, stack_b, "[ft_sort, end sort]"); // DEBUG
	if (stack_a->index_map[stack_a->nb_elem - 1] > stack_a->index_map[stack_a->nb_elem - 2])
                swapper(stack_a, cmd_list, "sa");
	show_stacks(stack_a, stack_b, "[ft_sort, end sort if swap needed]"); // DEBUG
	return ;
}*/

/*
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
*/
