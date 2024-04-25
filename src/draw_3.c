/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 01:55:43 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 00:24:35 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_data *data, t_img *img, t_cam *cam)
{
	t_coord	coord;
	t_coord	screen;

	coord.x = (int)(cam->pos.x) - 5;
	coord.y = (int)(cam->pos.y) - 5;
	screen.x = -1;
	screen.y = -1;
	while (++screen.y < 11)
	{
		while (++screen.x < 11)
		{
			if (screen.x == 5 && screen.y == 5)
				draw_square(img, screen.x * 10, screen.y * 10, 0x0000FF);
			else if ((coord.x >= 0 && coord.x <= data->lengh - 1)
				&& (coord.y >= 0 && coord.y <= data->height - 1))
				draw_map_select(data, img, screen, coord);
			else
				draw_square(img, screen.x * 10, screen.y * 10, 0x000000);
			coord.x++;
		}
		coord.x -= 11;
		coord.y++;
		screen.x = -1;
	}
}

void	draw_map_select(t_data *data, t_img *img, t_coord screen, t_coord coord)
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

void	draw_gun(t_mlx *mlx, t_img *img, t_cam *cam)
{
	t_coord		pixel;
	t_img		*gun;

	pixel.x = 0;
	pixel.y = 0;
	if (cam->shot)
		draw_gun_select(mlx, cam, &gun);
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

void	draw_gun_select(t_mlx *mlx, t_cam *cam, t_img **gun)
{
	static int	i;

	if (i == 0)
		*gun = &mlx->gun_1;
	else if (i == 1)
		*gun = &mlx->gun_2;
	else if (i == 2)
		*gun = &mlx->gun_3;
	else if (i == 3)
		*gun = &mlx->gun_4;
	else if (i == 4)
	{
		*gun = &mlx->gun_0;
		cam->shot = false;
		i = -1;
	}
	i++;
}

void	draw_gun_utils(t_img *img, t_img *gun, t_coord pixel)
{
	t_coord			multp;
	unsigned int	color;

	multp.x = 0;
	multp.y = 0;
	color = *(int *)(gun->addr + pixel.y * gun->size_line
			+ pixel.x * (gun->bpp / 8));
	if (color != 0xFF000000)
	{
		while (multp.y < 2)
		{
			while (multp.x < 2)
			{
				draw_pixel(img, (pixel.x * 2 + multp.x) + WIDTH / 2,
					(pixel.y * 2 + multp.y) + HEIGHT - HEIGHT_GUN * 2, color);
				multp.x++;
			}
			multp.y++;
			multp.x = 0;
		}
	}
}
