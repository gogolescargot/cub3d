/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 03:57:18 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 03:58:11 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_lengh(t_list *lst)
{
	t_list	*cur;
	int		max;
	int		len;

	max = 0;
	cur = lst;
	while (cur)
	{
		len = ft_strlen(cur->content);
		if (len > max)
			max = len;
		cur = cur->next;
	}
	return (max);
}

int	map_duplicate(t_data *data, char ***dst)
{
	int		i;
	char	*tmp;

	i = 0;
	*dst = ft_calloc(data->height + 1, sizeof(char *));
	while (data->map[i])
	{
		tmp = ft_strdup(data->map[i]);
		if (!tmp)
		{
			error("Malloc error");
			free_data(data);
			return (1);
		}
		(*dst)[i] = tmp;
		i++;
	}
	return (0);
}

int	map_string_init(t_data *data, t_list *map)
{
	int		i;
	char	*tmp;

	i = 0;
	data->lengh = map_lengh(map);
	data->height = ft_lstsize(map);
	data->map = ft_calloc(data->height + 1, sizeof(char *));
	if (!data->map)
	{
		error("Malloc error");
		free_data(data);
		return (1);
	}
	while (map)
	{
		if (map_string_insert(data, map->content, data->lengh, &tmp))
			return (1);
		data->map[i] = tmp;
		i++;
		map = map->next;
	}
	return (0);
}

int	map_string_insert(t_data *data, char *str, int max_len, char **dst)
{
	int	len;

	len = ft_strlen(str);
	*dst = ft_calloc(max_len + 1, sizeof(char));
	if (!*dst)
	{
		error("Malloc error");
		free_data(data);
		return (1);
	}
	ft_strlcat(*dst, str, max_len + 1);
	ft_memset(*dst + len, ' ', max_len - len);
	return (0);
}
