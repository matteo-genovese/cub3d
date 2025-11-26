/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:58:57 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/26 22:20:19 by mgenoves         ###   ########.fr       */
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
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
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
