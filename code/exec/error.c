/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:51:11 by machrist          #+#    #+#             */
/*   Updated: 2024/06/28 14:32:50 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	msg(char *err)
{
	ft_printf_fd(2, err);
	return (EXIT_FAILURE);
}

void	msg_error_cmd(char *err, t_cmd cmds)
{
	if (ft_strncmp(err, ERR_CMD, 10) == 0)
	{
		if (!cmds.args)
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else if (!cmds.args[0])
			ft_printf_fd(2, "%s", (char *)ERR_CMD_EMPTY);
		else
			ft_printf_fd(2, err, cmds.args[0]);
	}
	else
	{
		if (!cmds.args)
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else if (!cmds.args[0])
			ft_printf_fd(2, "%s", (char *)ERR_ACCESS_EMPTY);
		else
			ft_printf_fd(2, err, cmds.args[0]);
	}
}

void	msg_error_infile(char *err, t_pipex *pipex, char *infile_name)
{
	(void)pipex;
	if (!infile_name)
		ft_printf_fd(2, err, strerror(errno));
	else
		ft_printf_fd(2, err, infile_name, strerror(errno));
}

void	msg_error_outfile(char *err, t_pipex *pipex, char *outfiles_name)
{
	(void)pipex;
	if (!outfiles_name)
		ft_printf_fd(2, err, strerror(errno));
	else
		ft_printf_fd(2, err, outfiles_name, strerror(errno));
}

void	msg_error(char *err, t_pipex *pipex)
{
	ft_printf_fd(2, err);
	free_split(pipex->env->envp, ft_strstrlen(pipex->env->envp));
	parent_free(pipex);
	exit (EXIT_FAILURE);
}
