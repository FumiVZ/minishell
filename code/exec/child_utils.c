/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/26 20:25:36 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	and_or(t_pipex *pipex)
{
	ft_err_signal(SIGINT, signal_handler, pipex);
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

/* void	print_tab(char **tab)
{
	int		i;
	char	**new;

	i = -1;
	while (tab[++i])
	{
		ft_printf_fd(2, "tab[%d] = %s\n", i, tab[i]);
		ft_putchar_fd('\n', 1);
	}
} */

/* char	**ft_strjoin_tab(char **tab1, char **tab2, int i, int j)
{
	char	**new;

	new = malloc(sizeof(char *) * \
		(ft_strstrlen(tab1) + ft_strstrlen(tab2) + 1));
	new = malloc(sizeof(char *) * (ft_strstrlen(tab1) + ft_strstrlen(tab2)
				+ 1));
	if (!new)
		return (NULL);
	if (tab1)
	{
		while (tab1[++i])
		{
			new[i] = ft_strdup(tab1[i]);
			if (!new[i])
				return (NULL);
		}
	}
	else
		i = 0;
	while (tab2[++j])
	{
		new[i++] = ft_strdup(tab2[j]);
		if (!new[i - 1])
			return (NULL);
	}
	free_split(tab1, ft_strstrlen(tab1));
	free_split(tab2, ft_strstrlen(tab2));
	new[i] = NULL;
	return (new);
} */

/* char	**remove_spaces(char **args, t_pipex *pipex)
{
	int		i;
	char	**tmp;
	char	**new;

	i = -1;
	new = NULL;
	while (args[++i])
	{
		if (args[i][0] != '\"' && args[i][ft_strlen(args[i]) - 1] != '\"')
		{
			tmp = ft_split(args[i], ' ');
			if (!tmp)
				malloc_failed(pipex);
			new = ft_strjoin_tab(new, tmp, -1, -1);
			if (!new)
				malloc_failed(pipex);
		}
	}
	free_split(args, ft_strstrlen(args));
	return (new);
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
} */

void	args_patern(t_pipex *pipex, t_cmd *cmds)
{
	cmds->args = pattern_matching(cmds->args, pipex->env);
	quote_removal(cmds->args);
	/* 	cmds->args = remove_spaces(cmds->args, pipex); */
	/* 	cmds->args = remove_spaces(cmds->args, pipex); */
	if (!cmds->args)
		msg_error(ERR_MALLOC, pipex);
}
