/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:48 by machrist          #+#    #+#             */
/*   Updated: 2024/06/26 15:21:41 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static char	**add_str_env(char **str, t_env *env, size_t i, size_t pos)
{
	char	*tmp;
	char	**new_str;

	tmp = full_str(str[i], get_value(str[i] + pos, env->envp, env), pos);
	free(str[i]);
	if (!tmp)
	{
		free_split(str, ft_strstrlen(str));
		return (NULL);
	}
	if (!*tmp)
		str[i] = tmp;
	else
	{
		new_str = insert_tab(str, ft_word_spliting(tmp, ifs_value(env->envp)),
				i);
		free(tmp);
		if (!new_str)
		{
			free_split(str, ft_strstrlen(str));
			return (NULL);
		}
		str = new_str;
	}
	return (str);
}

static char	**modified_str(char **str, t_env *env, size_t i, long long old_pos)
{
	long long	pos;
	int			check;
	char		*tmp;
	char		**new_str;

	check = check_env_var(str[i], old_pos);
	pos = pos_var(str[i], old_pos);
	if (check == 1)
	{
		tmp = add_var_env(str[i], get_value(str[i] + pos, env->envp, env),
				get_len_name(str[i] + pos) + 1, pos);
		if (!tmp)
			return (NULL);
		free(str[i]);
		str[i] = tmp;
	}
	else if (check == 2)
	{
		new_str = add_str_env(str, env, i, pos);
		if (!new_str)
			return (NULL);
		str = new_str;
	}
	return (str);
}

static long long	ft_new_pos(t_env *env, char *str, long long old_pos)
{
	long long	len;
	char		*tmp;

	if (pos_var(str, old_pos) == -1)
		return (-1);
	tmp = get_value(str + pos_var(str, old_pos), env->envp, env);
	if (!tmp)
		return (-2);
	len = old_pos;
	len += ft_strlen(tmp);
	free(tmp);
	if (len == -1)
		return (0);
	return (len);
}

static char	**variable_env(char **str, t_env *env)
{
	size_t		i;
	long long	new_pos;
	long long	old_pos;

	i = 0;
	new_pos = 0;
	while (str[i])
	{
		old_pos = new_pos;
		new_pos = ft_new_pos(env, str[i], new_pos);
		str = modified_str(str, env, i, old_pos);
		str = check_str(str);
		if (new_pos == -2 || !str)
		{
			if (str)
				free_split(str, ft_strstrlen(str));
			ft_putstr_fd(MALLOC, 2);
			return (NULL);
		}
		if (new_pos == -1 && str[i])
			i++;
	}
	return (str);
}

char	**pattern_matching(char **str, t_env *env)
{
	size_t	i;
	char	**tmp;

	str = variable_env(str, env);	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		tmp = check_pattern_word(str, i);
		if (!tmp)
		{
			free_split(str, ft_strstrlen(str));
			return (NULL);
		}
		if (str != tmp)
			str = tmp;
		i++;
	}
	return (str);
}
