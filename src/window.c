/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:45:59 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 02:46:10 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(t_data *data, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		error("minilibX initialization failed");
		free_data(data);
		return (1);
	}
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "ggalon - cub3d");
	if (!mlx->win)
	{
		error("minilibX window failed");
		mlx_destroy_display(data->mlx->ptr);
		free_data(data);
		ft_free(mlx->ptr);
		return (1);
	}
	if (image_init(data, mlx))
		return (1);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &destroy, data);
	return (0);
}

int	image_init(t_data *data, t_mlx *mlx)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->img.ptr)
	{
		error("minilibX image failed");
		mlx_destroy_window(data->mlx->ptr, data->mlx->win);
		mlx_destroy_display(data->mlx->ptr);
		free_data(data);
		ft_free(mlx->ptr);
		return (1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr,
			&mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
	mlx->img = mlx->img;
	return (0);
}
