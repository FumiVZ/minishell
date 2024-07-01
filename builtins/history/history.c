/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/01 16:56:58 by machrist         ###   ########.fr       */
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
	size_t	i;
	size_t	j;

	j = 0;
	while (line[j] && is_space(line[j]))
		j++;
	if (!env->last_line)
	{
		env->last_line = line;
		add_history(line + j);
		return ;
	}
	i = 0;
	while (env->last_line[i] && is_space(env->last_line[i]))
		i++;
	if (ft_strncmp(env->last_line + i, line + j, ft_strlen(line + j)))
		add_history(line + j);
	free(env->last_line);
	env->last_line = line;
}

bool	ft_add_history(t_env *env, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		return (false);
	}
	j = i;
	while (line[j] && !is_space(line[j]))
		j++;
	if ((i != 0 && !line[j]) || i == 0)
	{
		change_last_line(env, line);
		return (true);
	}
	env->free_line = line;
	return (true);
}
