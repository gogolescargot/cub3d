/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:13:39 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 00:22:06 by ggalon           ###   ########.fr       */
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
	mlx->door.ptr = NULL;
	mlx->gun_0.ptr = NULL;
	mlx->gun_1.ptr = NULL;
	mlx->gun_2.ptr = NULL;
	mlx->gun_3.ptr = NULL;
	mlx->gun_4.ptr = NULL;
	cam->door.x = -1;
	cam->door.y = -1;
	cam->door_crossed = false;
	cam->shot = false;
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

void	door(t_data *data, t_cam *cam)
{
	if (cam->door.x != -1 && cam->door.y != -1)
	{
		if (data->map[cam->door.y][cam->door.x] == 'C')
			data->map[cam->door.y][cam->door.x] = 'O';
		else
			data->map[cam->door.y][cam->door.x] = 'C';
	}
}

void	door_check(t_data *data, t_draw *draw, t_cam *cam)
{
	if (!is_outside(data, draw->map.x, draw->map.y)
		&& ft_strchr("OC", data->map[draw->map.y][draw->map.x]))
	{
		if (draw->side == WEST || draw->side == EAST)
			draw->side = DOOR_X;
		else
			draw->side = DOOR_Y;
	}
	if (draw->screen.x != WIDTH / 2)
		return ;
	if (!is_outside(data, draw->map.x, draw->map.y)
		&& ft_strchr("OC", data->map[draw->map.y][draw->map.x])
		&& is_door(cam, draw->map.x, draw->map.y))
	{
		cam->door_crossed = true;
		cam->door.x = draw->map.x;
		cam->door.y = draw->map.y;
	}
	else if (!cam->door_crossed)
	{
		cam->door.x = -1;
		cam->door.y = -1;
	}
}
