/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:16:27 by mgenoves          #+#    #+#             */
/*   Updated: 2025/10/17 11:13:25 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_fill_line(int fd, char **left_o, char *buffer, int *bytes_read);
char	*gnl_fill_line_w_left_o(char **left_o);
void	gnl_memset(void *s, int c, size_t n);
int		gnl_sc(const char *s, int c);
int		gnl_check_nl(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2, int flag);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
void	gnl_m(void *dest, const void *src, int n);
size_t	gnl_strlen(const char *s);

#endif
