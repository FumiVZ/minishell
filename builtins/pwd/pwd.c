/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:15:47 by machrist          #+#    #+#             */
/*   Updated: 2024/06/25 22:54:49 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = ft_getenv(env->envp, "PWD");
	if (!pwd)
	{
		env->status = 1;
		printf("\n");
		return ;
	}
	printf("%s\n", pwd);
	env->status = 0;
}
