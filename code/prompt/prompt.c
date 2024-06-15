/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:08:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/14 17:40:38 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>
#include <var_global.h>

static void	minishell(t_env *env, char *line)
{
	if (!check_syntax(line))
	{
		env->status = 1;
		return ;
	}
	env->cmds = ft_word_spliting(line, " \t");
	if (!(env->cmds))
		return ;
	if (!check_syntax_split(env->cmds))
	{
		env->status = 1;
		free_split(env->cmds, ft_strstrlen(env->cmds));
		return ;
	}
	init_pipex(env);
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_here_doc == 1 && sig == SIGINT)
		g_here_doc = 0;
	else if (info->si_pid != 0 && sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (info->si_pid == 0 && sig == SIGINT)
		write(1, "\n", 1);
	if (info->si_pid == 0 && sig == SIGQUIT)
		write(1, "Quit\n", 6);
	else if ((info->si_pid != 0 || g_here_doc == 1) && sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

void	ft_readline(t_env *env)
{
	char	*line;

	while (1)
	{
		rl_done = 0;
		g_here_doc = 2;
		line = readline("minishell$ ");
		if (!line)
			ft_exit_error(env, 0);
		add_history(line);
		minishell(env, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env				env;
	struct sigaction	sa;
	char				**tmp;
	size_t				i;

	rl_event_hook = readline_event_hook;
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1 ||
		sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		printf("Error: signal\n");
		return (1);
	}
	env.status = 0;
	ft_init_env(&env, envp);
	init_last_param(&env, ac, av);
	if (!env.envp)
		ft_exit_error(&env, 1);
	// tester minishell -c  https://minishell-test.readthedocs.io/en/latest/
	if (ac == 3 && !ft_strncmp(av[1], "-c", 3))
	{
		tmp = ft_split(av[2], ';');
		if (!tmp)
			ft_exit_error(&env, 1);
		i = 0;
		if (tmp[ft_strstrlen(tmp) - 1][ft_strlen(tmp[ft_strstrlen(tmp) - 1])
			- 1] == '\n')
			tmp[ft_strstrlen(tmp) - 1][ft_strlen(tmp[ft_strstrlen(tmp) - 1])
				- 1] = '\0';
		while (tmp[i])
		{
			minishell(&env, tmp[i]);
			i++;
		}
		free_split(tmp, ft_strstrlen(tmp));
		return (env.status);
	}
	ft_readline(&env);
	return (0);
}
