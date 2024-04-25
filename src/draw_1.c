/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:55:43 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/25 20:16:08 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_data *data)
{
	t_cam	*cam;
	t_mlx	*mlx;
	t_img	*img;
	t_draw	draw;

	mlx = data->mlx;
	cam = data->cam;
	img = &mlx->img;
	draw.screen.x = 0;
	draw_color(data->asset, img);
	while (draw.screen.x < WIDTH)
	{
		draw_init(cam, &draw);
		draw_dir(cam, &draw);
		draw_dda(data, &draw);
		draw_assset_bounds(&draw);
		draw_assset_pixel(cam, &draw);
		draw_asset(mlx, img, &draw);
		draw.screen.x++;
	}
	draw_map(data, img, cam);
	draw_gun(mlx, img, cam);
	mlx_put_image_to_window(mlx->ptr, mlx->win, img->ptr, 0, 0);
	return (0);
}

void	draw_color(t_asset *asset, t_img *img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < HEIGHT - 1)
	{
		if (y < HEIGHT / 2)
			color = asset->ce;
		else
			color = asset->fl;
		while (x < WIDTH - 1)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_square(t_img *img, int x, int y, int color)
{
	t_coord	pixel;

	pixel.x = 0;
	pixel.y = 0;
	while (pixel.y < 10)
	{
		while (pixel.x < 10)
		{
			draw_pixel(img, x + pixel.x, y + pixel.y, color);
			pixel.x++;
		}
		pixel.x = 0;
		pixel.y++;
	}
}

void	draw_map(t_data *data, t_img *img, t_cam *cam)
{
	t_coord	coord;
	t_coord	screen;

	coord.x = (int)(cam->pos.x) - 5;
	coord.y = (int)(cam->pos.y) - 5;
	screen.x = 0;
	screen.y = 0;
	while (screen.y < 11)
	{
		while (screen.x < 11)
		{
			if (screen.x == 5 && screen.y == 5)
				draw_square(img, screen.x * 10, screen.y * 10, 0x0000FF);
			else if ((coord.x >= 0 && coord.x <= data->lengh - 1)
				&& (coord.y >= 0 && coord.y <= data->height - 1))
			{
				if (data->map[coord.y][coord.x] == '1')
					draw_square(img, screen.x * 10, screen.y * 10, 0xFFFFFF);
				else if (data->map[coord.y][coord.x] == 'O')
					draw_square(img, screen.x * 10, screen.y * 10, 0x00FF00);
				else if (data->map[coord.y][coord.x] == 'C')
					draw_square(img, screen.x * 10, screen.y * 10, 0xFF0000);
				else
					draw_square(img, screen.x * 10, screen.y * 10, 0x000000);
			}
			else
				draw_square(img, screen.x * 10, screen.y * 10, 0x000000);
			coord.x++;
			screen.x++;
		}
		coord.x -= 11;
		coord.y++;
		screen.x = 0;
		screen.y++;
	}
}

void	draw_shot(t_cam *cam)
{
	cam->shot = true;
}

void	draw_gun_utils(t_img *img, t_img *gun, t_coord pixel)
{
	t_coord			multp;
	unsigned int	color;

	multp.x = 0;
	multp.y = 0;
	color = *(int *)(gun->addr + pixel.y * gun->size_line + pixel.x * (gun->bpp / 8));
	if (color != 0xFF000000)
	{
		while (multp.y < 2)
		{
			while (multp.x < 2)
			{
				draw_pixel(img, (pixel.x * 2 + multp.x) + WIDTH / 2, (pixel.y * 2 + multp.y) + HEIGHT - HEIGHT_GUN * 2, color);
				multp.x++;
			}
			multp.y++;
			multp.x = 0;
		}
	}
}

void	draw_gun(t_mlx *mlx, t_img *img, t_cam *cam)
{
	t_coord		pixel;
	t_img		*gun;
	static int	i;

	pixel.x = 0;
	pixel.y = 0;
	if (cam->shot)
	{
		if (i == 0)
			gun = &mlx->gun_1;
		else if (i == 1)
			gun = &mlx->gun_2;
		else if (i == 2)
			gun = &mlx->gun_3;
		else if (i == 3)
			gun = &mlx->gun_4;
		else if (i == 4)
		{
			gun = &mlx->gun_0;
			cam->shot = false;
			i = -1;
		}
		i++;
	}
	else
		gun = &mlx->gun_0;
	while (pixel.y < HEIGHT_GUN)
	{
		while (pixel.x < WIDTH_GUN)
		{
			draw_gun_utils(img, gun, pixel);
			pixel.x++;
		}
		pixel.y++;
		pixel.x = 0;
	}
}

void	draw_init(t_cam *cam, t_draw *draw)
{
	cam->camera_x = draw->screen.x * 2.0 / WIDTH - 1;
	cam->ray.x = cam->dir.x + cam->plane.x * cam->camera_x;
	cam->ray.y = cam->dir.y + cam->plane.y * cam->camera_x;
	draw->map.x = cam->pos.x;
	draw->map.y = cam->pos.y;
	draw->delta_dist.x = absolute(1 / cam->ray.x);
	draw->delta_dist.y = absolute(1 / cam->ray.y);
}

void	draw_dir(t_cam *cam, t_draw *draw)
{
	if (cam->ray.x < 0)
	{
		draw->step_dir.x = -1;
		draw->dist.x = (cam->pos.x - draw->map.x) * draw->delta_dist.x;
	}
	else
	{
		draw->step_dir.x = 1;
		draw->dist.x = (draw->map.x + 1 - cam->pos.x) * draw->delta_dist.x;
	}
	if (cam->ray.y < 0)
	{
		draw->step_dir.y = -1;
		draw->dist.y = (cam->pos.y - draw->map.y) * draw->delta_dist.y;
	}
	else
	{
		draw->step_dir.y = 1;
		draw->dist.y = (draw->map.y + 1 - cam->pos.y) * draw->delta_dist.y;
	}
}

bool	is_door(t_cam *cam, int x, int y)
{
	if ((int)cam->pos.x - x <= 1 && (int)cam->pos.x - x >= -1
		&& (int)cam->pos.y - y <= 1 && (int)cam->pos.y - y >= -1)
		return (true);
	return (false);
}

void	door_check(t_data *data, t_draw *draw, t_cam *cam)
{
	if (!is_outside(data, draw->map.x, draw->map.y) && ft_strchr("OC", data->map[draw->map.y][draw->map.x]))
	{
		if (draw->side == WEST || draw->side == EAST)
			draw->side = DOOR_X;
		else
			draw->side = DOOR_Y;
	}
	if (draw->screen.x != WIDTH / 2)
		return ;
	if (!is_outside(data, draw->map.x, draw->map.y) && ft_strchr("OC", data->map[draw->map.y][draw->map.x]) && is_door(cam, draw->map.x, draw->map.y))
	{
		cam->door_crossed = true;
		cam->door.x = draw->map.x;
		cam->door.y = draw->map.y;
	}
	else if (!cam->door_crossed)
	{
		cam->door.x = -1;
		cam->door.y = -1;
	}
}

void	draw_dda(t_data *data, t_draw *draw)
{
	while (true)
	{
		if (draw->dist.x < draw->dist.y)
		{
			draw->dist.x += draw->delta_dist.x;
			draw->map.x += draw->step_dir.x;
			if (draw->step_dir.x == 1)
				draw->side = WEST;
			else
				draw->side = EAST;
		}
		else
		{
			draw->dist.y += draw->delta_dist.y;
			draw->map.y += draw->step_dir.y;
			if (draw->step_dir.y == 1)
				draw->side = NORTH;
			else
				draw->side = SOUTH;
		}
		door_check(data, draw, data->cam);
		if (is_outside(data, draw->map.x, draw->map.y)
			|| ft_strchr("1C", data->map[draw->map.y][draw->map.x]))
			break ;
	}
	data->cam->door_crossed = false;
}
