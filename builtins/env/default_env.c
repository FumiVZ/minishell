/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:30:50 by machrist          #+#    #+#             */
/*   Updated: 2024/06/27 18:50:27 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_envp(char **envp)
{
	ft_putendl_fd("minishell: malloc failed\n", 2);
	free_split(envp, ft_strstrlen(envp));
	envp = NULL;
}

void	init_pwd(t_env *env)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit_malloc(env);
	tmp = malloc(ft_strlen("PWD=") + ft_strlen(pwd) + 1);
	if (!tmp)
	{
		free(pwd);
		ft_exit_malloc(env);
	}
	ft_strlcpy(tmp, "PWD=", ft_strlen("PWD=") + 1);
	ft_strlcat(tmp, pwd, ft_strlen("PWD=") + ft_strlen(pwd) + 1);
	free(pwd);
	add_value_to_env(env, tmp);
}

void	init_shlvl(t_env *env)
{
	char	*shlvl;
	char	*tmp;
	long	lvl;

	shlvl = ft_getenv(env->envp, "SHLVL");
	if (!shlvl || !ft_is_int(shlvl) || !ft_check_num(shlvl))
	{
		tmp = ft_strdup("SHLVL=1");
		if (!tmp)
			ft_exit_malloc(env);
		add_value_to_env(env, tmp);
		return ;
	}
	lvl = check_shlvl(shlvl);
	tmp = ft_itoa(lvl);
	if (!tmp)
		ft_exit_malloc(env);
	shlvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	if (!shlvl)
		ft_exit_malloc(env);
	add_value_to_env(env, shlvl);
}

void	init_last_param(t_env *env, int ac, char **av)
{
	char	*last_param;
	char	*tmp;

	last_param = ft_getenv(env->envp, "_");
	if (!last_param)
	{
		if (av[ac - 1] && ft_strncmp(av[ac - 1], "$_", 2))
			tmp = ft_strjoin("_=", "/usr/bin/bash");
		else
			tmp = ft_strjoin("_=", av[ac - 1]);
		if (!tmp)
			ft_exit_malloc(env);
		add_value_to_env(env, tmp);
		return ;
	}
	tmp = ft_strjoin("_=", last_param);
	if (!tmp)
		ft_exit_malloc(env);
	add_value_to_env(env, tmp);
}

char	**set_last_param(t_env *env, char *last_param)
{
	char	*tmp;

	if (!last_param)
		return (env->envp);
	tmp = ft_strjoin("_=", last_param);
	if (!tmp)
	{
		free_envp(env->envp);
		return (NULL);
	}
	add_value_to_env(env, tmp);
	return (env->envp);
}
