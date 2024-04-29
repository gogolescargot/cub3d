/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:19:45 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/29 19:29:12 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_color(t_asset *asset, t_img *img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = asset->ce;
		else
			color = asset->fl;
		while (x < WIDTH)
		{
			draw_pixel(img, x, y, color);
			x++;
		}
		y++;
		x = 0;
	}
}
