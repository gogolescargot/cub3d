/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:55:57 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/23 18:31:52 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	asset_init(t_data *data, t_asset *asset, t_mlx *mlx)
{
	int	tmp;

	if (asset_check(asset))
		destroy(data, 1);
	mlx->no.ptr = mlx_xpm_file_to_image(mlx->ptr, asset->no, &tmp, &tmp);
	mlx->so.ptr = mlx_xpm_file_to_image(mlx->ptr, asset->so, &tmp, &tmp);
	mlx->we.ptr = mlx_xpm_file_to_image(mlx->ptr, asset->we, &tmp, &tmp);
	mlx->ea.ptr = mlx_xpm_file_to_image(mlx->ptr, asset->ea, &tmp, &tmp);
	mlx->door.ptr = mlx_xpm_file_to_image(mlx->ptr, "asset/door.xpm", &tmp, &tmp);
	if (!mlx->no.ptr || !mlx->so.ptr || !mlx->we.ptr || !mlx->ea.ptr || !mlx->door.ptr)
	{
		error("Asset error");
		destroy(data, 1);
	}
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
	return (0);
}

int	asset_check(t_asset *asset)
{
	if (asset_open(asset->no))
		return (1);
	if (asset_open(asset->so))
		return (1);
	if (asset_open(asset->we))
		return (1);
	if (asset_open(asset->ea))
		return (1);
	if (asset_open("asset/door.xpm"))
		return (1);
	return (0);
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
}
