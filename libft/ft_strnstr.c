/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:51:01 by mgenoves          #+#    #+#             */
/*   Updated: 2023/12/05 22:39:41 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)big;
	if (!little[0] || ((str == NULL) && !len))
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == little[j] && i + j < len)
		{
			if (!little[j + 1])
				return (str + i);
			j++;
		}
		++i;
	}
	return (NULL);
}
