/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:20:39 by vincent           #+#    #+#             */
/*   Updated: 2024/06/19 16:43:52 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**delete_parentheses(char **str, t_pipex *pipex)
{
	int		i;
	int		j;
	char	**new;

	i = -1;
	j = 0;
	while (str[++i] && ft_strncmp(str[i], "&&", 2) \
		&& ft_strncmp(str[i], "||", 2))
	{
		if (str[i][0] == '(')
		{
			new = malloc(sizeof(char *) * (ft_strstrlen(str) - 1));
			if (!new)
				msg_error(ERR_MALLOC, pipex);
			i = 0;
			while ((str[i] && ft_strncmp(str[i], "&&", 2) \
				&& ft_strncmp(str[i], "||", 2)))
			{
				if (str[i][0] != '(' && str[i][0] != ')')
					new[j++] = ft_strdup(str[i]);
				i++;
			}
			new[j] = NULL;
			return (new);
		}
		if (str[i][0] == ')')
		{
			new = malloc(sizeof(char *) * (ft_strstrlen(str)));
			if (!new)
				msg_error(ERR_MALLOC, pipex);
			i = 0;
			while ((str[i] && ft_strncmp(str[i], "&&", 2) \
				&& ft_strncmp(str[i], "||", 2)))
			{
				if (str[i][0] != '(' && str[i][0] != ')')
					new[j++] = ft_strdup(str[i]);
				i++;
			}
			new[j] = NULL;
			return (new);
		}
	}
	return (NULL);
}

//WORK IN PROGRESS