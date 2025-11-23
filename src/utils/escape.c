/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:00:00 by mgenoves          #+#    #+#             */
/*   Updated: 2025/11/23 17:45:35 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(int code, char *message, int exit_code)
{
	if (code == 1)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	exit(exit_code);
}
