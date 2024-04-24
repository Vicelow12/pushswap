#include "../../push_swap.h"

void	min_on_top(stack **a)
{
	while((*a)->node != find_min(a)->node)
	{
		if (find_min(a)->above_median)
			ra(a);
		else
			rra(a);
	}
}
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
stack	*find_min(stack **stk)
{
	stack	*cur;
	stack	*mem;

	cur = *stk;
	mem = *stk;
	while (cur != NULL)
	{
		if  (cur->index < mem->index)
			mem = cur;
		cur = cur->next;
	}
	return(mem);
}

void	set_target_b(stack **a, stack **b, size_t nb_node)
{
	stack	*cur_a;
	stack	*cur_b;
	size_t	best_match_index;
	int		check;

	cur_b = *b;
	cur_a = *a;
	best_match_index = nb_node;
	check = 0;
	while(cur_a != NULL)
	{
		if (cur_a->index > cur_b->index && cur_a->index <= best_match_index)
		{
			best_match_index = cur_a->index;
			cur_b->target = cur_a;
			check = 1;
		}
		cur_a = cur_a->next;
	}
	if (check == 0)
		cur_b->target = find_min(a);
}
void	init_b(stack **a, stack **b, size_t nb_node)
{
	set_pos(a);
	set_pos(b);
	set_target_b(a, b, nb_node);
}
stack	*get_cheapest(stack **stk)
{
	stack *cur;

	cur = *stk;
	if(!cur)
		return (NULL);
	while (cur != NULL)
	{
		if (cur->cheapest == 1)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
void	move_1(stack **a, stack	**b, stack *cheapest)
{
	while(cheapest->pos > 0 && cheapest->target->pos >0)
		{
			rr(a,b);
			cheapest->pos--;
			cheapest->target->pos--;
		}
		while(cheapest->pos > 0)
		{
			ra(a);
			cheapest->pos--;
		}
		while(cheapest->target->pos >0)
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
	while(cheapest->pos < (int)len_a && cheapest->target->pos < (int)len_b)
	{
		rrr(a,b);
		cheapest->pos++;
		cheapest->target->pos++;
	}
	while(cheapest->pos < (int)len_a)
	{
		rra(a);
		cheapest->pos++;
	}
	while(cheapest->target->pos < (int)len_b)
	{
		rrb(b);
		cheapest->target->pos++;
	}
}

void	move_3(stack **a, stack	**b, stack *cheapest)
{
	size_t	len_b;

	len_b = count_elem(b);
	while(cheapest->pos > 0)
	{
		ra(a);
		cheapest->pos--;
	}
	while(cheapest->target->pos < (int)len_b)
	{
		rrb(b);
		cheapest->target->pos++;
	}
}

void	move_4(stack **a, stack	**b, stack *cheapest)
{
	size_t	len_a;

	len_a = count_elem(a);
	while(cheapest->pos < (int)len_a)
		{
			rra(a);
			cheapest->pos++;
		}
		while(cheapest->target->pos >0)
		{
			rb(b);
			cheapest->target->pos--;
		}
}
void 	move_a_to_b(stack	**a, stack	**b)
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
	

void	set_cheapest(stack **stk)
{
	stack	*cur;
	stack	*cheapest_node;
	size_t	cheapest_value;

	if(!stk)
		return;
	cur = *stk;
	cheapest_node = cur;
	cheapest_value = cur->push_cost;
	while(cur != NULL)
	{
		if (cur->push_cost < cheapest_value)
		{
			cheapest_node = cur;
			cheapest_value = cur->push_cost;
		}
		cur->cheapest = 0;
		cur = cur->next;
	}
	cheapest_node->cheapest = 1;
}
void	push_cost_below_median(stack *cur_a,size_t len_a, size_t len_b)
{
	cur_a->push_cost = (int)len_a - cur_a->pos;
	cur_a->move_strat = 2;
			if((cur_a->target->above_median == 0) && (((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) > 0))
			{
				cur_a->push_cost += ((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos);
			}
			else if(cur_a->target->above_median == 1)
			{
				if((((int)len_b - cur_a->target->pos) - ((int)len_a - cur_a->pos) < (cur_a->target->pos)) 
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
			if((cur_a->target->above_median == 1) && ((cur_a->target->pos - cur_a->pos) > 0))
			{
				cur_a->push_cost += cur_a->target->pos - cur_a->pos;
			}
			else if(cur_a->target->above_median == 0)
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

void	set_push_cost(stack **a, stack **b)
{
	size_t	len_a;
	size_t	len_b;
	stack	*cur_a;

	len_a = count_elem(a);
	len_b = count_elem(b);
	cur_a = *a;
	while(cur_a != NULL)
	{
		if(cur_a->above_median == 1)
			push_cost_above_median(cur_a, len_b);
		else
			push_cost_below_median(cur_a, len_a, len_b);
		cur_a = cur_a->next;
	}
}
stack	*find_max(stack **stk)
{
	stack	*cur;
	stack	*mem;

	cur = *stk;
	mem = *stk;
	while (cur != NULL)
	{
		if  (cur->index > mem->index)
			mem = cur;
		cur = cur->next;
	}
	return(mem);
}

void	set_target(stack **a, stack **b)
{
	stack	*cur_a;
	stack	*cur_b;
	size_t	best_match_index;

	cur_a = *a;
	while (cur_a != NULL)
	{
		best_match_index = 0;
		cur_b = *b;
		while (cur_b != NULL)
		{
			if ((cur_b->index < cur_a->index) && (cur_b->index > best_match_index))
			{
				best_match_index = cur_b->index;
				cur_a->target = cur_b;
			}
			cur_b = cur_b->next;
		}
		if (best_match_index == 0)
			cur_a->target = find_max(b);
		cur_a = cur_a->next;
	}
}
void	set_pos(stack **a)
{
	size_t	pos;
	stack	*cur;
	size_t	median;

	pos = 0;
	cur = *a;
	median = (count_elem(a) + 1) / 2;

	while (cur != NULL)
	{
		if (pos + 1 <= median )
			cur->above_median = 1;
		else
			cur->above_median = 0;
		cur->pos = pos++;
		cur = cur->next;
	}
}
void	init_a(stack **a, stack **b)
{
	set_pos(a);
	set_pos(b);
	set_target(a, b);
	set_push_cost(a, b);
	set_cheapest(a);
}
size_t	set_index(stack **a)
{
	size_t	index;
	stack	*cur;
	stack	*check;
	size_t	nb_node;

	cur = *a;
	index = 1;
	nb_node = 1;

	while (cur != NULL)
	{
		check = *a;
		while (check != NULL)
		{
			if (check->node < cur->node)
				index++;
			check = check->next;
		}
		cur->index = index;
		if(index > nb_node)
			nb_node = index;
		index = 1;
		cur = cur->next;
	}
	return(nb_node);
}
void	sort_stack(stack **a, stack **b, size_t nb_node)
{
	size_t	len_a;

	len_a = count_elem(a) - 1;
	pb(a, b);
	if (len_a-- > 3)
		pb(a, b);
	while (len_a-- > 3)
	{
		init_a(a, b);
		move_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		init_b(a, b, nb_node);
		move_b_to_a(a, b);
	}
	set_pos(a);
	min_on_top(a);
}
int	is_sorted(stack	**stk)
{
	stack	*cur;

	cur = *stk;
	if (!cur)
		return(0);
	while(cur->next != NULL)
	{
		if (cur->node > cur->next->node)
			return (0);
		cur = cur->next;
	}
	return (1);
}
void	sort_three(stack **stk)
{
	stack*	cur;
	stack*	max;
	int		i;

	i = 0;
	cur = *stk;
	max = *stk;
	if (!cur || count_elem(stk) != 3 || is_sorted(stk))
		return;
	while (cur->next != NULL)
	{
		cur = cur->next;
		if (max->node < cur->node)
		{
			max = cur;
			i++;
		}
	}
	if (i == 0)
		ra(stk);
	else if (i == 1)
		rra(stk);
	if (!is_sorted(stk))
		sa(stk);
}

void	free_split(char **argv, int argc)
{
	size_t	i;

	i = 0;
	while (i < (size_t)argc)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
size_t	count_elem(stack **stk)
{
	size_t	i;
	stack	*cur;

	cur = *stk;
	i = 0;
	while (cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	return(i);
}

int	check_duplicate(stack	**a)
{
	stack	*cur;
	stack	*check;
	cur = *a;
	check = *a;
	while (cur != NULL)
	{
		while (check != cur)
		{
			if (check->node == cur->node)
				return(0);
			check = check->next;
		}
		check = *a;
		cur = cur->next;
	}
	return(1);
}
int	check_arg(char	*arg)
{
	size_t	i;
	size_t	digit;

	i = 0;
	digit = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			if (arg[i] != '+' && arg[i] != '-' && arg[i] != ' ')
				return (0);
		}
		else
			digit++;
		i++;
	}
	if (digit == 0)
		return(0);
	return(1);
}

void	free_stack(stack **a)
{
	stack	*cur;
	stack	*mem;

	cur = *a;
	while (cur != NULL)
	{
		mem = cur;
		cur = cur->next;
		free(mem);
	}
}
void	create_stack(stack **a, char **argv, size_t argc, size_t i)
{
	stack	*new_node;
	stack	*cur;

	while (i < argc)
	{
		new_node = malloc(sizeof(stack));
		if (!new_node)
			exit(1);
		new_node->next = NULL;
		new_node->node = ft_atoi(argv[i]);
		if (!*a)
		{
			*a = new_node;
			cur = *a;
		}
		else
		{
			cur->next = new_node;
			cur = cur->next;
		}
		i++;
	}
}
size_t	nb_nodes(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
	{
		i++;
	}
	return((int)i);
}
void	init_stack(stack **a, char **argv)
{
	size_t	i;
	size_t	j;
	size_t	nb_node;
	
	i = 0;
	j = 0;
	nb_node = nb_nodes(argv);
	while (i < nb_node)
	{
		if (!check_arg(argv[i]))
			exit(1);
		i++;
	}
	create_stack(a, argv, nb_node, j);
	free_split(argv, nb_node);
	if (!check_duplicate(a))
		exit(1);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	**create_tab(char **tab, char **argv, int argc)
{
		size_t	i;

		i = 0;
		tab = malloc(sizeof(char *) * (argc));
		if (!tab)
			return (0);
		while((int)i < argc - 1)
		{
			tab[i] = ft_strdup(argv[i + 1]);
			if (!tab[i])
			{
				free_split(tab, i);
				return(NULL);
			}
			i++;
		}
		tab[i] = NULL;
		return (tab);
}
int	main(int argc, char** argv) 
{
    stack   *a;
	stack	*b;
//	stack	*cur;
	size_t	nb_node;
	char	**tab;

	// argc = 7;
	// argv[0] = "b" ;
	// argv[1] = "45 " ;
	// argv[2] = "24852455211511" ;
	// argv[3] = "3" ;
	// argv[4] = "5" ;
	// argv[5] = "4" ;
	// argv[6] = "6" ;
	a = NULL;
	b = NULL;
	tab = NULL;
	
	if (argc == 1 || (argc == 2 && argv[1][0] == '\0'))
		return (1);
	else if (argc == 2)
		tab = ft_split(argv[1], ' ');
	else
		tab = create_tab(tab, argv, argc);
	init_stack(&a, tab);
	nb_node = set_index(&a);
	if (nb_node == 2 && is_sorted(&a) == 0)
		sa(&a);
	else if (nb_node == 3 && is_sorted(&a) == 0)
		sort_three(&a);
	else if (is_sorted(&a) == 0)
		sort_stack(&a, &b, nb_node);

	

	// cur = a;
	// while (cur != NULL)
	// {
	// 	ft_printf("a : %d  ", cur->node);
	// 	ft_printf("pos : %d", cur->pos);
	// 	ft_printf("  med : %d", cur->above_median);
	// 	ft_printf("  target index : %d", cur->target->index);
	// 	ft_printf("  push cost : %d", cur->push_cost);
	// 	ft_printf("  cheap : %d", cur->cheapest);
	// 	ft_printf("  strat : %d", cur->move_strat);
	// 	ft_printf("  ind : %d\n", cur->index);
	// 	cur = cur->next;
	// }
	// cur = b;
	// while (cur != NULL)
	// {
	// 	ft_printf("b : %d  ", cur->node);
	// 	ft_printf("pos : %d", cur->pos);
	// 	ft_printf("  med : %d", cur->above_median);
	// 	//ft_printf("  target index : %d", cur->target->index);
	// 	ft_printf("  push cost : %d", cur->push_cost);
	// 	//ft_printf("  strat : %d", cur->move_strat);
	// 	ft_printf("  ind : %d\n", cur->index);
	// 	cur = cur->next;
	// }
	if (is_sorted(&a) == 1)
		ft_printf("ok");
	free_stack(&a);
    return 0;
}