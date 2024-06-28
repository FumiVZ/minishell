/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:26:40 by vzuccare          #+#    #+#             */
/*   Updated: 2024/06/28 20:43:57 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	ft_add_history(char *line)
{
	HIST_ENTRY	**hist_list;
	int			i;
	int			flag;

	if (!line)
		return ;
	hist_list = history_list();
	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (!is_space(line[i]))
			flag = 1;
		if (flag)
			break ;
		i++;
	}
	if (!hist_list)
	{
		if (flag)
			add_history(line);
		return ;
	}
}

int	ft_history(char **args)
{
	HIST_ENTRY	**hist_list;
	int			i;
	int			n;

	hist_list = history_list();
	i = -1;
	if (args[1])
	{
		if (args[1][0] < '0' || args[1][0] > '9')
			return (-1);
		n = ft_atoi(args[1]);
		while (hist_list[++i])
			;
		n = i - n - 1;
		while (n++ < i)
			if (n < i && n >= 0 && hist_list[n])
				printf("    %d  %s\n", n, hist_list[n]->line);
		return (0);
	}
	if (!hist_list)
		return (0);
	while (hist_list[++i])
		printf("    %d  %s\n", i, hist_list[i]->line);
	return (0);
}
