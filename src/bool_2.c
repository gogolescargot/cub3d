/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:07:17 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/26 00:21:02 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_door(t_cam *cam, int x, int y)
{
	if ((int)cam->pos.x - x <= 1 && (int)cam->pos.x - x >= -1
		&& (int)cam->pos.y - y <= 1 && (int)cam->pos.y - y >= -1)
		return (true);
	return (false);
}
