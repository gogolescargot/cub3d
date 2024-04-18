/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:58:56 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 03:59:02 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check(t_data *data)
{
	if (map_check_char(data))
		return (1);
	if (map_check_entities(data))
		return (1);
	if (map_check_border(data))
		return (1);
	return (0);
}

int	map_check_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (!ft_strchr("01NSWE ", data->map[i][j]))
			{
				error("Forbidden character");
				free_data(data);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	map_check_entities(t_data *data)
{
	int	spawn;
	int	i;
	int	j;

	spawn = 0;
	i = 0;
	j = 0;
	while (spawn < 2 && data->map[i])
	{
		while (spawn < 2 && data->map[i][j])
		{
			if (ft_strchr("NSWE", data->map[i][j]))
				spawn++;
			j++;
		}
		j = 0;
		i++;
	}
	if (spawn != 1)
	{
		error("Wrong spawn location number");
		free_data(data);
		return (1);
	}
	return (0);
}

int	map_check_border(t_data *data)
{
	int		i;
	int		j;
	char	**map_dfs;

	if (map_duplicate(data, &map_dfs))
		return (1);
	while (is_coord(data, map_dfs, &i, &j))
	{
		if (dfs(data, map_dfs, i, j))
		{
			error("Map not surrounded by walls");
			free_data(data);
			ft_arrayclear(map_dfs);
			return (1);
		}
	}
	ft_arrayclear(map_dfs);
	return (0);
}

int	map_check_extension(const char *filename)
{
	const char	*dot;

	dot = NULL;
	if (ft_strlen(filename) < 5)
		return (1);
	while (*filename)
	{
		if (*filename == '.')
			dot = filename;
		filename++;
	}
	if (!dot || ft_strncmp(dot, ".cub", 5) != 0)
		return (1);
	return (0);
}
