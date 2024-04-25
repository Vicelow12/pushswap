/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:21:39 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 17:21:50 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

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
	return (i);
}

size_t	nb_nodes(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
	{
		i++;
	}
	return ((int)i);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

stack	*find_max(stack **stk)
{
	stack	*cur;
	stack	*mem;

	cur = *stk;
	mem = *stk;
	while (cur != NULL)
	{
		if (cur->index > mem->index)
			mem = cur;
		cur = cur->next;
	}
	return (mem);
}

stack	*find_min(stack **stk)
{
	stack	*cur;
	stack	*mem;

	cur = *stk;
	mem = *stk;
	while (cur != NULL)
	{
		if (cur->index < mem->index)
			mem = cur;
		cur = cur->next;
	}
	return (mem);
}
