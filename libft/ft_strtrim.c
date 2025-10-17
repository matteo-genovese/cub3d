/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:36:01 by mgenoves          #+#    #+#             */
/*   Updated: 2023/12/11 10:41:59 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, const char *set)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (char_in_set(s1[start], set))
		++start;
	end = ft_strlen(s1) - 1;
	if (start > end)
		return (ft_strdup(""));
	while (char_in_set(s1[end], set))
		--end;
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}
