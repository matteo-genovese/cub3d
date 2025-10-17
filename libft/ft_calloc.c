/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:30:27 by mgenoves          #+#    #+#             */
/*   Updated: 2023/12/11 09:48:09 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n_elem, size_t size)
{
	char	*cal;

	cal = (char *)malloc(n_elem * size);
	if (!cal)
		return (0);
	ft_bzero(cal, n_elem * size);
	return (cal);
}
