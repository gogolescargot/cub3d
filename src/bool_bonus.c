/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:07:17 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/20 09:15:00 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	is_empty(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str)
		return (false);
	return (true);
}

bool	is_border(t_data *data, int i, int j)
{
	if (i == 0 || i == data->height - 1)
		return (true);
	if (j == 0 || j == data->lengh - 1)
		return (true);
	return (false);
}

bool	is_coord(t_data *data, char **str_map, int *i, int *j)
{
	*i = 0;
	*j = 0;
	while (str_map[*i])
	{
		while (str_map[*i][*j])
		{
			if (ft_strchr("0NSWE", str_map[*i][*j]))
				return (true);
			(*j)++;
		}
		if (*i == data->height && *j == data->lengh)
			return (false);
		(*j) = 0;
		(*i)++;
	}
	return (false);
}

bool	is_valid(t_data *data, t_point *point)
{
	if (point->x <= 1.01 || point->x >= data->lengh - 1.01)
		return (false);
	if (point->y <= 1.01 || point->y >= data->height - 1.01)
		return (false);
	if (data->map[(int)(point->y + 0.01)][(int)(point->x + 0.01)] == '1' ||
		data->map[(int)(point->y - 0.01)][(int)(point->x + 0.01)] == '1' ||
		data->map[(int)(point->y + 0.01)][(int)(point->x - 0.01)] == '1' ||
		data->map[(int)(point->y - 0.01)][(int)(point->x - 0.01)] == '1')
		return (false);
	return (true);
}
