/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:38:46 by mgenoves          #+#    #+#             */
/*   Updated: 2023/11/29 19:21:53 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp_dest;
	char	*temp_src;
	size_t	i;

	temp_dest = (char *) dest;
	temp_src = (char *) src;
	if (n == 0 || (!dest && !src))
		return (dest);
	if (temp_dest > temp_src)
	{
		while (n--)
			temp_dest[n] = temp_src[n];
	}
	else
	{
		i = -1;
		while (++i < n)
			temp_dest[i] = temp_src[i];
	}
	return (dest);
}
