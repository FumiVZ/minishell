/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:12 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/15 17:32:15 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>
#include <var_global.h>

static void	minishell(t_env *env, char *line)
{
	if (!check_syntax(line))
	{
		env->status = 2;
		return ;
	}
	env->cmds = ft_word_spliting(line, " \t\n\r\f\v");
	if (!(env->cmds))
		return ;
	if (!check_syntax_split(env->cmds))
	{
		env->status = 2;
		return (free_split(env->cmds, ft_strstrlen(env->cmds)));
	}
	if (g_signal)
	{
		if (g_signal == 130)
			env->status = 130;
		g_signal = 0;
	}
	init_pipex(env, env->cmds);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf_fd(2, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	ft_readline(t_env *env)
{
	char	*line;

	while (1)
	{
		rl_done = 0;
		line = readline("minishell$ ");
		if (!line)
			ft_exit_error(env, env->status);
		if (ft_add_history(env, line))
			minishell(env, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env.status = 0;
	ft_init_env(&env, envp);
	init_last_param(&env, ac, av);
	if (!env.envp)
		ft_exit_error(&env, 1);
	ft_readline(&env);
	return (0);
}
