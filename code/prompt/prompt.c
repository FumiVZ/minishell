/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:08:51 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/24 16:25:35 by machrist         ###   ########.fr       */
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
	init_pipex(env, env->cmds);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT && g_signal == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
	g_signal = 0;
}

void	ft_readline(t_env *env)
{
	char	*line;

	while (1)
	{
		rl_done = 0;
		line = readline("minishell$ ");
		if (!line)
			ft_exit_error(env, 0);
		ft_add_history(line);
		minishell(env, line);
	}
}

int	manage_c(char **av, t_env env)
{
	char	**tmp;
	size_t	i;

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

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	env.status = 0;
	ft_init_env(&env, envp);
	init_last_param(&env, ac, av);
	if (!env.envp)
		ft_exit_error(&env, 1);
	if (ac == 3 && !ft_strncmp(av[1], "-c", 3))
		return (manage_c(av, env));
	else
		ft_readline(&env);
	return (0);
}
