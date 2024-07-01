/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:19:20 by machrist          #+#    #+#             */
/*   Updated: 2024/06/28 15:05:59 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	init_cd(t_env *env, char **args, char **oldpwd, char **pwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
	{
		ft_putendl_fd("minishell: error getcwd", 2);
		env->status = 1;
		return (false);
	}
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": Not a directory", 2);
		free(*oldpwd);
		env->status = 1;
		return (false);
	}
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
	{
		ft_putendl_fd("minishell: error getcwd", 2);
		free(*oldpwd);
		env->status = 1;
		return (false);
	}
	return (true);
}

static void	cd_oldpwd(t_env *env, char **args, t_pipex *pipex)
{
	char	*tmp;
	char	**new;

	tmp = ft_getenv(env->envp, "OLDPWD");
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		env->status = 1;
		return ;
	}
	new = malloc(sizeof(char *) * 3);
	if (!new)
	{
		msg_perror(env, ERR_MALLOC);
		return ;
	}
	new[0] = args[0];
	new[1] = tmp;
	new[2] = NULL;
	ft_cd(env, new, pipex);
	free(new);
}

static void	cd_no_args(t_env *env, char **args, t_pipex *pipex)
{
	char	*tmp;
	char	**new;

	tmp = ft_getenv(env->envp, "HOME");
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		env->status = 1;
		return ;
	}
	new = malloc(sizeof(char *) * 3);
	if (!new)
	{
		msg_perror(env, ERR_MALLOC);
		return ;
	}
	new[0] = args[0];
	new[1] = tmp;
	new[2] = NULL;
	ft_cd(env, new, pipex);
	free(new);
}

void	ft_cd(t_env *env, char **args, t_pipex *pipex)
{
	char	*oldpwd;
	char	*pwd;

	if (!args[1])
		return (cd_no_args(env, args, pipex));
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		env->status = 1;
		return ;
	}
	if (!ft_strncmp(args[1], "-", 2))
		return (cd_oldpwd(env, args, pipex));
	if (!init_cd(env, args, &oldpwd, &pwd))
		return ;
	if (!update_env(env, &oldpwd, &pwd, pipex))
	{
		free(oldpwd);
		free(pwd);
		env->status = 1;
		return ;
	}
	free(oldpwd);
	free(pwd);
	env->status = 0;
}
