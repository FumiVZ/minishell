/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:26:52 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/26 20:39:16 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**init_tab(char **str, char **add_str)
{
	char	**new_str;

	if (!add_str)
		return (NULL);
	new_str = malloc(sizeof(char *) * (ft_strstrlen(str) + ft_strstrlen(add_str)
				+ 1)); // valide
	if (!new_str)
	{
		free_split(add_str, ft_strstrlen(add_str));
		return (NULL);
	}
	return (new_str);
}

char	**insert_tab(char **str, char **add_str, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_str;

	new_str = init_tab(str, add_str);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < pos)
		new_str[i++] = str[j++];
	j = 0;
	while (add_str[j])
		new_str[i++] = add_str[j++];
	free(add_str);
	j = pos + 1;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = NULL;
	free(str);
	return (new_str);
}
