/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:13:39 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/20 09:55:06 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_data *data, t_asset *asset, t_mlx	*mlx, t_cam *cam)
{
	data->file = NULL;
	data->map = NULL;
	data->asset = asset;
	data->mlx = mlx;
	data->cam = cam;
	asset->no = NULL;
	asset->so = NULL;
	asset->we = NULL;
	asset->ea = NULL;
	mlx->no.ptr = NULL;
	mlx->so.ptr = NULL;
	mlx->we.ptr = NULL;
	mlx->ea.ptr = NULL;
}

int	args_check(int argc, const char **argv)
{
	if (argc != 2)
	{
		error("Wrong parameters number");
		return (1);
	}
	if (!argv[1])
	{
		error("Empty filepath");
		return (1);
	}
	if (map_check_extension(argv[1]))
	{
		error("Wrong file extension");
		return (1);
	}
	return (0);
}

int	type_init(char ***type)
{
	*type = ft_calloc(6, sizeof(char *));
	if (!*type)
	{
		error("Malloc error");
		return (1);
	}
	(*type)[0] = "NO";
	(*type)[1] = "SO";
	(*type)[2] = "WE";
	(*type)[3] = "EA";
	(*type)[4] = "F";
	(*type)[5] = "C";
	return (0);
}
