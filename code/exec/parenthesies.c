/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:20:39 by vincent           #+#    #+#             */
/*   Updated: 2024/06/15 02:40:05 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* //check if there is any parentheses in the command and delete them
static void	delete_parentheses(t_pipex *pipex)
{
	int	i;
	int	j;
	int	start[2];

	start[0] = -1;
	start[1] = -1;
	i = -1;
	while (pipex->cmd[++i] != NULL)
	{
		j = -1;
		while (pipex->cmd[i][++j] != '\0')
		{
			if (pipex->cmd[i][j] == '(')
			{
				start[0] = i;
				start[1] = j;
			}
		}
	}
}

static	int count_len(char **cmd, int start[2], int end[2])
{
	int	i;
	int	len;

	i = start[0];
	len = 0;
	while (i < end[0])
	{
		if (i == start[0])
			len += ft_strlen(cmd[i]) - start[1];
		else if (i == end[0])
			len += end[1];
		else
			len += ft_strlen(cmd[i]);
		i++;
	}
	return (len);
}
{

}
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (cmd[++i] != NULL)
		len++;
	return (len);
}
 */

static char **save_parentheses(t_pipex *pipex, int start, int end)
{
	char	**new_cmd;
	int		i;
	int		j;

	new_cmd = malloc(sizeof(char *) * (end - start + 1));
	if (!new_cmd)
		msg_error(ERR_MALLOC, pipex);
	i = start;
	j = 0;
	while (i < end)
	{
		if (i == start)
			new_cmd[j] = ft_strdup(pipex->cmd[i] + 1);
		else if (i == end - 1)
			new_cmd[j] = \
				ft_substr(pipex->cmd[i], 0, ft_strlen(pipex->cmd[i]) - 1);
		else
			new_cmd[j] = ft_strdup(pipex->cmd[i]);
		i++;
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

static char	**delete_parentheses(t_pipex *pipex)
{
	char	**new_cmd;
	char	**tmp;
	int		i;
	int		start;
	int		end;
	int		len;

	i = 0;
	end = 0;
	tmp = NULL;
	new_cmd = NULL;
	while (pipex->cmd[i])
	{
		if (pipex->cmd[i][0] == '(')
		{
			start = i;
			while (pipex->cmd[i] && \
				pipex->cmd[i][ft_strlen(pipex->cmd[i]) - 1] != ')')
				i++;
			if (!pipex->cmd[i])
				return (NULL);
			end = i + 1;
			new_cmd = save_parentheses(pipex, start, end);
			if ((ft_strstrlen(pipex->cmd) - (end - start)) == 0)
				break;
			tmp = malloc(sizeof(char *) * \
				(ft_strstrlen(pipex->cmd) - (end - start) + 1));
			if (!tmp)
				msg_error(ERR_MALLOC, pipex);
			i = 0;
			while (i < start)
			{
				if (tmp)
					tmp[i] = ft_strdup(pipex->cmd[i]);
				i++;
			}
			len = 0;
			while (pipex->cmd[end + len])
			{
				tmp[start + len] = ft_strdup(pipex->cmd[end + len]);
				len++;
			}
			tmp[start + len] = NULL; 
			free_split(pipex->cmd, ft_strstrlen(pipex->cmd));
			pipex->cmd = tmp;
		}
		if (pipex->cmd[i])
			i++;
	}
	if (new_cmd)
	{
		free_split(pipex->cmd, ft_strstrlen(pipex->cmd));
		pipex->cmd = tmp;
	}
	return (new_cmd);
}


//WORK IN PROGRESS
void parentheses(t_pipex *pipex, t_cmd *cmd)
{
	(void) cmd;
	char 	**sav_cmd;
	pid_t	pid;
	int		status;
	t_env	*env;

	(void) pid;
	(void) status;
	if (pipex)
		return ;
	env = pipex->env;
	sav_cmd = delete_parentheses(pipex);
	if (sav_cmd)
	{
		printf("Parentheses found\n");
		print_tab(sav_cmd);
	}
	ft_printf_fd(2, "No parentheses found\n");
	if (sav_cmd)
	{
		ft_printf_fd(2, "CHILD\n");
		pid = fork();
		if (pid == -1)
			msg_error(ERR_FORK, pipex);
		if (pid == 0)
		{
/* 			child_free(pipex, pipex->env->envp); */
			init_pipex(env, sav_cmd);
		}
		waitpid(pid, &status, 0);
	}
}