/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:05:56 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 03:59:12 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_init(t_data *data, t_asset *asset)
{
	t_list	*cur;
	int		i;

	cur = data->file;
	i = 0;
	while (cur)
	{
		if (i < 6 && !is_empty(cur->content))
		{
			if (map_asset(asset, cur->content, i))
			{
				free_data(data);
				return (1);
			}
			i++;
		}
		else if (!is_empty(cur->content))
			return (map_string_init(data, cur));
		cur = cur->next;
	}
	error("Missing map");
	free_data(data);
	return (1);
}

int	map_asset(t_asset *asset, const char *str, int i)
{
	char	**type;
	char	**info;

	if (type_init(&type))
		return (1);
	info = ft_split(str, ' ');
	if (!info)
	{
		error("Malloc error");
		return (1);
	}
	if (map_check_asset(asset, i, info, type))
		return (1);
	ft_arrayclear(info);
	ft_free(type);
	return (0);
}

int	map_check_asset(t_asset *asset, int i, char **info, char **type)
{
	if (!info[0] || !info[1] || info[2])
	{
		error("Incorrect argument number");
		ft_arrayclear(info);
		ft_free(type);
		return (1);
	}
	if (ft_strncmp(info[0], type[i], 3) != 0)
	{
		error("Incorrect argument order");
		ft_arrayclear(info);
		ft_free(type);
		return (1);
	}
	if (asset_insert(asset, info[1], i))
	{
		ft_arrayclear(info);
		ft_free(type);
		return (1);
	}
	return (0);
}
