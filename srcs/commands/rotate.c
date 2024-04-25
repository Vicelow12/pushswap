#include "../../push_swap.h"

void	rotate(stack **stk)
{
	stack	*cur;
	stack	*mem;

	if (*stk == NULL)
		return ;
	cur = *stk;
	mem = cur;
	if ((*stk)->next != NULL)
		*stk = (*stk)->next;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = mem;
	mem->next = NULL;
}

void	ra(stack **a)
{
	rotate(a);
	ft_printf("ra\n");
}

void	rb(stack **b)
{
	rotate(b);
	ft_printf("rb\n");
}

void	rr(stack **a, stack **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
