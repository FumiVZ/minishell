/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/06/28 18:04:57 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_child(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
	free_split(env->cmds, ft_strstrlen(env->cmds));
	free_split(env->clean_cmds, ft_strstrlen(env->clean_cmds));
}

void	ft_free_parent(t_env *env)
{
	free_split(env->envp, ft_strstrlen(env->envp));
}

void	ft_free_ex(int status, t_pipex *pipex)
{
	int	status2;

	status2 = status;
	free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
	child_free(pipex, pipex->env->envp);
	exit (status2);
}

void	ft_free_ex_msg(int status, t_pipex *pipex, t_cmd *cmds)
{
	int	status2;

	status2 = status;
	if (errno == EACCES && !ft_strfind(*cmds->args, '/'))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", *cmds->args);
		status2 = 127;
	}
	else if (errno == EACCES || errno == EPERM)
		ft_printf_fd(2, "minishell: %s: Permission denied\n", *cmds->args);
	else if (errno == ENOENT)
		ft_printf_fd(2, "minishell: %s: \
			No such file or directory\n", *cmds->args);
	else if (errno == EISDIR)
		ft_printf_fd(2, "minishell: %s: Is a directory\n", *cmds->args);
	else
		ft_printf_fd(2, "minishell: %s: %s\n", *cmds->args, strerror(errno));
	free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
	child_free(pipex, pipex->env->envp);
	exit (status2);
}