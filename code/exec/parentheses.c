/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:42:53 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/27 18:48:27 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**allocate_and_copy(char **str, t_pipex *pipex, int size_reduction)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(sizeof(char *) * (ft_strstrlen(str) - size_reduction + 1));
	if (!new)
		msg_error(ERR_MALLOC, pipex);
	i = 0;
	j = 0;
	while (str[i] && ft_strncmp(str[i], "&&", 2) && ft_strncmp(str[i], "||", 2))
	{
		if (str[i][0] != '(' && str[i][0] != ')')
		{
			new[j] = ft_strdup(str[i]);
			if (!new[j])
			{
				free_split(new, j);
				msg_error(ERR_MALLOC, pipex);
			}
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**delete_parentheses(char **str, t_pipex *pipex)
{
	int	i;
	int	size_reduction;

	i = -1;
	while (str[++i] \
		&& ft_strncmp(str[i], "&&", 2) && ft_strncmp(str[i], "||", 2))
	{
		if (str[i][0] == '(' || str[i][0] == ')')
		{
			if (str[i][0] == '(' || str[i][0] == ')')
				size_reduction = 1;
			else
				size_reduction = 0;
			return (allocate_and_copy(str, pipex, size_reduction));
		}
	}
	return (NULL);
}
