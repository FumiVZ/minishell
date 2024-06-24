/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:53:07 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/24 18:41:45 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal = 0;

void	exec_builtins(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int	status;

	redirect(pipex, cmds);
	ft_builtins(pipex->env, pipex, cmds->args);
	if (pipex->old0 != -1 && pipex->old1 != -1)
	{
		secure_dup2(pipex->old0, STDIN_FILENO, pipex);
		secure_dup2(pipex->old1, STDOUT_FILENO, pipex);
	}
	close_files(pipex, pipex->cmds);
	pipex->pid[0] = -1;
	if (cmds->is_parentheses)
	{
		status = pipex->env->status;
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit (status);
	}
	return ;
}

void	exec_single(t_pipex *pipex, t_cmd *cmds, char **env)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
		msg_error(ERR_FORK, pipex);
	if (pipex->pid[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_exec(pipex, cmds, env);
	}
	if (cmds->is_parentheses)
		ft_free_ex(pipex->env->status, pipex);
}

void	single_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	args_patern(pipex, cmds);
	if (cmds->args[0] == NULL)
		return ;
	env = set_last_param(pipex->env, \
		cmds->args[ft_strstrlen(cmds->args) - 1]);
	if (!env)
	{
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		parent_free(pipex);
		exit (1);
	}
	if (cmds->exec == 1 && !is_builtin(cmds->args) && \
		(cmds->pid_par == 0 || cmds->is_parentheses == 0))
		exec_single(pipex, cmds, env);
	else if (cmds->exec == 1 && (cmds->pid_par == 0 \
		|| cmds->is_parentheses == 0))
	{
		exec_builtins(pipex, cmds, env);
		close_files(pipex, pipex->cmds);
		return ;
	}
	else
		return (close_files(pipex, pipex->cmds));
	wait_execve(pipex, pipex->cmds);
	close_files(pipex, pipex->cmds);
}

int	child_crt(t_pipex *pipex, char **env)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		malloc_failed(pipex);
	pipex->cmds = cmds;
	parse_cmd(pipex, cmds);
	if (cmds->next)
		multiple_command(pipex, cmds, env);
	else
	{
		if (cmds->is_parentheses == 1)
			cmds->pid_par = fork();
		if (cmds->pid_par == -1)
			msg_error(ERR_FORK, pipex);
		if (cmds->pid_par == 0 || cmds->is_parentheses == 0)
			single_command(pipex, cmds, env);
		if (cmds->pid_par != 0 && cmds->is_parentheses == 1)
		{
			waitpid(cmds->pid_par, &pipex->env->status, 0);
			if (WIFEXITED(pipex->env->status))
				pipex->env->status = pipex->env->status % 255;
		}
	}
	return (and_or(pipex));
}
