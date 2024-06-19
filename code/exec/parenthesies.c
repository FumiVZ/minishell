/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:20:39 by vincent           #+#    #+#             */
/*   Updated: 2024/06/18 20:25:40 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* //check if there is any parentheses in the command and delete them
static void	delete_parentheses(t_pipex *pipex)
{
	int	i;
	int	j;
	int	start[2];

	start[0] = -1;
	start[1] = -1;
	i = -1;
	while (pipex->cmd[++i] != NULL)
	{
		j = -1;
		while (pipex->cmd[i][++j] != '\0')
		{
			if (pipex->cmd[i][j] == '(')
			{
				start[0] = i;
				start[1] = j;
			}
		}
	}
}

static	int count_len(char **cmd, int start[2], int end[2])
{
	int	i;
	int	len;

	i = start[0];
	len = 0;
	while (i < end[0])
	{
		if (i == start[0])
			len += ft_strlen(cmd[i]) - start[1];
		else if (i == end[0])
			len += end[1];
		else
			len += ft_strlen(cmd[i]);
		i++;
	}
	return (len);
}
{

}
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (cmd[++i] != NULL)
		len++;
	return (len);
}
 */

/* static char **save_parentheses(t_pipex *pipex, int start, int end)
{
	char	**new_cmd;
	int		i;
	int		j;

	new_cmd = malloc(sizeof(char *) * (end - start + 1));
	if (!new_cmd)
		msg_error(ERR_MALLOC, pipex);
	i = start;
	j = 0;
	while (i < end)
	{
		if (i == start)
			new_cmd[j] = ft_strdup(pipex->cmd[i] + 1);
		else if (i == end - 1)
			new_cmd[j] = \
				ft_substr(pipex->cmd[i], 0, ft_strlen(pipex->cmd[i]) - 1);
		else
			new_cmd[j] = ft_strdup(pipex->cmd[i]);
		i++;
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
} */

char	**delete_parentheses(char **str, t_pipex *pipex)
{
	int	i;
	int j;
	char **new;

	i = -1;
	j = 0;
	while (str[++i] && ft_strncmp(str[i], "&&", 2) && ft_strncmp(str[i], "||", 2))
	{
		if (str[i][0] == '(')
		{
			new = malloc(sizeof(char *) * (ft_strstrlen(str) - 1));
			if (!new)
				msg_error(ERR_MALLOC, pipex);
			i = 0;
			while ((str[i] && ft_strncmp(str[i], "&&", 2) && ft_strncmp(str[i], "||", 2)))
			{
				if (str[i][0] != '(' && str[i][0] != ')')
					new[j++] = ft_strdup(str[i]);
				i++;
			}
			new[j] = NULL;
			return (new);
		}
		if (str[i][0] == ')')
		{
			new = malloc(sizeof(char *) * (ft_strstrlen(str)));
			if (!new)
				msg_error(ERR_MALLOC, pipex);
			i = 0;
			while ((str[i] && ft_strncmp(str[i], "&&", 2) && ft_strncmp(str[i], "||", 2)))
			{
				if (str[i][0] != '(' && str[i][0] != ')')
					new[j++] = ft_strdup(str[i]);
				i++;
			}
			new[j] = NULL;
			return (new);
		}
	}
	return (NULL);
}

//WORK IN PROGRESS