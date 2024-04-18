/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:01:36 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 04:06:56 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	absolute(double nbr)
{
	if (nbr < 0)
		return (nbr *= -1);
	return (nbr);
}

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	free_data(t_data *data)
{
	ft_lstclear(&data->file, ft_free);
	ft_arrayclear(data->map);
	if (data->asset)
	{
		ft_free(data->asset->no);
		ft_free(data->asset->so);
		ft_free(data->asset->we);
		ft_free(data->asset->ea);
	}
}

int	dfs(t_data *data, char **str_map, int i, int j)
{
	if (is_border(data, i, j) && !ft_strchr("1", str_map[i][j]))
		return (1);
	if (ft_strchr(" ", str_map[i][j]))
		return (1);
	if (str_map[i][j] == '1')
		return (0);
	if (ft_strchr("0NSWE", str_map[i][j]))
	{
		str_map[i][j] = 'x';
		if (dfs(data, str_map, i - 1, j)
			|| dfs(data, str_map, i + 1, j)
			|| dfs(data, str_map, i, j - 1)
			|| dfs(data, str_map, i, j + 1))
			return (1);
	}
	return (0);
}

void	move_point(t_cam *cam, t_point *tmp, t_vector *move_dir, int keycode)
{
	if (keycode == W)
	{
		tmp->x = cam->pos.x + move_dir->x;
		tmp->y = cam->pos.y + move_dir->y;
	}
	else if (keycode == A)
	{
		tmp->x = cam->pos.x + move_dir->y;
		tmp->y = cam->pos.y - move_dir->x;
	}
	else if (keycode == S)
	{
		tmp->x = cam->pos.x - move_dir->x;
		tmp->y = cam->pos.y - move_dir->y;
	}
	else if (keycode == D)
	{
		tmp->x = cam->pos.x - move_dir->y;
		tmp->y = cam->pos.y + move_dir->x;
	}
}
