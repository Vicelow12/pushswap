#include "../../push_swap.h"


int	main(int argc, char **argv)
{
	stack	*a;
	stack	*b;
	size_t	nb_node;
	char	**tab;

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
	if (is_sorted(&a) == 1)
		ft_printf("ok");
	free_stack(&a);
	return (0);
}
