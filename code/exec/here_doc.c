/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:09:04 by vincent           #+#    #+#             */
/*   Updated: 2024/07/15 17:12:23 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <var_global.h>

void	hook_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

int	readline_event_hook(void)
{
	if (g_signal == 130 || g_signal == 0)
	{
		rl_done = 1;
	}
	return (0);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	tmp2 = ft_strjoin(tmp, "\n");
	if (!tmp2)
		return (NULL);
	free(tmp);
	return (tmp2);
}

char	*collect_heredoc_input(char *delimiter, t_pipex *pipex)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		malloc_failed(pipex);
	while (g_signal == 1)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) \
		&& ft_strlen(line) == ft_strlen(delimiter)))
		{
			if (!line)
			{
				ft_printf_fd(2, "minishell: warning: here-document delimited");
				ft_printf_fd(2, " by end-of-file (wanted `%s')\n", delimiter);
				return (free(tmp), NULL);
			}
			return (free(line), tmp);
		}
		tmp = ft_strjoin_free(tmp, line);
		if (!tmp)
			ft_free_ex(EXIT_FAILURE, pipex);
	}
	return (tmp);
}

int	here_doc(t_pipex *pipex, char *infile_name)
{
	int		pipefd[2];
	char	*input;

	g_signal = 1;
	signal(SIGINT, hook_here_doc);
	rl_event_hook = readline_event_hook;
	input = collect_heredoc_input(infile_name, pipex);
	signal(SIGINT, signal_handler);
	rl_event_hook = NULL;
	if (!input)
	{
		g_signal = 0;
		rl_done = 0;
		return (-2);
	}
	if (pipe(pipefd) == -1)
		ft_exit_error(pipex->env, 1);
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	free(input);
	if (g_signal == 130)
		return (close(pipefd[0]), -1);
	return (pipefd[0]);
}
