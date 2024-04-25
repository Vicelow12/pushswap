#include "../../push_swap.h"

void	move_b_to_a(stack	**a, stack **b)
{
	stack	*cur_b;
	size_t	len_a;

	cur_b = *b;
	len_a = count_elem(a);
	if (cur_b->target->above_median == 1)
	{
		while (cur_b->target->pos > 0)
		{
			ra(a);
			cur_b->target->pos--;
		}
	}
	else if (cur_b->target->above_median == 0)
	{
		while (cur_b->target->pos < (int)len_a)
		{
			rra(a);
			cur_b->target->pos++;
		}
	}
	pa(b, a);
}

stack	*get_cheapest(stack **stk)
{
	stack	*cur;

	cur = *stk;
	if (!cur)
		return (NULL);
	while (cur != NULL)
	{
		if (cur->cheapest == 1)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	move_a_to_b(stack	**a, stack	**b)
{
	stack	*cheapest;

	cheapest = get_cheapest(a);
	if (cheapest->move_strat == 1)
		move_1(a, b, cheapest);
	else if (cheapest->move_strat == 2)
		move_2(a, b, cheapest);
	else if (cheapest->move_strat == 3)
		move_3(a, b, cheapest);
	else if (cheapest->move_strat == 4)
		move_4(a, b, cheapest);
	pb(a, b);
}

void	push_cost_below_median(stack *cur_a, size_t len_a, size_t len_b)
{
	cur_a->push_cost = (int)len_a - cur_a->pos;
	cur_a->move_strat = 2;
	if ((cur_a->target->above_median == 0) && (((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) > 0))
	{
		cur_a->push_cost += ((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos);
	}
	else if (cur_a->target->above_median == 1)
	{
		if ((((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) < (cur_a->target->pos))
			&& (((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) > 0))
		{
			cur_a->push_cost += ((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos);
		}
		else if((((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) >= (cur_a->target->pos)))
		{
			cur_a->push_cost += (cur_a->target->pos);
			cur_a->move_strat = 4;
		}
	}
}

void	push_cost_above_median(stack *cur_a, size_t len_b)
{
	cur_a->push_cost = cur_a->pos;
	cur_a->move_strat = 1;
	if ((cur_a->target->above_median == 1)
		&& ((cur_a->target->pos - cur_a->pos) > 0))
	{
		cur_a->push_cost += cur_a->target->pos - cur_a->pos;
	}
	else if (cur_a->target->above_median == 0)
	{
		if ((cur_a->target->pos - cur_a->pos < (int)len_b - cur_a->target->pos)
			&& (cur_a->target->pos - cur_a->pos > 0))
		{
			cur_a->push_cost += cur_a->target->pos - cur_a->pos;
		}
		else if ((cur_a->target->pos - cur_a->pos) >= ((int)len_b - cur_a->target->pos))
		{
			cur_a->push_cost += len_b - cur_a->target->pos;
			cur_a->move_strat = 3;
		}
	}
}
