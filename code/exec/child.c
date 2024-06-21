/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:53:07 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/20 18:04:36 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	single_command(t_pipex *pipex, t_cmd *cmds, char **env)
{
	int status;

	if (cmds->args[0] == NULL)
		return ;
	env = set_last_param(pipex->env, \
		cmds->args[ft_strstrlen(cmds->args) - 1]);
	if (!pipex->env->envp)
	{
		parent_free(pipex);
		exit (1);
	}
	if (cmds->exec == 1 && !is_builtin(cmds->args) && (cmds->pid_par == 0 || cmds->is_parentheses == 0))
	{
		pipex->pid[0] = fork();
		if (pipex->pid[0] == -1)
			msg_error(ERR_FORK, pipex);
		if (pipex->pid[0] == 0)
			child_exec(pipex, cmds, env);
		if (cmds->is_parentheses)
		{
			status = pipex->env->status;
			free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
			child_free(pipex, env);
			exit (status);
		}
	}
	else if (cmds->exec == 1 && (cmds->pid_par == 0 || cmds->is_parentheses == 0))
	{
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
	else
		return ;
	wait_execve(pipex, pipex->cmds);
	close_files(pipex, pipex->cmds);
}

void	execute_command(t_pipex *pipex, t_cmd *cmds, char **env, int i)
{
	int	status;

 	env = set_last_param(pipex->env, cmds->args[ft_strstrlen(cmds->args) - 1]);
	if (!pipex->env->envp)
	{
		parent_free(pipex);
		exit (1);
	}
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		msg_error(ERR_FORK, pipex);
	if (pipex->pid[i] == 0 && !is_builtin(cmds->args))
	{
		pipe_handle(pipex, cmds);
		child_exec(pipex, cmds, env);
	}
	else if (pipex->pid[i] == 0)
	{
		pipe_handle(pipex, cmds);
		redirect(pipex, cmds);
		ft_builtins(pipex->env, pipex, cmds->args);
		status = pipex->env->status;
		free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
		child_free(pipex, env);
		exit (status);
	}
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
		{
			cmds->pid_par = fork();
		}
		if (cmds->pid_par == -1)
			msg_error(ERR_FORK, pipex);
		if (cmds->pid_par == 0 || cmds->is_parentheses == 0)
		{
			cmds->args = pattern_matching(cmds->args, pipex->env);
			quote_removal(cmds->args);
			if (!cmds->args)
				msg_error(ERR_MALLOC, pipex);
			if (cmds->exec == 1)
				execute_command(pipex, cmds, env, i);
			else
				pipex->pid[i] = -1;
		}
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

int	child_crt(t_pipex *pipex, char **env)
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
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
		{
			cmds->args = pattern_matching(cmds->args, pipex->env);
			quote_removal(cmds->args);
			if (!cmds->args)
				msg_error(ERR_MALLOC, pipex);
			single_command(pipex, cmds, env);
		}
		if (cmds->pid_par != 0 && cmds->is_parentheses == 1)
		{
			waitpid(cmds->pid_par, &pipex->env->status, 0);
			if (WIFEXITED(pipex->env->status))
				pipex->env->status = pipex->env->status % 255;
		}
	}
	if (pipex->cmd[pipex->i] && !(((pipex->env->status == 0
					&& ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 2) == 0))
			|| (pipex->env->status != 0 && ft_strncmp(pipex->cmd[pipex->i - 1],
					"||", 2) == 0)))
		while (pipex->cmd[pipex->i] && \
			(!(ft_strncmp(pipex->cmd[pipex->i], "&&", 2) == 0)
				|| !(ft_strncmp(pipex->cmd[pipex->i], "||", 2) == 0)))
			pipex->i++;
	free_l(pipex->cmds);
	pipex->cmds = NULL;
	free(pipex->pid);
	pipex->pid = NULL;
	return (pipex->i);
}
