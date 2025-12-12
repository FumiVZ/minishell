/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:00:31 by machrist          #+#    #+#             */
/*   Updated: 2024/07/15 16:56:17 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	return (0);
}

static void	change_last_line(t_env *env, char *line)
{
	if (!env->free_line)
	{
		env->free_line = line;
		add_history(line);
		return ;
	}
	if (ft_strncmp(env->free_line, line, ft_strlen(line)))
		add_history(line);
	free(env->free_line);
	env->free_line = line;
}

bool	ft_add_history(t_env *env, char *line)
{
	size_t	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		return (false);
	}
	if (i == 0)
	{
		change_last_line(env, line);
		return (true);
	}
	if (env->free_line)
		free(env->free_line);
	env->free_line = line;
	return (true);
}
