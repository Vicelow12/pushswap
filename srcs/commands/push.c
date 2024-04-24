#include "../../push_swap.h"

void	push(stack **src, stack** dest)
{
	stack	*cur;

	if (*src == NULL)
		return;

	cur = *src;
	*src = (*src)->next;
	cur->next = *dest;
	*dest = cur;
}

void	pa(stack **b, stack** a)
{
	push(b, a);
	ft_printf("pa\n");
}

void	pb(stack **a, stack** b)
{
	push(a, b);
	ft_printf("pb\n");
}