/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:34:11 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 19:31:32 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef struct stack
{
	int				node;
	struct stack	*next;
	size_t			index;
	int				pos;
	int				above_median;
	struct stack	*target;
	size_t			push_cost;
	int				cheapest;
	int				move_strat;
}	stack;

int		is_sorted(stack	**stk);
void	sort_three(stack **stk);
void	free_split(char **argv);
size_t	count_elem(stack **stk);
void	reverse_rotate(stack **stk);
void	rra(stack **a);
void	rrb(stack **b);
void	rrr(stack **a, stack **b);
void	rotate(stack **stk);
void	ra(stack **a);
void	rb(stack **b);
void	rr(stack **a, stack **b);
void	push(stack **src, stack **dest);
void	pa(stack **b, stack **a);
void	pb(stack **a, stack **b);
void	swap(stack **stk);
void	sa(stack **a);
void	sb(stack **b);
void	ss(stack **a, stack **b);
int		check_duplicate(stack	**a);
int		check_arg(char	*arg);
void	free_stack(stack **a);
void	free_error(stack	**a, char **tab);
void	create_stack(stack **a, char **argv, size_t argc, size_t i);
void	sort_stack(stack **a, stack **b, size_t nb_node);
size_t	set_index(stack **a);
void	init_a(stack **a, stack **b);
void	set_pos(stack **a);
void	set_target(stack **a, stack **b);
stack	*find_max(stack **stk);
void	set_push_cost(stack **a, stack **b);
void	push_cost_above_median(stack *cur_a, size_t len_b);
void	push_cost_below_median(stack *cur_a, size_t len_a, size_t len_b);
void	set_cheapest(stack **stk);
void	move_a_to_b(stack	**a, stack	**b);
stack	*get_cheapest(stack **stk);
void	init_b(stack **a, stack **b, size_t nb_node);
void	set_target_b(stack **a, stack **b, size_t nb_node);
stack	*find_min(stack **stk);
void	move_b_to_a(stack	**a, stack **b);
void	min_on_top(stack **a);
void	init_stack(stack **a, char **argv);
char	**create_tab(char **tab, char **argv, int argc);
size_t	ft_strlen(char *str);
size_t	nb_nodes(char **argv);
char	**ft_split(char const *s, char c);
void	move_1(stack **a, stack	**b, stack *cheapest);
void	move_2(stack **a, stack	**b, stack *cheapest);
void	move_3(stack **a, stack	**b, stack *cheapest);
void	move_4(stack **a, stack	**b, stack *cheapest);
char	**init_arg(int argc, char **argv, char **tab);
int		ft_atoi(const char *nptr, stack **a, char **argv);

#endif