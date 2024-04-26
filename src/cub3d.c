/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 18:25:05 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, const char *argv[])
{
	t_data	data;
	t_asset	asset;
	t_mlx	mlx;
	t_cam	cam;

	struct_init(&data, &asset, &mlx, &cam);
	if (args_check(argc, argv))
		return (1);
	if (file_init(&data, argv[1]))
		return (1);
	if (map_init(&data, &asset))
		return (1);
	if (map_check(&data))
		return (1);
	camera_init(&data, &cam);
	if (window_init(&data, &mlx))
		return (1);
	if (asset_init(&data, &asset, &mlx))
		return (1);
	mlx_loop_hook(mlx.ptr, &loop, &data);
	mlx_loop(mlx.ptr);
	destroy(&data, 0);
	return (0);
}

void	move(t_data *data, t_cam *cam, int keycode)
{
	t_vector	move_dir;
	t_point		tmp;

	move_dir.x = cam->dir.x * MOVE_SPEED;
	move_dir.y = cam->dir.y * MOVE_SPEED;
	move_point(cam, &tmp, &move_dir, keycode);
	if (is_valid(data, &tmp))
	{
		cam->pos.x = tmp.x;
		cam->pos.y = tmp.y;
	}
}

void	rotate(t_cam *cam, int keycode, double rotate_speed)
{
	double	old_plane_x;
	double	old_dir_x;

	if (keycode == L_ARR)
		rotate_speed *= -1;
	old_dir_x = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(rotate_speed)
		- cam->dir.y * sin(rotate_speed);
	cam->dir.y = old_dir_x * sin(rotate_speed)
		+ cam->dir.y * cos(rotate_speed);
	old_plane_x = cam->plane.x;
	cam->plane.x = cam->plane.x * cos(rotate_speed)
		- cam->plane.y * sin(rotate_speed);
	cam->plane.y = old_plane_x * sin(rotate_speed)
		+ cam->plane.y * cos(rotate_speed);
}

int	loop(t_data *data)
{
	clock_t	start_time;
	clock_t	end_time;
	int		wait_time;

	start_time = clock();
	mouse(data->mlx, data->cam);
	draw(data);
	end_time = clock();
	wait_time = ((1000.0 / FPS) - ((end_time - start_time) / 1000)) * 1000;
	if (wait_time > 0)
		usleep(wait_time);
	return (0);
}

int	destroy(t_data *data, int error_code)
{
	asset_destroy(data->mlx);
	mlx_destroy_image(data->mlx->ptr, data->mlx->img.ptr);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	mlx_destroy_display(data->mlx->ptr);
	ft_free(data->mlx->ptr);
	free_data(data);
	exit(error_code);
}
