#include "push_swap.h"  
#include "ft_printf.h"
#include "libft.h"

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
void 	move_a_to_b(stack	**a, stack	**b)
{
	stack	*cheapest;
	size_t	len_a;
	size_t	len_b;

	len_a = count_elem(a);
	len_b = count_elem(b);
	cheapest = get_cheapest(a);
	if (cheapest->move_strat == 1)
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
	else if (cheapest->move_strat == 2)
	{
		while(cheapest->pos < len_a && cheapest->target->pos < len_b)
		{
			rrr(a,b);
			cheapest->pos++;
			cheapest->target->pos++;
		}
		while(cheapest->pos < len_a)
		{
			rra(a);
			cheapest->pos++;
		}
		while(cheapest->target->pos < len_b)
		{
			rrb(b);
			cheapest->target->pos++;
		}
	}
	else if (cheapest->move_strat == 3)
	{
		while(cheapest->pos > 0)
		{
			ra(a);
			cheapest->pos--;
		}
		while(cheapest->target->pos < len_b)
		{
			rrb(b);
			cheapest->target->pos++;
		}
	}
	else if (cheapest->move_strat == 4)
	{
		while(cheapest->pos < len_a)
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
	int	len_a;



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
	if (!cur || count_elem(stk) != 3)
		return;
	if (is_sorted(stk))
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

void	free_split(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
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
void	create_stack(stack **a, char **argv)
{
	stack	*new_node;
	stack	*cur;
	ssize_t	i;

	i = 0;
	
	while (argv[i] != NULL)
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
			// cur = *a;
			// while (cur->next != NULL)
			// 	cur = cur->next;
			cur->next = new_node;
			cur = cur->next;
		}
		i++;
	}
	
}

int main(int argc, char** argv) 
{
    stack   *a;
	stack	*b;
	stack	*cur;
	size_t	nb_node;

	// argc = 6;
	// argv[1] = " 983 -534 -598 -240 986 257 893 729 678 -34 978 395 625 401 -118 -656 405 319 -577 -233 413 -172 -674 348 -802 428 754 780 -425 394 -202 -837 840 -459 -646 -88 -401 -819 -471 885 -373 -474 554 -349 353 -675 -326 673 199 138 414 -468 -831 -137 976 755 -666 -439 -561 834 -315 83 101 -662 -493 914 -782 141 -896 373 708 931 249 483 407 -352 -985 830 567 -925 54 -524 74 734 831 909 23 64 71 204 130 -975 655 163 -231 191 -190 -398 314 122 901 -84 547 87 985 -171 0 511 378 -563 737 676 969 -226 -521 -777 -407 -791 -444 654 -215 -965 677 -70 887 -266 -977 231 86 -419 72 699 -181 728 -574 170 193 -375 -735 702 -119 -870 -54 410 -867 658 -247 942 -308 739 -440 720 -706 -856 37 224 903 -982 -718 513 352 367 -681 374 57 82 -719 -301 13 -864 941 294 717 506 768 452 117 911 321 -639 864 680 -973 -477 -93 -63 -957 -807 -142 44 951 -618 -509 -535 650 -725 -657 383 -391 -243 229 804 -920 -33 -331 -219 -105 512 30 -3 549 -752 167 -806 -31 -436 -463 859 148 925 -416 583 696 255 -242 -381 420 -465 -64 897 771 -597 -151 266 -602 557 -485 765 787 614 92 528 -410 -293 -152 327 473 -188 -548 642 -265 -686 411 447 -555 609 -940 884 -71 808 492 -145 -586 248 -193 561 -809 -883 604 -838 -665 -652 798 -767 444 -750 133 -422 -45 -121 711 295 698 516 -96 228 -692 361 -344 60 58 533 -139 530 416 -251 -710 302 -788 727 606 918 865 -701 -76 -530 -184 -101 16 -192 -591 612 -222 -280 -437 -826 338 159 -338 -81 345 -607 682 709 172 143 -26 748 622 189 196 -877 -567 438 -522 505 872 -125 -811 -189 636 -879 926 566 212 -651 -590 -387 701 685 277 -354 381 -4 735 934 803 -250 392 183 448 -878 -367 18 -822 -340 767 -399 827 -85 -792 904 -611 442 793 -785 -212 -149 300 309 -770 -741 476 958 -805 -237 285 -909 209 -316 563 126 -227 860 -36 280 -299 -421 461 252 -43 -158 -572 -745 45 -960 -467 168 800 102 -455 721 548 569 -714 -22 -553 -582 -372 621 -562 -319 169 417 535 921 -332 757 -20 106 -201 -9 749 564 704 265 661 206 33 -178 -950 478 301 591 -307 -941 841 -175 -918 286 -872 -728 -898 -397 -687 -672 -89 842 776 -934 422 -529 258 187 -102 -323 -916 480 -413 390 -211 -460 603 -229 -314 805 -833 -661 -14 -108 -626 -312 -183 -255 -882 848 -128 -525 -818 -997 -994 995 19 208 930 -778 618 -490 -746 457";
	if (argc == 1 || (argc == 2 && argv[1][0] == '\0'))
		return (1);
    a = NULL;
	b = NULL;
	
	if (!check_arg(argv[1]))
		exit(1);
	argv = ft_split(argv[1], ' ');
	create_stack(&a, argv);
	free_split(argv);
	if (!check_duplicate(&a))
		exit(1);
	nb_node = set_index(&a);

	// sa(&a);
	// ra(&a);
	// rra(&a);
	// sort_three(&a);
	// pb(&a, &b);
	// pb(&a, &b);
	// sb(&b);
	// pb(&a, &b);
	// pb(&a, &b);
	// sb(&b);
	// pb(&a, &b);
	// pb(&a, &b);
	// // pa(&a, &b);
	// sb(&b);
	// rb(&b);
	// sb(&b);
	// rb(&b);
	// pb(&a, &b);
	// pb(&a, &b);
	// rrb(&b);
	// rrr(&a, &b);
	// rr(&a, &b);
	// ss(&a, &b);
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
	// if (is_sorted(&a) == 1)
	// 	ft_printf("ok");
	// while (argv[i] != NULL)
	// {
	// 	ft_printf("%s\n", argv[i]);
	// 	i++;
	// }
	free_stack(&a);


    // printf("Number of command-line arguments: %d\n", argc);
    // printf("Program name: %s\n", argv[0]);
    // for (int i = 1; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, argv[i]);
    // }
    return 0;
}