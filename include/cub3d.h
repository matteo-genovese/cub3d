/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sist <fde-sist@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:53:33 by mgenoves          #+#    #+#             */
/*   Updated: 2025/12/11 13:40:08 by fde-sist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define S_WIDTH 1080
# define S_HEIGHT 720
# define FPS 30
# define MAX_ITER 10000

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_input
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	t_color	floor;
	t_color	ceiling;
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_floor;
	int		has_ceiling;
}	t_input;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_height;
}	t_map;

typedef struct s_mlx_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_win;

typedef struct s_vectors
{
	int			map[2];
	int			step[2];
	double		camera[2];
	double		ray[2];
	double		sidedist[2];
	double		deltadist[2];
	int			draw[2];
	int			texture[2];
}	t_vectors;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_vars
{
	t_mlx_win		*mlx;
	t_image			textures[4];
	t_keys			keys;
	char			**map;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			move_speed;
	double			rot_speed;
	double			plane[2];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				map_height;
}	t_vars;

void	init(t_mlx_win *vars);
void	move(t_vars *vars);
void	render(t_vars *vars);
void	hooks(t_vars *vars);
void	my_mlx_pixel_put(t_mlx_win *mlx_win, int x, int y, int color);
void	draw_vertical_texture(t_vars *vars, int x_side[2],
			t_vectors v, double perp_wall_dist);
int		destroy(t_vars *vars);

/* UTILS */
int		ft_exit(int code, char *message, int exit_code);
int		ft_error(char *message);
char	*skip_whitespace(char *str);

/* PARSING */
int		parse_input(char *file_path, t_input *input);
int		parse_map(char *file_path, t_map *map);
int		is_map_line(char *line);
int		parse_color(char *line, t_color *color);
char	*parse_texture_path(char *line);
int		validate_map(t_map *map);
int		find_player(t_map *map);
int		check_walls(t_map *map);
int		parse_no_so(char *line, t_input *input);
int		parse_we_ea(char *line, t_input *input);
int		parse_floor_ceiling(char *line, t_input *input);
int		all_settings_found(t_input *input);
void	init_input(t_input *input);
void	skip_to_map(int fd);
t_list	*read_map_lines(int fd);
int		get_max_width(t_list *map_lines);
void	init_map_struct(t_map *map, t_list *map_lines);
void	free_map_array(char **map, int i);
void	clear_map(t_map *map);
void	free_input(t_input *input);
int		is_empty_line(char *line);
void	fill_line_char(char *dest, char *src, int width, char c);
void	space_to_char(char *str, char c);
void	space_to_one(char **str);
int		is_player_char(char c);

#endif
