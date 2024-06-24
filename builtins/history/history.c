/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 01:52:43 by vincent           #+#    #+#             */
/*   Updated: 2024/06/24 15:58:54 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	is_same(char *line, char *hist)
{
	int	i;

	i = 0;
	while (line[i] && hist[i])
	{
		if (line[i] != hist[i])
			return (0);
		i++;
	}
	if (line[i] || hist[i])
		return (0);
	return (1);
}

void	ft_add_history(char *line)
{
	HIST_ENTRY	**hist_list;
	int			i;
	int			flag;

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
	while (hist_list[i])
		i++;
	if (!is_same(line, hist_list[i - 1]->line) && flag)
		add_history(line);
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
				printf("%d: %s\n", n, hist_list[n]->line);
		return (0);
	}
	if (!hist_list)
		return (0);
	while (hist_list[++i])
		printf("%d: %s\n", i, hist_list[i]->line);
	return (0);
}
