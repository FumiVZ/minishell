/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:33:41 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/24 19:16:19 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_command(t_pipex *pipex, t_cmd *cmds, char **env, int i)
{
	env = set_last_param(pipex->env, cmds->args[ft_strstrlen(cmds->args) - 1]);
	if (!env)
	{
		parent_free(pipex);
		exit (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		msg_error(ERR_FORK, pipex);
	if (pipex->pid[i] == 0 && !is_builtin(cmds->args))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe_handle(pipex, cmds);
		child_exec(pipex, cmds, env);
	}
	else if (pipex->pid[i] == 0)
	{
		pipe_handle(pipex, cmds);
		redirect(pipex, cmds);
		ft_builtins(pipex->env, pipex, cmds->args);
		ft_free_ex(pipex->env->status, pipex);
	}
}

void	exec_multiple(t_pipex *pipex, t_cmd *cmds, char **env, int i)
{
	args_patern(pipex, cmds);
	if (cmds->exec == 1)
		execute_command(pipex, cmds, env, i);
	else
		pipex->pid[i] = -1;
}

void	multiple_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	crt_pipes(pipex, cmds);
	while (cmds)
	{
		if (cmds->is_parentheses == 1)
			cmds->pid_par = fork();
		if (cmds->pid_par == -1)
			msg_error(ERR_FORK, pipex);
		if (cmds->pid_par == 0 || cmds->is_parentheses == 0)
			exec_multiple(pipex, cmds, env, i);
		i++;
		tmp = cmds;
		cmds = cmds->next;
	}
	close_files(pipex, pipex->cmds);
	close_pipes(pipex, pipex->cmds);
	wait_execve(pipex, pipex->cmds);
	if (tmp->exec == 0)
		pipex->env->status = 1;
}
