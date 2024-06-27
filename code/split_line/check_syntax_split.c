/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:15:01 by machrist          #+#    #+#             */
/*   Updated: 2024/06/27 19:35:54 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <parthing.h>

static bool	is_redir(char c)
{
	return (c == '<' || c == '>');
}

static bool	is_pipe_or_and(char c)
{
	return (c == '|' || c == '&');
}

static bool	special_case(char **str, size_t i)
{
	return (((is_redir(str[i + 1][0]) || is_pipe_or_and(str[i + 1][0]))
			&& is_redir(str[i][0])) || (is_pipe_or_and(str[i + 1][0])
			&& is_pipe_or_and(str[i][0]))
			|| ft_strlen(str[i]) >= 3);
}

static bool	check_double_special(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (!*str)
		return (false);
	if (str[i][0] == '|' || str[i][0] == '&')
		return (msg_err_syntax(ERR_TOKEN, str[i][0]));
	while (str[i])
	{
		if (is_special_no_par(str[i][0]))
		{
			if (!str[i + 1])
				return (msg_err_syntax(ERR_TOKEN, str[i][0]));
			else if (special_case(str, i))
				return (msg_err_syntax(ERR_TOKEN, str[i + 1][0]));
		}
		if (str[i][0] == '(')
			if (str[i + 1])
				if (str[i + 1][0] == ')')
					return (msg_err_syntax(ERR_TOKEN, str[i + 1][0]));
		i++;
	}
	return (true);
}

bool	check_syntax_split(char **str)
{
	if (!str)
		return (true);
	if (!check_double_special(str))
		return (false);
	return (true);
}
