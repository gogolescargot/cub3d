/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 04:00:44 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/25 23:51:19 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_asset_bounds(t_draw *draw)
{
	if (draw->side == EAST || draw->side == WEST || draw->side == DOOR_X)
		draw->perp_wall_dist = draw->dist.x - draw->delta_dist.x;
	else
		draw->perp_wall_dist = draw->dist.y - draw->delta_dist.y;
	draw->line_height = HEIGHT / draw->perp_wall_dist;
	draw->draw_start = -draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
}

void	draw_asset_pixel(t_cam *cam, t_draw *draw)
{
	if (draw->side == WEST || draw->side == EAST || draw->side == DOOR_X)
		draw->wall_x = cam->pos.y + draw->perp_wall_dist * cam->ray.y;
	else
		draw->wall_x = cam->pos.x + draw->perp_wall_dist * cam->ray.x;
	draw->wall_x -= floor(draw->wall_x);
	draw->wall_pixel.x = draw->wall_x * WIDTH_WALL;
	if ((draw->side == WEST || draw->side == EAST
			|| draw->side == DOOR_X) && cam->ray.x > 0)
		draw->wall_pixel.x = WIDTH_WALL - draw->wall_pixel.x - 1;
	if ((draw->side == NORTH || draw->side == SOUTH
			|| draw->side == DOOR_Y) && cam->ray.y < 0)
		draw->wall_pixel.x = WIDTH_WALL - draw->wall_pixel.x - 1;
}

void	draw_asset_select(t_draw *draw, t_mlx *mlx, int padding, char **color)
{
	if (draw->side == NORTH)
		*color = mlx->no.addr + padding;
	else if (draw->side == SOUTH)
		*color = mlx->so.addr + padding;
	else if (draw->side == WEST)
		*color = mlx->we.addr + padding;
	else if (draw->side == EAST)
		*color = mlx->ea.addr + padding;
	else if (draw->side == DOOR_X || draw->side == DOOR_Y)
		*color = mlx->door.addr + padding;
}

void	draw_asset(t_mlx *mlx, t_img *img, t_draw *draw)
{
	double	step;
	double	tex_pos;
	char	*color;
	int		padding;

	step = 1.0 * HEIGHT_WALL / draw->line_height;
	tex_pos = (draw->draw_start - HEIGHT / 2 + draw->line_height / 2) * step;
	draw->screen.y = draw->draw_start;
	while (draw->screen.y < draw->draw_end)
	{
		draw->wall_pixel.y = tex_pos;
		tex_pos += step;
		padding = draw->wall_pixel.y * mlx->we.size_line
			+ draw->wall_pixel.x * (mlx->no.bpp / 8);
		draw_asset_select(draw, mlx, padding, &color);
		draw_pixel(img, draw->screen.x, draw->screen.y, *(int *)color);
		draw->screen.y++;
	}
}

void	draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}
