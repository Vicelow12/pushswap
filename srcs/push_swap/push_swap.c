/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:21:37 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 19:20:15 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

char	**init_arg(int argc, char **argv, char **tab)
{
	if (argc == 1)
		exit (1);
	else if (argc == 2 && argv[1][0] == '\0')
		free_error(NULL, NULL);
	else if (argc == 2)
	{
		tab = ft_split(argv[1], ' ');
		if (!tab[0])
			free_error(NULL, tab);
	}
	else
		tab = create_tab(tab, argv, argc);
	return (tab);
}

int	main(int argc, char **argv)
{
	stack	*a;
	stack	*b;
	size_t	nb_node;
	char	**tab;

	tab = NULL;
	a = NULL;
	b = NULL;
	tab = init_arg(argc, argv, tab);
	init_stack(&a, tab);
	nb_node = set_index(&a);
	if (nb_node == 2 && is_sorted(&a) == 0)
		sa(&a);
	else if (nb_node == 3 && is_sorted(&a) == 0)
		sort_three(&a);
	else if (is_sorted(&a) == 0)
		sort_stack(&a, &b, nb_node);
	free_stack(&a);
	return (0);
}
