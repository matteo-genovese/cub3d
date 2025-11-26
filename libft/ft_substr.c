/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:30:45 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/26 22:20:13 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	i = -1;
	if (len < ft_strlen(s) - start)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (!str || !s)
		return (NULL);
	while (++i < len && i < ft_strlen(s) && s[i + start])
		str[i] = s[i + start];
	str[i] = '\0';
	return (str);
}
