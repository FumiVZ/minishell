/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:28:09 by machrist          #+#    #+#             */
/*   Updated: 2024/06/27 19:28:22 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ascii_sort(char **tab)
{
	size_t	i;
	size_t	j;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) > 0)
				swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

static char	**list_to_tab(t_list **result, char **tab)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	tmp = *result;
	while (tmp)
	{
		tab[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	if (tab[0] == NULL)
	{
		free(tab);
		tab = malloc(sizeof(char *) * 2);
		if (!tab)
			return (NULL);
		tab[0] = ft_strdup("");
		if (!tab[0])
			return (free(tab), NULL);
		tab[1] = NULL;
		return (tab);
	}
	return (tab);
}

static void	do_nothing(void *content)
{
	(void)content;
}

char	**sort_result(t_list **result, char **str, size_t i)
{
	char	**tab;
	char	*tmp;

	tab = malloc(sizeof(char *) * (ft_lstsize(*result) + 1));
	if (!tab)
	{
		ft_lstclear(result, free);
		free(result);
		return (NULL);
	}
	tab = list_to_tab(result, tab);
	ft_lstclear(result, do_nothing);
	free(result);
	ascii_sort(tab);
	tmp = str[i];
	tab = insert_tab(str, tab, i);
	if (!tab)
	{
		free_split(tab, ft_strstrlen(tab));
		return (NULL);
	}
	free(tmp);
	return (tab);
}
