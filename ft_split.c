/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elerika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:03:25 by elerika           #+#    #+#             */
/*   Updated: 2021/10/24 14:24:01 by elerika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	sub = 0;
	if (!s)
		return (NULL);
	i = 0;
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char) * (1));
		sub[0] = 0;
		return (sub);
	}
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

static size_t	ft_words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static char	**ft_split2(char const *s, char c, char **str)
{
	size_t		len;
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		len = 0;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		if (*(s - 1) != c)
			str[i++] = ft_substr(start, 0, len);
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(((ft_words(s, c)) + 1) * sizeof(*str));
	if (!str)
		return (0);
	return (ft_split2(s, c, str));
}
