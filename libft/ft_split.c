/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:19:16 by mgenoves          #+#    #+#             */
/*   Updated: 2023/12/12 16:18:37 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static void	ft_aux(size_t *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = -1;
}

char	**ft_split(char const *s, char c)
{
	size_t	i[3];
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	ft_aux(i);
	while (s[i[0]])
	{
		while (s[i[0]] == c)
			++i[0];
		if (s[i[0]])
		{
			i[1] = i[0];
			while (s[i[0]] != c && s[i[0]])
				(i[0])++;
			split[++(i[2])] = ft_substr(s, i[1], i[0] - i[1]);
			if (!split[i[2]])
				free(split[i[2]]);
		}
	}
	split[++(i[2])] = NULL;
	return (split);
}
