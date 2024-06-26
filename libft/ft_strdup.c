/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machrist <machrist@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:27:01 by machrist          #+#    #+#             */
/*   Updated: 2024/06/26 18:12:26 by machrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_strstrdup(const char **s)
{
	char	**str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_strstrlen((char **)s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = ft_strdup(s[i]);
		if (!str[i])
		{
			free_split(str, i);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
