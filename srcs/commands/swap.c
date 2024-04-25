#include "../../push_swap.h"

void	swap(stack **stk)
{
	size_t	i;
	int		tmp_node;
	size_t	tmp_index;

	i = count_elem(stk);
	if (i > 1)
	{
		tmp_node = (*stk)->node;
		tmp_index = (*stk)->index;
		(*stk)->node = (*stk)->next->node;
		(*stk)->index = (*stk)->next->index;
		(*stk)->next->node = tmp_node;
		(*stk)->next->index = tmp_index;
	}
}

void	sa(stack **a)
{
	swap(a);
	ft_printf("sa\n");
}

void	sb(stack **b)
{
	swap(b);
	ft_printf("sb\n");
}

void	ss(stack **a, stack **b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}
