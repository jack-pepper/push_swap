/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pusher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:02:17 by mmalie            #+#    #+#             */
/*   Updated: 2024/12/23 20:03:52 by mmalie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pusher(t_stack *stack_dst, t_stack *stack_src)
{
	size_t	nb_dst;
	size_t	nb_src;

	nb_dst = stack_dst->nb_elem;
	nb_src = stack_src->nb_elem;
	if (nb_src != 0)
	{
		stack_dst->content[nb_dst] = stack_src->content[nb_src - 1];
		stack_dst->nb_elem++;
		stack_src->content[nb_src - 1] = 0;
		stack_src->nb_elem--;
	}
}

// pa (push a): Take the first element at the top of b, put it at the top of a.
// Do nothing if b is empty.
void	pa(t_stack *stack_a, t_stack *stack_b, t_list *cmd_list)
{
	t_list	*new_cmd;

	pusher(stack_a, stack_b);
	new_cmd = ft_lstnew("pa");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}

// pb (push b): Take the first element at the top of a, put it at the top of b.
// Do nothing if a is empty.
void	pb(t_stack *stack_b, t_stack *stack_a, t_list *cmd_list)
{
	t_list	*new_cmd;

	pusher(stack_b, stack_a);
	new_cmd = ft_lstnew("pb");
	if (!new_cmd)
		return ;
	ft_lstadd_back(&cmd_list, new_cmd);
	if (!new_cmd)
		return ;
}
