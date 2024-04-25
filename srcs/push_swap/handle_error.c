/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:22:02 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 19:23:36 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

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
			else if (i != 0)
				return (0);
		}
		else
			digit++;
		i++;
	}
	if (digit == 0)
		return (0);
	return (1);
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
				return (0);
			check = check->next;
		}
		check = *a;
		cur = cur->next;
	}
	return (1);
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
	*a = NULL;
}

void	free_split(char **argv)
{
	size_t	i;

	i = nb_nodes(argv);
	while (i > 0)
	{
		i--;
		if (argv[i] != NULL)
			free(argv[i]);
	}
	free(argv);
}

void	free_error(stack	**a, char **tab)
{
	if (tab != NULL)
		free_split(tab);
	if (a != NULL)
		free_stack(a);
	ft_printf("Error\n");
	exit(1);
}
