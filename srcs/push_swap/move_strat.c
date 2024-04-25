/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_strat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:21:41 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 17:35:56 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	move_1(stack **a, stack	**b, stack *cheapest)
{
	while (cheapest->pos > 0 && cheapest->target->pos > 0)
	{
		rr(a, b);
		cheapest->pos--;
		cheapest->target->pos--;
	}
	while (cheapest->pos > 0)
	{
		ra(a);
		cheapest->pos--;
	}
	while (cheapest->target->pos > 0)
	{
		rb(b);
		cheapest->target->pos--;
	}
}

void	move_2(stack **a, stack	**b, stack *cheapest)
{
	size_t	len_a;
	size_t	len_b;

	len_a = count_elem(a);
	len_b = count_elem(b);
	while (cheapest->pos < (int)len_a && cheapest->target->pos < (int)len_b)
	{
		rrr(a, b);
		cheapest->pos++;
		cheapest->target->pos++;
	}
	while (cheapest->pos < (int)len_a)
	{
		rra(a);
		cheapest->pos++;
	}
	while (cheapest->target->pos < (int)len_b)
	{
		rrb(b);
		cheapest->target->pos++;
	}
}

void	move_3(stack **a, stack	**b, stack *cheapest)
{
	size_t	len_b;

	len_b = count_elem(b);
	while (cheapest->pos > 0)
	{
		ra(a);
		cheapest->pos--;
	}
	while (cheapest->target->pos < (int)len_b)
	{
		rrb(b);
		cheapest->target->pos++;
	}
}

void	move_4(stack **a, stack	**b, stack *cheapest)
{
	size_t	len_a;

	len_a = count_elem(a);
	while (cheapest->pos < (int)len_a)
	{
		rra(a);
		cheapest->pos++;
	}
	while (cheapest->target->pos > 0)
	{
		rb(b);
		cheapest->target->pos--;
	}
}

void	min_on_top(stack **a)
{
	while ((*a)->node != find_min(a)->node)
	{
		if (find_min(a)->above_median)
			ra(a);
		else
			rra(a);
	}
}
