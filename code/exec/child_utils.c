/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:12:10 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/27 19:22:58 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	and_or(t_pipex *pipex)
{
	signal(SIGINT, signal_handler);
	if (pipex->cmd[pipex->i] && !(((pipex->env->status == 0
					&& ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 2) == 0))
			|| (pipex->env->status != 0 && ft_strncmp(pipex->cmd[pipex->i - 1],
					"||", 2) == 0)))
		while (pipex->cmd[pipex->i] && (!(ft_strncmp(pipex->cmd[pipex->i], "&&",
						2) == 0) || !(ft_strncmp(pipex->cmd[pipex->i], "||",
						2) == 0)))
			pipex->i++;
	free_l(pipex->cmds);
	pipex->cmds = NULL;
	free(pipex->pid);
	pipex->pid = NULL;
	return (pipex->i);
}

void	args_patern(t_pipex *pipex, t_cmd *cmds)
{
	cmds->args = pattern_matching(cmds->args, pipex);
	quote_removal(cmds->args);
	if (!cmds->args)
		msg_error(ERR_MALLOC, pipex);
}
