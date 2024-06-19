/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:04:48 by vincent           #+#    #+#             */
/*   Updated: 2024/06/18 18:09:34 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// function to compare two string char by char and by lenght

char	**malloc_args(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int		i;
	int		j;
	char	**tmp;
	char	**args;

	i = -1;
	j = 0;
	tmp = delete_parentheses(cmd, pipex);
	if (!tmp)
		tmp = cmd;
	else
		cmds->is_parentheses = 1;
	while (tmp[++i] && !(chre(tmp[i], "||") || chre(tmp[i], "&&")
			|| chre(tmp[i], "|")))
	{
		while (tmp[i] && (chre(tmp[i], "<") || chre(tmp[i], "<<")
				|| chre(tmp[i], ">>") || chre(tmp[i], ">")))
			i += 2;
		if (tmp[i] && !(chre(tmp[i], "||") || chre(tmp[i], "&&") || chre(tmp[i],
					"|")))
			j++;
		if (!tmp[i] || (chre(tmp[i], "||") || chre(tmp[i], "&&") || chre(tmp[i],
					"|")))
			break ;
	}
	if (tmp != cmd)
		free_split(tmp, ft_strstrlen(tmp));
	args = malloc(sizeof(char *) * (j + 1));
	if (!args)
		msg_error(ERR_MALLOC, pipex);
	return (args);
}

char	**get_args(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	int		i;
	int		j;
	char	**args;
	char	**tmp;

	if (!pipex->cmd)
		return (NULL);
	args = malloc_args(pipex, cmd, cmds);
	tmp = delete_parentheses(cmd, pipex);
	if (!tmp)
		tmp = cmd;
	i = -1;
	j = 0;
	while (tmp[++i] && !(chre(tmp[i], "||") || chre(tmp[i], "&&")
			|| chre(cmd[i], "|")))
	{
		while (tmp[i] && (chre(tmp[i], "<") || chre(tmp[i], "<<")
				|| chre(tmp[i], ">>") || chre(tmp[i], ">")))
			i += 2;
		if (tmp[i] && !(chre(tmp[i], "||") || chre(tmp[i], "&&") || chre(tmp[i],
					"|")))
			args[j++] = ft_strdup(tmp[i]);
		if (!tmp[i] || (chre(tmp[i], "||") || chre(tmp[i], "&&") || chre(tmp[i],
					"|")))
			break ;
	}
	args[j] = NULL;
	if (args)
		pipex->cmd_nmbs++;
	if (tmp != cmd)
		free_split(tmp, ft_strstrlen(tmp));
	return (args);
}

void	create_new_nodes(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds->next)
		cmds = cmds->next;
	tmp = malloc(sizeof(t_cmd));
	list_init(tmp);
	if (!tmp)
		msg_error(ERR_MALLOC, pipex);
	tmp->args = get_args(pipex, &pipex->cmd[pipex->i], cmds);
	tmp->id = cmds->id + 1;
	get_infiles(pipex, &pipex->cmd[pipex->i], tmp);
	if (pipex->env->status == 0)
		get_outfiles(pipex, &pipex->cmd[pipex->i], tmp);
	tmp->next = NULL;
	cmds->next = tmp;
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&")
			|| chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i],
			"|"))
		pipex->i++;
	if (pipex->cmd[pipex->i] && chre(pipex->cmd[pipex->i], "|"))
		pipex->i++;
}

void	first_node(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	list_init(cmds);
	pipex->cmd_nmbs = 0;
	cmds->args = get_args(pipex, &pipex->cmd[pipex->i], cmds);
	get_infiles(pipex, &pipex->cmd[pipex->i], cmds);
	get_outfiles(pipex, &pipex->cmd[pipex->i], cmds);
	while (pipex->cmd[pipex->i] && !(chre(pipex->cmd[pipex->i], "&&")
			|| chre(pipex->cmd[pipex->i], "||")) && !chre(pipex->cmd[pipex->i],
			"|"))
		pipex->i++;
	if (!pipex->cmd[pipex->i] || (chre(pipex->cmd[pipex->i], "||")
			|| chre(pipex->cmd[pipex->i], "&&")))
	{
		tmp = cmds;
		while (cmds->next)
			cmds = cmds->next;
		pipex->nb_pipes = 2 * (pipex->cmd_nmbs - 1);
		cmds = tmp;
		return ;
	}
}

void	parse_cmd(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;

	if (!cmds)
		msg_error(ERR_MALLOC, pipex);
	first_node(pipex, cmds);
	if (pipex->cmd[pipex->i])
		pipex->i++;
	while (pipex->cmd[pipex->i] && \
		(ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 2) != 0) && \
			(ft_strncmp(pipex->cmd[pipex->i - 1], "||", 2) != 0))
		create_new_nodes(pipex, cmds);
	tmp = cmds;
	while (cmds->next)
		cmds = cmds->next;
	pipex->nb_pipes = 2 * (pipex->cmd_nmbs - 1);
	cmds->next = NULL;
	cmds = tmp;
	pipex->pid = malloc(sizeof(pid_t) * (pipex->cmd_nmbs));
	if (!pipex->pid)
		msg_error(ERR_MALLOC, pipex);
}
