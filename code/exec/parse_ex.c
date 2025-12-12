/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:04:48 by vincent           #+#    #+#             */
/*   Updated: 2024/06/27 19:27:20 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_new_nodes(t_pipex *pipex, t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(t_cmd));
	while (cmds->next)
		cmds = cmds->next;
	list_init(tmp);
	if (!tmp)
		msg_error(ERR_MALLOC, pipex);
	tmp->args = get_args(pipex, &pipex->cmd[pipex->i], cmds);
	tmp->id = cmds->id + 1;
	get_infiles(pipex, &pipex->cmd[pipex->i], tmp, i);
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
	int		i;

	i = -1;
	list_init(cmds);
	pipex->cmd_nmbs = 0;
	cmds->args = get_args(pipex, &pipex->cmd[pipex->i], cmds);
	get_infiles(pipex, &pipex->cmd[pipex->i], cmds, i);
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
		(ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 3) != 0) && \
			(ft_strncmp(pipex->cmd[pipex->i - 1], "||", 3) != 0))
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
