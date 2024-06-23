/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:35:00 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/23 20:11:01 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	and_or(t_pipex *pipex)
{
	if (pipex->cmd[pipex->i] && !(((pipex->env->status == 0 \
		&& ft_strncmp(pipex->cmd[pipex->i - 1], "&&", 2) == 0)) \
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

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		ft_printf_fd(2, "tab[%d] = %s\n", i, tab[i]);
		ft_putchar_fd('\n', 1);
	}
}

void	args_patern(t_pipex *pipex, t_cmd *cmds)
{
	cmds->args = pattern_matching(cmds->args, pipex->env);
	quote_removal(cmds->args);
	if (!cmds->args)
		msg_error(ERR_MALLOC, pipex);
}
