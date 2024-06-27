/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:06:32 by machrist          #+#    #+#             */
/*   Updated: 2024/06/27 19:44:10 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char **envp, char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len))
		{
			if (envp[i][len] != '=')
				return (NULL);
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

static void	alloc_env(char **new, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			free_split(new, i);
			ft_putendl_fd("minishell: malloc failed", 2);
			exit(1);
		}
		i++;
	}
	new[i] = NULL;
}

void	ft_init_env(t_env *env, char **envp)
{
	char	**new;

	new = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	if (!new)
	{
		ft_putendl_fd("minishell: malloc failed", 2);
		exit(1);
	}
	alloc_env(new, envp);
	env->envp = new;
	set_default_env(env);
}

void	update_or_add_env_var(t_env *env, char **new, char *var)
{
	size_t	i;
	size_t	j;
	bool	check;

	check = false;
	i = 0;
	j = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, ft_strlen_c(var, '=')))
		{
			free(env->envp[i++]);
			new[j++] = var;
			check = true;
		}
		else
			new[j++] = env->envp[i++];
	}
	if (!check)
		new[j++] = var;
	new[j] = NULL;
}

void	add_value_to_env(t_env *env, char *var)
{
	char	**new;

	if (!var)
		ft_exit_malloc(env);
	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 2));
	if (!new)
	{
		free(var);
		ft_exit_malloc(env);
	}
	update_or_add_env_var(env, new, var);
	free(env->envp);
	env->envp = new;
}
