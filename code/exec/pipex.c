/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/24 19:41:36 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>
#include <var_global.h>

void	close_pipes(t_pipex *pipex, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (!cmd->pipe)
		return ;
	while (i < 2 * (pipex->cmd_nmbs - 1))
	{
		if (cmd->pipe[i] != -1)
			close(cmd->pipe[i++]);
	}
}

int	wait_parentheses(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;
	int		status;

	tmp = cmds;
	status = 0;
	while (tmp)
	{
		if (tmp->is_parentheses)
		{
			waitpid(tmp->pid_par, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				printf("\n");
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				printf("\nQuit: 3\n");
			if (tmp->next == NULL)
			{
				if (WIFEXITED(status))
					pipex->env->status = WEXITSTATUS(status);
				if (WIFSIGNALED(status))
					pipex->env->status = 128 + WTERMSIG(status);
			}
		}
		tmp = tmp->next;
	}
	return (status);
}

void	wait_execve(t_pipex *pipex, t_cmd *cmds)
{
	int		status;
	int		i;

	i = -1;
	status = 0;
	while (++i < pipex->cmd_nmbs)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			printf("\n");
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit\n");
		if (i == pipex->cmd_nmbs - 1)
		{
			if (WIFEXITED(status))
				pipex->env->status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				pipex->env->status = 128 + WTERMSIG(status);
		}
	}
	status = wait_parentheses(pipex, cmds);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

char	*find_path(char **env)
{
	if (!env)
		return (NULL);
	while (ft_strncmp("PATH", *env, 4))
		env++;
	if (!*env)
		return (NULL);
	return (*env + 5);
}

void	init_pipex(t_env *env, char **cmds)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		free_split(cmds, ft_strstrlen(cmds));
		free_split(env->envp, ft_strstrlen(env->envp));
		exit (EXIT_FAILURE);
	}
	*pipex = (t_pipex){0};
	pipex->env = env;
	pipex->cmd = cmds;
	pipex->paths = ft_split(find_path(env->envp), ':');
	pipex->old0 = -1;
	pipex->old1 = -1;
	if (!pipex->paths)
		pipex->paths = ft_split("/usr/local/bin:\
			/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.", ':');
	if (!pipex->paths)
		malloc_failed(pipex);
	while (pipex->cmd[pipex->i])
		pipex->i = child_crt(pipex, env->envp);
	parent_free(pipex);
}
