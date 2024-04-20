/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:09:20 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/20 09:55:06 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	asset_insert(t_asset *asset, char *info, int i)
{
	if (i < 4 && asset_insert_string(asset, info, i))
		return (1);
	else if (i > 3 && asset_insert_color(asset, info, i))
		return (1);
	return (0);
}

int	asset_insert_string(t_asset *asset, char *info, int i)
{
	char	*str;

	if (i < 4)
	{
		str = ft_strdup(info);
		if (!str)
		{
			error("Malloc error");
			return (1);
		}
	}
	if (i == 0)
		asset->no = str;
	else if (i == 1)
		asset->so = str;
	else if (i == 2)
		asset->we = str;
	else if (i == 3)
		asset->ea = str;
	return (0);
}

int	asset_insert_color(t_asset *asset, char *info, int i)
{
	if (i == 4)
	{
		if (asset_format_color(info, &asset->fl))
			return (1);
	}
	else
	{
		if (asset_format_color(info, &asset->ce))
			return (1);
	}
	return (0);
}

int	asset_format_color(char *str, int *rgb)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	color = ft_split(str, ',');
	if (!color)
	{
		error("Malloc error");
		return (1);
	}
	if (!color[0] || !color[1] || !color[2] || color[3])
	{
		ft_arrayclear(color);
		error("Wrong color format");
		return (1);
	}
	if (asset_atoi(color, &r, &g, &b))
		return (1);
	*rgb = (r << 16) + (g << 8) + b;
	ft_arrayclear(color);
	return (0);
}

int	asset_atoi(char	**color, int *r, int *g, int *b)
{
	*r = ft_atoi(color[0]);
	*g = ft_atoi(color[1]);
	*b = ft_atoi(color[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		ft_arrayclear(color);
		error("Out of range color");
		return (1);
	}
	return (0);
}
