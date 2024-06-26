/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:00 by machrist          #+#    #+#             */
/*   Updated: 2024/06/25 23:58:31 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parthing.h"

static bool	is_dir(const char *dir, char *pwd)
{
	char		*path;
	struct stat	info;

	if (!pwd)
		return (msg_err(GETCWD));
	path = malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(dir) + 2));
	if (!path)
	{
		free(pwd);
		return (msg_err(MALLOC));
	}
	ft_strlcpy(path, pwd, ft_strlen(pwd) + 1);
	ft_strlcat(path, "/", ft_strlen(pwd) + 2);
	ft_strlcat(path, dir, ft_strlen(pwd) + ft_strlen(dir) + 2);
	free(pwd);
	if (stat(path, &info) != 0)
	{
		free(path);
		return (msg_err(STAT));
	}
	free(path);
	if (S_ISDIR(info.st_mode))
		return (true);
	return (false);
}

static bool	match(const char *str, const char *pattern, const char *dir)
{
	if (str[0] == '.' && pattern[0] != '.')
		return (0);
	while ((*str && *pattern) || *pattern == '*')
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
		}
		if (*pattern != '?' && *str != *pattern)
		{
			while (*pattern == '/')
				pattern++;
			if (*pattern == '\0' && is_dir(dir, getcwd(NULL, 0))
				&& ft_strncmp("..", dir, ft_strlen(dir)))
				return (1);
			return (0);
		}
		str++;
		pattern++;
	}
	return (*str == '\0' && *pattern == '\0');
}

static bool	set_result(t_list **result, const struct dirent *entry,
		const char *pattern)
{
	const char	*tmp;
	t_list		*new;

	if (pattern[ft_strlen(pattern) - 1] == '/')
		tmp = ft_strjoin(entry->d_name, "/");
	else
		tmp = ft_strdup(entry->d_name);
	if (!tmp)
		return (msg_err(MALLOC));
	new = ft_lstnew((char *)tmp);
	if (!new)
	{
		free((char *)tmp);
		return (msg_err(MALLOC));
	}
	ft_lstadd_back(result, new);
	return (true);
}

char	**wildcard_match(const char *pattern, char **str, size_t i)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			**result;
	char			**tmp;

	result = malloc(sizeof(t_list *));
	if (!result)
		return (msg_err_ptr(MALLOC));
	*result = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match(entry->d_name, pattern, entry->d_name))
		{
			if (!set_result(result, entry, pattern))
			{
				ft_lstclear(result, free);
				closedir(dir);
				return (NULL);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	tmp = sort_result(result, str, i);
	return (tmp);
}
