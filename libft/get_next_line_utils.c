/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:58:57 by mgenoves          #+#    #+#             */
/*   Updated: 2025/10/17 11:13:25 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_sc(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = -1;
	while (s[++i])
		if (str[i] == (unsigned char) c)
			return (i);
	if (s[i] == (unsigned char) c)
		return (i);
	return (i);
}

int	gnl_check_nl(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = -1;
	while (s[++i])
		if (str[i] == (unsigned char) c)
			return (1);
	if (s[i] == (unsigned char) c)
		return (1);
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2, int flag)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len_s1 && s1[i])
		str[i] = s1[i];
	i = -1;
	while (++i < len_s2 && s2[i])
		str[len_s1 + i] = s2[i];
	str[len_s1 + len_s2] = '\0';
	if (flag)
	{
		free(s1);
		free(s2);
	}
	return (str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (start >= gnl_strlen(s))
		return (NULL);
	i = -1;
	if (len < gnl_strlen(s) - start)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((gnl_strlen(s) - start + 1) * sizeof(char));
	if (!str || !s)
		return (NULL);
	while (++i < len && i < gnl_strlen(s) && s[i + start])
		str[i] = s[i + start];
	str[i] = '\0';
	return (str);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		++i;
	return (i);
}
