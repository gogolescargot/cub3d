/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:38 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/29 18:03:12 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	asset_check_size(t_data *data, t_mlx *mlx)
{
	bool	trigger;

	trigger = false;
	asset_check_size_utils(mlx, &trigger);
	if (trigger)
	{
		error("Wrong asset size");
		destroy(data, 1);
	}
}

void	asset_check_size_utils(t_mlx *mlx, bool *trigger)
{
	if (mlx->no.width != WIDTH_WALL || mlx->no.height != HEIGHT_WALL)
		*trigger = true;
	else if (mlx->so.width != WIDTH_WALL || mlx->so.height != HEIGHT_WALL)
		*trigger = true;
	else if (mlx->we.width != WIDTH_WALL || mlx->we.height != HEIGHT_WALL)
		*trigger = true;
	else if (mlx->ea.width != WIDTH_WALL || mlx->ea.height != HEIGHT_WALL)
		*trigger = true;
	else if (mlx->door.width != WIDTH_WALL || mlx->door.height != HEIGHT_WALL)
		*trigger = true;
	else if (mlx->gun_0.width != WIDTH_GUN || mlx->gun_0.height != HEIGHT_GUN)
		*trigger = true;
	else if (mlx->gun_1.width != WIDTH_GUN || mlx->gun_1.height != HEIGHT_GUN)
		*trigger = true;
	else if (mlx->gun_2.width != WIDTH_GUN || mlx->gun_2.height != HEIGHT_GUN)
		*trigger = true;
	else if (mlx->gun_3.width != WIDTH_GUN || mlx->gun_3.height != HEIGHT_GUN)
		*trigger = true;
	else if (mlx->gun_4.width != WIDTH_GUN || mlx->gun_4.height != HEIGHT_GUN)
		*trigger = true;
}

int	asset_check_open(t_asset *asset)
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
	if (asset_open("asset/gun_0.xpm"))
		return (1);
	if (asset_open("asset/gun_1.xpm"))
		return (1);
	if (asset_open("asset/gun_2.xpm"))
		return (1);
	if (asset_open("asset/gun_3.xpm"))
		return (1);
	if (asset_open("asset/gun_4.xpm"))
		return (1);
	return (0);
}
