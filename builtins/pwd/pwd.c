/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:15:47 by machrist          #+#    #+#             */
/*   Updated: 2024/06/26 20:50:45 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		env->status = 1;
		printf("\n");
		free(pwd);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	env->status = 0;
}
