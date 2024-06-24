/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:09:07 by machrist          #+#    #+#             */
/*   Updated: 2024/06/24 18:22:02 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error_env(t_pipex *pipex, t_env *env, char **new, size_t i)
{
	free_split(new, i);
	parent_free(pipex);
	ft_putstr_fd("minishell: cd: failed\n", 2);
	free(env->oldpwd);
	free(env->pwd);
	ft_exit_error(env, 1);
}

static char	**new_envp(t_env *env, char *var, t_pipex *pipex)
{
	char	**new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 2)); // valide
	if (!new)
	{
		free(var);
		error_env(pipex, env, new, i);
	}
	while (env->envp[i])
	{
		new[i] = env->envp[i];
		i++;
	}
	new[i] = var;
	new[i + 1] = NULL;
	free(env->envp);
	return (new);
}

static char	**ft_export_env(t_env *env, char *var, t_pipex *pipex)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	if (!var[len])
		return (env->envp);
	i = 0;
	while (env->envp[i])
	{
		if (!ft_strncmp(env->envp[i], var, len))
		{
			free(env->envp[i]);
			env->envp[i] = var;
			return (env->envp);
		}
		i++;
	}
	return (new_envp(env, var, pipex));
}

bool	update_env(t_env *env, char **oldpwd, char **pwd, t_pipex *pipex)
{
	char	*tmp_pwd;
	char	*tmp_oldpwd;

	env->oldpwd = *oldpwd;
	env->pwd = *pwd;
	tmp_oldpwd = ft_strjoin("OLDPWD=", *oldpwd); // valide
	if (!tmp_oldpwd)
	{
		perror("minishell: error malloc");
		return (false);
	}
	env->envp = ft_export_env(env, tmp_oldpwd, pipex);
	tmp_pwd = ft_strjoin("PWD=", *pwd); // valide
	if (!tmp_pwd)
	{
		perror("minishell: error malloc");
		return (false);
	}
	env->envp = ft_export_env(env, tmp_pwd, pipex);
	return (true);
}
