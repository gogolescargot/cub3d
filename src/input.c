/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 00:14:03 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 00:16:15 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		destroy(data, 0);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		move(data, data->cam, keycode);
	else if (keycode == E)
		door(data, data->cam);
	else if (keycode == L_ARR || keycode == R_ARR)
		rotate(data->cam, keycode, ROTATE_SPEED);
	return (0);
}

int	mousepress(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == LEFT_CLICK)
		data->cam->shot = true;
	return (0);
}

int	mouse(t_mlx *mlx, t_cam *cam)
{
	t_coord	mouse;

	mlx_mouse_get_pos(mlx->ptr, mlx->win, &mouse.x, &mouse.y);
	if (mouse.x > WIDTH / 2 + WIDTH / 4)
		rotate(cam, R_ARR, ROTATE_SPEED / 5);
	else if (mouse.x < WIDTH / 2 - WIDTH / 4)
		rotate(cam, L_ARR, ROTATE_SPEED / 5);
	return (0);
}
