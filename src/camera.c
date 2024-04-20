/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:44:30 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/20 09:55:06 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera_init(t_data *data, t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	camera_coord(data, cam);
	camera_dir(data, cam);
	camera_plane(data, cam);
}

void	camera_coord(t_data *data, t_cam *cam)
{
	while (cam->pos.y < data->height)
	{
		while (cam->pos.x < data->lengh)
		{
			if (ft_strchr("NSWE", data->map[(int)cam->pos.y][(int)cam->pos.x]))
			{
				cam->pos.x += 0.5;
				cam->pos.y += 0.5;
				return ;
			}
			cam->pos.x++;
		}
		cam->pos.y++;
		cam->pos.x = 0;
	}
}

void	camera_dir(t_data *data, t_cam *cam)
{
	char	c;

	c = data->map[(int)cam->pos.y][(int)cam->pos.x];
	if (c == 'N')
	{
		cam->dir.x = 0;
		cam->dir.y = -1;
	}
	else if (c == 'S')
	{
		cam->dir.x = 0;
		cam->dir.y = 1;
	}
	else if (c == 'W')
	{
		cam->dir.x = -1;
		cam->dir.y = 0;
	}
	else if (c == 'E')
	{
		cam->dir.x = 1;
		cam->dir.y = 0;
	}
}

void	camera_plane(t_data *data, t_cam *cam)
{
	char	c;

	c = data->map[(int)cam->pos.y][(int)cam->pos.x];
	if (c == 'N')
	{
		cam->plane.x = 0.80;
		cam->plane.y = 0;
	}
	else if (c == 'S')
	{
		cam->plane.x = -0.80;
		cam->plane.y = 0;
	}
	else if (c == 'W')
	{
		cam->plane.x = 0;
		cam->plane.y = -0.80;
	}
	else if (c == 'E')
	{
		cam->plane.x = 0;
		cam->plane.y = 0.80;
	}
}
