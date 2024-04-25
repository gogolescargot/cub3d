/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:55:43 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 00:20:23 by ggalon           ###   ########.fr       */
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
		draw_dda_side(draw);
		door_check(data, draw, data->cam);
		if (is_outside(data, draw->map.x, draw->map.y)
			|| ft_strchr("1C", data->map[draw->map.y][draw->map.x]))
			break ;
	}
	data->cam->door_crossed = false;
}

void	draw_dda_side(t_draw *draw)
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
}
