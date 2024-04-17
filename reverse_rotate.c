#include "push_swap.h"
#include "ft_printf.h"

void	reverse_rotate(stack **stk)
{
	stack	*cur;
	stack	*prev_cur;
	stack	*mem;
	size_t	i;

	if (*stk == NULL)
		return;
	cur = *stk;
	prev_cur = *stk;
	mem = cur;
	i = 0;
	while (cur->next != NULL)
	{
		cur = cur->next;
		if (i > 0)
			prev_cur = prev_cur->next;
		i++;
	}
	cur->next = *stk;
	*stk = cur;
	prev_cur->next = NULL;
}

void	rra(stack **a)
{
	reverse_rotate(a);
	ft_printf("rra\n");
}

void	rrb(stack **b)
{
	reverse_rotate(b);
	ft_printf("rrb\n");
}

void	rrr(stack **a, stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
}