/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:12:07 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/23 18:20:07 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**count_arguments(char **cmd, t_pipex *pipex)
{
	int		i;
	int		j;
	char	**args;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&")
			|| chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") || chre(cmd[i], "<<")
				|| chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			j++;
		if (!cmd[i] || (chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			break ;
	}
	args = malloc(sizeof(char *) * (j + 1));
	if (!args)
		msg_error(ERR_MALLOC, pipex);
	return (args);
}

char	**malloc_args(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	char	**args;
	char	**tmp;

	tmp = delete_parentheses(cmd, pipex);
	if (!tmp)
		tmp = cmd;
	else
		cmds->is_parentheses = 1;
	args = count_arguments(tmp, pipex);
	if (tmp != cmd)
		free_split(tmp, ft_strstrlen(tmp));
	return (args);
}

char	**extract_arguments(char **cmd, char **args)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&")
			|| chre(cmd[i], "|")))
	{
		while (cmd[i] && (chre(cmd[i], "<") || chre(cmd[i], "<<")
				|| chre(cmd[i], ">>") || chre(cmd[i], ">")))
			i += 2;
		if (cmd[i] && !(chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			args[j++] = ft_strdup(cmd[i]);
		if (!cmd[i] || (chre(cmd[i], "||") || chre(cmd[i], "&&") || chre(cmd[i],
					"|")))
			break ;
	}
	args[j] = NULL;
	return (args);
}

char	**get_args(t_pipex *pipex, char **cmd, t_cmd *cmds)
{
	char	**args;
	char	**tmp;

	if (!pipex->cmd)
		return (NULL);
	args = malloc_args(pipex, cmd, cmds);
	tmp = delete_parentheses(cmd, pipex);
	if (!tmp)
		tmp = cmd;
	args = extract_arguments(tmp, args);
	if (args)
		pipex->cmd_nmbs++;
	if (tmp != cmd)
		free_split(tmp, ft_strstrlen(tmp));
	return (args);
}
