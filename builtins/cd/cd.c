/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:19:20 by machrist          #+#    #+#             */
/*   Updated: 2024/06/21 14:50:38 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	update_env(t_env *env, char **oldpwd, char **pwd, t_pipex *pipex)
{
	char	*tmp_pwd;
	char	*tmp_oldpwd;

	tmp_oldpwd = ft_strjoin("OLDPWD=", *oldpwd);
	if (!tmp_oldpwd)
	{
		perror("minishell: error malloc");
		return (false);
	}
	env->envp = ft_export_env(env, tmp_oldpwd, pipex);
	free(tmp_oldpwd);
	tmp_pwd = ft_strjoin("PWD=", *pwd);
	if (!tmp_pwd)
	{
		perror("minishell: error malloc");
		return (false);
	}
	env->envp = ft_export_env(env, tmp_pwd, pipex);
	free(tmp_pwd);
	return (true);
}

static bool	init_cd(t_env *env, char **args, char **oldpwd, char **pwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
	{
		perror("minishell: cd");
		env->status = 1;
		return (false);
	}
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		free(*oldpwd);
		env->status = 1;
		return (false);
	}
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
	{
		perror("minishell: cd");
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
