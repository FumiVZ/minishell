/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:04 by vincent           #+#    #+#             */
/*   Updated: 2024/06/24 01:46:29 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <var_global.h>

static void	hook_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		rl_done = 1;
		g_signal = 0;
		printf("\n");
	}
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(tmp, "\n");
	if (!tmp2)
	{
		free(s1);
		free(s2);
		ft_exit_error(NULL, 1);
	}
	free(tmp);
	free(s1);
	free(s2);
	return (tmp2);
}

char	*collect_heredoc_input(char *delimiter)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		ft_exit_error(NULL, 1);
	while (g_signal)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			if (!line)
			{
				ft_printf_fd(2, "minishell: syntax error\n");
				free(tmp);
				return (NULL);
			}
			return (tmp);
		}
		tmp = ft_strjoin_free(tmp, line);
		if (!tmp)
			ft_exit_error(NULL, 1);
	}
	return (tmp);
}

int	here_doc(t_pipex *pipex, char *infile_name)
{
	int		pipefd[2];
	char	*input;

	signal(SIGINT, hook_here_doc);
	g_signal = 1;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_exit_error(pipex->env, 1);
	}
	input = collect_heredoc_input(infile_name);
	if (!input)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-2);
	}
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	free(input);
	return (pipefd[0]);
}
