/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:28:09 by machrist          #+#    #+#             */
/*   Updated: 2024/06/25 22:35:32 by machrist         ###   ########.fr       */
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
	return (tab);
}

static void   do_nothing(void *content)
{
	(void)content;
}

char	**sort_result(t_list **result, char **str, size_t i)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (ft_lstsize(*result) + 1));
	if (!tab)
	{
		ft_lstclear(result, free);
		return (msg_err_ptr(MALLOC));
	}
	tab = list_to_tab(result, tab);
	ft_lstclear(result, do_nothing);
	free(result);
	// ascii_sort(tab);
	free(str[i]);
	tab = insert_tab(str, tab, i);
	return (tab);
}

