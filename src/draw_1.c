/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:55:43 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/20 07:23:46 by ggalon           ###   ########.fr       */
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
	draw_map(data, data->asset, img);
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

void	draw_map(t_data *data, t_asset *asset, t_mlx *mlx, t_cam *cam)
{
	t_coord	coord;
	t_coord start;
	t_coord	screen;

	coord.x = cam->pos.x;
	coord.y = cam->pos.y;

	coord.x -= 10;
	coord.y -= 10;
	start.x = coord.x;
	start.y = coord.y;
	screen.x = 0;
	screen.y = 0;
	while (coord.y < start.y + 20)
	{
		while (coord.x < start.x + 20)
		{
			if (coord.x >= 0 || coord.x <= data->lengh - 1)
			{
				mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->no.ptr, screen.x * 10, screen.y * 10);
			}
			coord.x++;
			screen.x++;
		}
		coord.x -= 20;
		coord.y++;
		screen.x = 0;
		screen.y++;
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
		if (draw->map.y < 0 || draw->map.y > data->height - 1
			|| draw->map.x < 0 || draw->map.x > data->lengh - 1
			|| data->map[draw->map.y][draw->map.x] == '1')
			break ;
	}
}
