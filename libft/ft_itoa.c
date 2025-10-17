/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:29:48 by mgenoves          #+#    #+#             */
/*   Updated: 2023/12/12 15:35:21 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennumber(long nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static char	*ft_aux(long nb, size_t i, char *str)
{
	if (nb < 0)
	{
		nb *= -1;
		str[i] = '-';
		++i;
	}
	if (nb < 10)
	{
		str[i] = nb + '0';
		str[i + 1] = '\0';
		return (str);
	}
	else
	{
		str[i] = nb % 10 + '0';
		ft_aux(nb / 10, i + 1, str);
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		i;
	int		j;
	char	temp;

	nb = n;
	str = (char *)malloc((ft_lennumber(nb) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_aux(nb, 0, str);
	if (str[0] == '-')
		i = 1;
	else
		i = 0;
	j = ft_lennumber(nb) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		++i;
		--j;
	}
	return (str);
}
