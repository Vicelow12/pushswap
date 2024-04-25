/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:21:46 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 19:23:10 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

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
			free_error(a, argv);
		i++;
	}
	create_stack(a, argv, nb_node, j);
	free_split(argv);
	if (!check_duplicate(a))
		free_error(a, NULL);
}

void	create_stack(stack **a, char **argv, size_t argc, size_t i)
{
	stack	*new_node;
	stack	*cur;
	int		check;

	while (i < argc)
	{
		check = ft_atoi(argv[i], a, argv);
		new_node = malloc(sizeof(stack));
		if (!new_node)
			free_error(a, argv);
		new_node->next = NULL;
		new_node->node = check;
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
		if (index > nb_node)
			nb_node = index;
		index = 1;
		cur = cur->next;
	}
	return (nb_node);
}

char	**create_tab(char **tab, char **argv, int argc)
{
	size_t	i;

	i = 0;
	tab = malloc(sizeof(char *) * (argc));
	if (!tab)
		return (0);
	while ((int)i < argc - 1)
	{
		tab[i] = ft_strdup(argv[i + 1]);
		if (!tab[i])
		{
			free_error(NULL, tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
