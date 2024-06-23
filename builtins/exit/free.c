/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:47:09 by machrist          #+#    #+#             */
/*   Updated: 2024/06/23 17:05:14 by vzuccare         ###   ########lyon.fr   */
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
