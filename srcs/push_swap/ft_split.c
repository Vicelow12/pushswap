/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaulthi <ngaulthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:13:42 by ngaulthi          #+#    #+#             */
/*   Updated: 2024/04/25 17:22:10 by ngaulthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static	size_t	count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		fl;

	i = 0;
	count = 0;
	fl = 1;
	while (s[i])
	{
		if (s[i] == c && !fl)
			fl = 1;
		else if (c != s[i] && fl)
		{
			fl = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static	void	*secure_malloc(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		if (tab[i] != NULL)
			free(tab[i]);
	}
	free(tab);
	return ((void *)0);
}

static	char	*malloc_str(char const *s, char c, size_t *step)
{
	size_t	nb_letter;
	char	*str;

	nb_letter = 0;
	while (s[*step] == c)
		*step = *step + 1;
	while (s[*step] != c && s[*step])
	{
		nb_letter++;
		*step = *step +1;
	}
	str = malloc(sizeof(char) * (nb_letter + 1));
	if (!str)
		return (NULL);
	return (str);
}

static	void	tab_fill(const char *s, char c, size_t *step, char *strfill)
{
	size_t	i;

	i = 0;
	while (s[*step] == c)
		*step = *step + 1;
	while (s[*step] != c && s[*step])
	{
		strfill[i] = s[*step];
		i++;
		*step = *step + 1;
	}
	strfill[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		j;
	size_t		step;

	if (!s)
		return (NULL);
	i = 0;
	step = 0;
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	while (i < count_word(s, c))
	{
		j = step;
		tab[i] = malloc_str(s, c, &step);
		if (!tab[i])
			return (secure_malloc(tab, i));
		step = j;
		tab_fill(s, c, &step, tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
