/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:38 by machrist          #+#    #+#             */
/*   Updated: 2024/07/15 15:38:04 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_check_num(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	if (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] < 13))
		i++;
	if (nptr[i] != '\0')
		return (false);
	return (true);
}

void	basic_exit(t_env *env, t_pipex *pipex, char **str)
{
	if (!str[1])
		return ;
	else if (ft_check_num(str[1]) == false || !ft_is_int(str[1]))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			str[1]);
		parent_free(pipex);
		if (env->envp)
			free_split(env->envp, ft_strstrlen(env->envp));
		exit(2);
	}
	else if (str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		env->status = 1;
	}
}

void	ft_exit(t_env *env, t_pipex *pipex, char **str)
{
	int	status;

	basic_exit(env, pipex, str);
	if (!str[1])
		status = 0;
	else if (str[2])
		return ;
	else
		status = ft_atoi(str[1]);
	while (status > 255)
		status -= 256;
	while (status < 0)
		status += 256;
	parent_free(pipex);
	if (env->envp)
		free_split(env->envp, ft_strstrlen(env->envp));
	ft_putendl_fd("exit", 2);
	exit(status);
}

void	ft_exit_error(t_env *env, int status)
{
	ft_putendl_fd("exit", 2);
	if (env->free_line)
		free(env->free_line);
	if (env->last_line)
		free(env->last_line);
	if (env->envp)
		free_split(env->envp, ft_strstrlen(env->envp));
	exit(status);
}

void	ft_exit_malloc(t_env *env)
{
	ft_putendl_fd("minishell: malloc failed", 2);
	if (env->envp)
		free_split(env->envp, ft_strstrlen(env->envp));
	exit(1);
}
