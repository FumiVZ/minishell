/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:49:45 by machrist          #+#    #+#             */
/*   Updated: 2024/06/28 14:45:56 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	msg_err(char *err)
{
	ft_printf_fd(2, err);
	return (0);
}

void	*msg_err_ptr_status(char *err, t_env *env)
{
	ft_printf_fd(2, err);
	env->status = 1;
	return (NULL);
}

void	*msg_err_ptr(char *err)
{
	ft_printf_fd(2, err);
	return (NULL);
}

void	msg_perror(t_env *env, char *err)
{
	ft_printf_fd(2, "minishell: %s: %s\n", err, strerror(errno));
	env->status = 1;
}

int	msg_err_syntax(char *err, char *c)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('`', 2);
	if (ft_strlen(c) > 1)
		write(2, c, 2);
	else
		write(2, c, 1);
	ft_putstr_fd("'\n", 2);
	return (0);
}
