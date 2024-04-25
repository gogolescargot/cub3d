/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:45:55 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/25 20:12:54 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define L_ARR 65361
# define R_ARR 65363
# define LEFT_CLICK 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR_X 4
# define DOOR_Y 5

# define WIDTH 800
# define HEIGHT 600

# define WIDTH_WALL 450
# define HEIGHT_WALL 450

# define WIDTH_GUN 128
# define HEIGHT_GUN 128

# define PI 3.14159265359

# define ROTATE_SPEED 0.031416
# define MOVE_SPEED 0.05

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_draw
{
	t_point	dist;
	t_point	delta_dist;
	t_coord	step_dir;
	t_coord	wall_pixel;
	t_coord	screen;
	t_coord	map;
	double	perp_wall_dist;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}	t_draw;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_cam
{
	t_point		pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray;
	t_coord		door;
	bool		door_crossed;
	double		camera_x;
	bool		shot;
}	t_cam;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
	t_img	door;
	t_img	gun_0;
	t_img	gun_1;
	t_img	gun_2;
	t_img	gun_3;
	t_img	gun_4;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_mlx;

typedef struct s_asset
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		fl;
	int		ce;
}	t_asset;

typedef struct s_data
{
	t_list	*file;
	char	**map;
	int		height;
	int		lengh;
	t_asset	*asset;
	t_mlx	*mlx;
	t_cam	*cam;
}	t_data;

int		keypress(int keycode, t_data *data);
int		mousepress(int keycode, int x, int y, t_data *data);
void	move(t_data *data, t_cam *cam, int keycode);
void	rotate(t_cam *cam, int keycode, double rotate_speed);
int		destroy(t_data *data, int error_code);

int		mouse(t_mlx *mlx, t_cam *cam);
int		loop(t_data *data);

void	struct_init(t_data *data, t_asset *asset, t_mlx	*mlx, t_cam *cam);
int		type_init(char ***type);

int		file_init(t_data *data, const char *file);
int		file_open(t_data *data, const char *file, int *fd);
int		file_read(t_data *data, int fd);

int		map_init(t_data *data, t_asset *asset);
int		map_duplicate(t_data *data, char ***dst);
int		map_asset(t_asset *asset, const char *str, int i);
int		map_check_asset(t_asset *asset, int i, char **info, char **type);

int		map_check(t_data *data);
int		map_check_char(t_data *data);
int		map_check_entities(t_data *data);
int		map_check_border(t_data *data);
int		map_check_extension(const char *filename);

int		map_string_init(t_data *data, t_list *map);
int		map_lengh(t_list *lst);
int		map_string_insert(t_data *data, char *str, int max_len, char **dst);

void	camera_init(t_data *data, t_cam *cam);
void	camera_coord(t_data *data, t_cam *cam);
void	camera_dir(t_data *data, t_cam *cam);
void	camera_plane(t_data *data, t_cam *cam);

int		window_init(t_data *data, t_mlx *mlx);
int		image_init(t_data *data, t_mlx *mlx);

int		asset_init(t_data *data, t_asset *asset, t_mlx *mlx);
int		asset_check(t_asset *asset);
int		asset_open(char *filepath);
int		asset_insert(t_asset *asset, char *info, int i);
int		asset_insert_string(t_asset *asset, char *info, int i);
int		asset_insert_color(t_asset *asset, char *info, int i);
int		asset_format_color(char *str, int *rgb);
int		asset_atoi(char	**color, int *r, int *g, int *b);
void	asset_destroy(t_mlx *mlx);

int		draw(t_data *data);
void	draw_color(t_asset *asset, t_img *img);
void	draw_map(t_data *data, t_img *img, t_cam *cam);
void	draw_gun(t_mlx *mlx, t_img *img, t_cam *cam);
void	draw_shot(t_cam *cam);
void	draw_init(t_cam *cam, t_draw *draw);
void	draw_dir(t_cam *cam, t_draw *draw);
void	draw_dda(t_data *data, t_draw *draw);
void	draw_assset_bounds(t_draw *draw);
void	draw_assset_pixel(t_cam *cam, t_draw *draw);
void	draw_asset(t_mlx *mlx, t_img *img, t_draw *draw);
void	draw_pixel(t_img *img, int x, int y, unsigned int color);

bool	is_empty(char *str);
bool	is_border(t_data *data, int i, int j);
bool	is_outside(t_data *data, int x, int y);
bool	is_coord(t_data *data, char **str_map, int *i, int *j);
bool	is_valid(t_data *data, t_point *point);

void	free_data(t_data *data);
void	move_point(t_cam *cam, t_point *tmp, t_vector *move_dir, int keycode);
int		args_check(int argc, const char **argv);
int		error(char *str);
int		dfs(t_data *data, char **str_map, int i, int j);
double	absolute(double nbr);

#endif