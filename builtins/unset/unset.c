/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:47:33 by machrist          #+#    #+#             */
/*   Updated: 2024/06/25 23:42:07 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_unset_envp(t_env *env, char **cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (ft_strstrlen(env->envp) + 1)); // valide
	if (!new)
		return (msg_err_ptr_status(ERR_MALLOC, env));
	while (env->envp[i])
	{
		k = 0;
		while (cmd[k])
		{
			if (!ft_strncmp(env->envp[i], cmd[k], ft_strlen(cmd[k]))
				&& env->envp[i][ft_strlen(cmd[k])] == '=')
				free(env->envp[i++]);
			k++;
		}
		if (env->envp[i])
			new[j++] = env->envp[i++];
	}
	new[j] = NULL;
	return (new);
}

static char	**ft_clean_cmd(t_env *env, char **cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**new;

	new = malloc(sizeof(char *) * (ft_strstrlen(cmd) + 1)); // valide
	if (!new)
		return (msg_err_ptr_status(ERR_MALLOC, env));
	i = 0;
	k = 0;
	while (env->envp[i])
	{
		j = 0;
		while (cmd[j])
		{
			if (!ft_strncmp(env->envp[i], cmd[j], ft_strlen(cmd[j]))
				&& env->envp[i][ft_strlen(cmd[j])] == '=')
				new[k++] = cmd[j];
			j++;
		}
		i++;
	}
	new[k] = NULL;
	return (new);
}

void	ft_unset(t_env *env, char **cmd)
{
	char	**new;
	char	**clean_cmd;

	if (!cmd[1])
		return ;
	clean_cmd = ft_clean_cmd(env, cmd + 1);
	if (!clean_cmd)
		return ;
	new = ft_unset_envp(env, clean_cmd);
	free(clean_cmd);
	if (!new)
		return ;
	free(env->envp);
	env->envp = new;
}
