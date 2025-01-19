/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:48:27 by mmalie            #+#    #+#             */
/*   Updated: 2025/01/19 23:23:08 by mmalie           ###   ########.fr       */
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

/* NB: This function is called only if the stack is not ordered.
// Must be replaced by sort_three
void    handle_small_stack(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
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
        //      sa(stack_a, cmd_list);
}
*/

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
//        ft_printf("[sort_3_a] stack_a highest_pos: %d - lowest_pos: %d\n", stack_a->highest_pos, stack_a->lowest_pos);
        if ((stack_a->highest_pos == 1 && stack_a->lowest_pos == 2)
                || (stack_a->highest_pos == 2 && stack_a->lowest_pos == 0))
                swapper(stack_a, cmd_list, "sa");
        //if (stack_a_a->highest_pos == 0 && stack_a_a->lowest_pos == 1)
        //      sa(stack_a_a, cmd_list);
}

void    sort_three_b(t_stack *stack_b, t_list *cmd_list)
{
        find_highest(stack_b);
	find_lowest(stack_b);
//	ft_printf("stack_b[0] %d - stack_b[1] %d", stack_b->index_map[0], stack_b->index_map[1]);
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
        //ft_printf("stack_b highest_pos: %d - lowest_pos: %d\n", stack_b->highest_pos, stack_b->lowest_pos);
        if ((stack_b->lowest_pos == 1 && stack_b->highest_pos == 2)
                || (stack_b->lowest_pos == 2 && stack_b->highest_pos == 0))
                swapper(stack_b, cmd_list, "sb");
        //if (stack_b->highest_pos == 0 && stack_b->lowest_pos == 1)
        //      sa(stack_b_a, cmd_list);
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
void	ps_sort(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
	size_t	mid_val;
	size_t	unpushed;
	int		dist;
	size_t	i;

	mid_val = (stack_a->len) / 2;
	unpushed = stack_a->len;
//	ft_printf("MID_VAL: %d\n", mid_val);
	// push to b
	while (is_ordered(stack_a, 'd') != 0 && mid_val < stack_a->len)
	{	
		while (unpushed > 3)
		{
			dist = get_shortest_dist(stack_a->index_map, stack_a->nb_elem, mid_val);
//			ft_printf("DIST: %d\n", dist); // DEBUG
			while (dist != 0) // get the abs, take the sign into account
			{
				if (dist > 0)
				{
//					ft_printf("DIST > 0! cmd: ra\n"); // DEBUG
					rotater(stack_a, cmd_list, "ra");
					dist--;
				}
				else if (dist < 0)
				{	
//					ft_printf("DIST < 0! cmd: rra\n"); // DEBUG
					reverse_rotater(stack_a, cmd_list, "rra");
					dist++;
				}
			}
//			ft_printf("DIST back to 0! cmd: pb\n");
			pusher(stack_b, stack_a, cmd_list, "pb");
			unpushed--;
//			show_stacks(stack_a, stack_b, "[ft_sort, after pb]"); // DEBUG
			if (stack_a->nb_elem == 3)
			{
//				ft_printf("3 ELEM IN A! TESTING ORDER...\n");
//				ft_printf("is_ordered: %d\n", is_ordered(stack_a, 'd'));
				if (is_ordered(stack_a, 'd') != 0)
				{
//					ft_printf("A NON ORDERED! Ordering...\n");
					sort_three_a(stack_a, cmd_list); // Need to review...
				}
				break ;
			}
			if (unpushed == mid_val)
				break ;

		}
		mid_val = mid_val + (mid_val / 2);
//		ft_printf("MID_VAL: %d\n", mid_val);
	}
	// push_to_a
	while (stack_b->nb_elem > 3)
	{
		i = (stack_b->nb_elem) - 1;
		while (i > 0 && stack_b->index_map[i] != (stack_a->index_map[stack_a->nb_elem - 1]) - 1)
			i--;
//		ft_printf("top_a: %d - ind next in b: %d\n", stack_a->index_map[stack_a->nb_elem - 1], i); // DEBUG
      		while (stack_b->index_map[stack_b->nb_elem - 1] != (stack_a->index_map[stack_a->nb_elem - 1]) - 1)
		{
			if (stack_b->index_map[i] == stack_a->index_map[i] - 1)
                		swapper(stack_b, cmd_list, "sb");
			rotater(stack_b, cmd_list, "rb");
			i++;
		}
//		show_stacks(stack_a, stack_b, "[ft_sort, during pa"); // DEBUG	
        	pusher(stack_a, stack_b, cmd_list, "pa");
//		show_stacks(stack_a, stack_b, "[ft_sort, during pa]"); // DEBUG
	}
	if (is_ordered(stack_b, 'a') != 0 && stack_b->nb_elem > 1)
		sort_three_b(stack_b, cmd_list);
//	show_stacks(stack_a, stack_b, "[ft_sort, after sort_3_b]"); // DEBUG
	while (stack_b->nb_elem > 0)
		pusher(stack_a, stack_b, cmd_list, "pa");
//	show_stacks(stack_a, stack_b, "[ft_sort, end sort]"); // DEBUG
	if (stack_a->index_map[stack_a->nb_elem - 1] > stack_a->index_map[stack_a->nb_elem - 2])
                swapper(stack_a, cmd_list, "sa");
//	show_stacks(stack_a, stack_b, "[ft_sort, end sort if swap needed]"); // DEBUG
	return ;
}

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

/* Returns the shortest distance. Its sign indicates the direction:
 * - pos val: from the end of array
 * - neg val: from the start of array
 * This function should NOT be relied on if there is no more nb to be found.
 */
int     get_shortest_dist(int *arr, size_t len, int mid_val)
{
        size_t     dist_from_end;
        size_t     dist_from_start;
        size_t  i;
        size_t  j;

        i = 1; // I start at 1 for less calc
        while ((i < len) && (arr[len - i] >= mid_val))
                i++;
        dist_from_end = i - 1;
        if (dist_from_end == 0)
                return (0);
        j = 0;
        dist_from_start = 1;
        while ((j < dist_from_end) && (arr[j] >= mid_val))
                j++;
        dist_from_start = dist_from_start + j;
        if (dist_from_end < dist_from_start)
                return (dist_from_end);
        else
                return (dist_from_start * (-1));
}

