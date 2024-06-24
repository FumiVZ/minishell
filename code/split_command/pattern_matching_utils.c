/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:26:52 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/24 18:35:30 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**insert_tab(char **str, char **add_str, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_str;

	if (!add_str)
		return (NULL);
	new_str = malloc(sizeof(char *) * (ft_strstrlen(str) + ft_strstrlen(add_str)
				+ 1));
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
