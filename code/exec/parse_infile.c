/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:27:05 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/26 19:40:56 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_infiles(t_pipex *pipex, t_cmd *cmds, char **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
			j++;
	if (j)
	{
		cmds->infiles = malloc(sizeof(int) * (j + 1));
		if (!cmds->infiles)
			msg_error(ERR_MALLOC, pipex);
		cmds->infiles_name = malloc(sizeof(char *) * (j + 1));
		if (!cmds->infiles_name)
		{
			free(cmds->infiles);
			msg_error(ERR_MALLOC, pipex);
		}
		cmds->infiles_name[j] = NULL;
	}
}

int	open_infiles(t_pipex *pipex, char *cmd, char *file, char *infile_name)
{
	int		fd;
	char	**tmp;

	if (ft_strncmp(cmd, "<<", 2))
	{
		tmp = malloc(sizeof(char *) * 2);
		if (!tmp)
			ft_free_ex(EXIT_FAILURE, pipex);
		tmp[0] = ft_strdup(file);
		if (!tmp[0])
		{
			free(tmp);
			ft_free_ex(EXIT_FAILURE, pipex);
		}
		tmp[1] = NULL;
		tmp = pattern_matching(tmp, pipex->env);
		quote_removal(tmp);
		fd = open(tmp[0], O_RDONLY);
		free_split(tmp, ft_strstrlen(tmp));
	}
	else
		fd = here_doc(pipex, infile_name);
	return (fd);
}

void	error_infile(t_pipex *pipex, t_cmd *cmds, char *file, int fd)
{
	int	j;

	if (fd == -1)
		cmds->exec = 0;
	if (errno != 0)
		msg_error_infile(ERR_FILE, *pipex, file);
	pipex->env->status = 1;
	j = -1;
	while (cmds->infiles_name[++j])
	{
		cmds->infiles[j] = -1;
		if (cmds->infiles[j] > 0)
			close(cmds->infiles[j]);
		free(cmds->infiles_name[j]);
		cmds->infiles_name[j] = NULL;
	}
	free(cmds->infiles);
	free(cmds->infiles_name);
	cmds->infiles = NULL;
	cmds->infiles_name = NULL;
}

void	get_infiles(t_pipex *pipex, char **cmd, t_cmd *cmds, int i)
{
	int	j;

	j = 0;
	malloc_infiles(pipex, cmds, cmd);
	if (!cmds->infiles)
		return ;
	while (cmd[++i] && !(chre(cmd[i], "&&") || chre(cmd[i], "||")
			|| chre(cmd[i], "|")))
	{
		if (chre(cmd[i], "<") || chre(cmd[i], "<<"))
		{
			cmds->infiles_name[j] = quote_rm_world(cmd[i + 1], NULL);
			cmds->infiles[j] = -1;
			cmds->infiles[j] = open_infiles(pipex, cmd[i], cmd[i + 1],
					cmds->infiles_name[j]);
			if (cmds->infiles[j] < 0)
			{
				error_infile(pipex, cmds, \
					cmds->infiles_name[j], cmds->infiles[j]);
					rl_done = 0;
				break ;
			}
			j++;
		}
		cmds->infiles[j] = -1;
	}
}
