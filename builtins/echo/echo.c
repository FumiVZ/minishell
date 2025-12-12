/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:55:35 by machrist          #+#    #+#             */
/*   Updated: 2024/06/23 16:34:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	check_option(char **args, bool *is_option)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (!ft_strncmp(args[i], "-n", 2))
	{
		j = 2;
		while (args[i][j] == 'n')
			++j;
		if (args[i][j])
			break ;
		if (!args[i + 1])
		{
			*is_option = true;
			return (i + 1);
		}
		++i;
		*is_option = true;
	}
	return (i);
}

void	ft_echo(t_env *env, char **args)
{
	size_t	i;
	bool	is_option;

	i = 1;
	is_option = false;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		env->status = 0;
		return ;
	}
	i = check_option(args, &is_option);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!is_option)
		ft_putchar_fd('\n', 1);
	env->status = 0;
}
