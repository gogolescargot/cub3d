/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:55:57 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/29 18:00:27 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	asset_init(t_data *data, t_asset *asset, t_mlx *mlx)
{
	if (asset_check_open(asset))
		destroy(data, 1);
	asset_init_pointer(mlx, asset);
	if (!mlx->no.ptr || !mlx->so.ptr || !mlx->we.ptr
		|| !mlx->ea.ptr || !mlx->door.ptr
		|| !mlx->gun_0.ptr || !mlx->gun_1.ptr || !mlx->gun_2.ptr
		|| !mlx->gun_3.ptr || !mlx->gun_4.ptr)
	{
		error("Asset error");
		destroy(data, 1);
	}
	asset_check_size(data, mlx);
	asset_init_address(mlx);
	return (0);
}

void	asset_init_pointer(t_mlx *mlx, t_asset *asset)
{
	mlx->no.ptr = mlx_xpm_file_to_image
		(mlx->ptr, asset->no, &mlx->no.width, &mlx->no.height);
	mlx->so.ptr = mlx_xpm_file_to_image
		(mlx->ptr, asset->so, &mlx->so.width, &mlx->so.height);
	mlx->we.ptr = mlx_xpm_file_to_image
		(mlx->ptr, asset->we, &mlx->we.width, &mlx->we.height);
	mlx->ea.ptr = mlx_xpm_file_to_image
		(mlx->ptr, asset->ea, &mlx->ea.width, &mlx->ea.height);
	mlx->door.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/door.xpm", &mlx->door.width, &mlx->door.height);
	mlx->gun_0.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/gun_0.xpm", &mlx->gun_0.width, &mlx->gun_0.height);
	mlx->gun_1.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/gun_1.xpm", &mlx->gun_1.width, &mlx->gun_1.height);
	mlx->gun_2.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/gun_2.xpm", &mlx->gun_2.width, &mlx->gun_2.height);
	mlx->gun_3.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/gun_3.xpm", &mlx->gun_3.width, &mlx->gun_3.height);
	mlx->gun_4.ptr = mlx_xpm_file_to_image
		(mlx->ptr, "asset/gun_4.xpm", &mlx->gun_4.width, &mlx->gun_4.height);
}

void	asset_init_address(t_mlx *mlx)
{
	mlx->no.addr = mlx_get_data_addr(mlx->no.ptr,
			&mlx->no.bpp, &mlx->no.size_line, &mlx->no.endian);
	mlx->so.addr = mlx_get_data_addr(mlx->so.ptr,
			&mlx->so.bpp, &mlx->so.size_line, &mlx->so.endian);
	mlx->we.addr = mlx_get_data_addr(mlx->we.ptr,
			&mlx->we.bpp, &mlx->we.size_line, &mlx->we.endian);
	mlx->ea.addr = mlx_get_data_addr(mlx->ea.ptr,
			&mlx->ea.bpp, &mlx->ea.size_line, &mlx->ea.endian);
	mlx->door.addr = mlx_get_data_addr(mlx->door.ptr,
			&mlx->door.bpp, &mlx->door.size_line, &mlx->door.endian);
	mlx->gun_0.addr = mlx_get_data_addr(mlx->gun_0.ptr,
			&mlx->gun_0.bpp, &mlx->gun_0.size_line, &mlx->gun_0.endian);
	mlx->gun_1.addr = mlx_get_data_addr(mlx->gun_1.ptr,
			&mlx->gun_1.bpp, &mlx->gun_1.size_line, &mlx->gun_1.endian);
	mlx->gun_2.addr = mlx_get_data_addr(mlx->gun_2.ptr,
			&mlx->gun_2.bpp, &mlx->gun_2.size_line, &mlx->gun_2.endian);
	mlx->gun_3.addr = mlx_get_data_addr(mlx->gun_3.ptr,
			&mlx->gun_3.bpp, &mlx->gun_3.size_line, &mlx->gun_3.endian);
	mlx->gun_4.addr = mlx_get_data_addr(mlx->gun_4.ptr,
			&mlx->gun_4.bpp, &mlx->gun_4.size_line, &mlx->gun_4.endian);
}

int	asset_open(char *filepath)
{
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		perror(filepath);
		return (1);
	}
	close(fd);
	return (0);
}

void	asset_destroy(t_mlx *mlx)
{
	if (mlx->no.ptr)
		mlx_destroy_image(mlx->ptr, mlx->no.ptr);
	if (mlx->so.ptr)
		mlx_destroy_image(mlx->ptr, mlx->so.ptr);
	if (mlx->we.ptr)
		mlx_destroy_image(mlx->ptr, mlx->we.ptr);
	if (mlx->ea.ptr)
		mlx_destroy_image(mlx->ptr, mlx->ea.ptr);
	if (mlx->door.ptr)
		mlx_destroy_image(mlx->ptr, mlx->door.ptr);
	if (mlx->gun_0.ptr)
		mlx_destroy_image(mlx->ptr, mlx->gun_0.ptr);
	if (mlx->gun_1.ptr)
		mlx_destroy_image(mlx->ptr, mlx->gun_1.ptr);
	if (mlx->gun_2.ptr)
		mlx_destroy_image(mlx->ptr, mlx->gun_2.ptr);
	if (mlx->gun_3.ptr)
		mlx_destroy_image(mlx->ptr, mlx->gun_3.ptr);
	if (mlx->gun_4.ptr)
		mlx_destroy_image(mlx->ptr, mlx->gun_4.ptr);
}
