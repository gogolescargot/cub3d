/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/04 12:32:07 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	free_data(t_data *data, t_asset *asset)
{
	ft_lstclear(&data->file, ft_free);
	// ft_lstclear(&data->map, ft_free);
	if (asset)
	{
		ft_free(asset->no);
		ft_free(asset->so);
		ft_free(asset->we);
		ft_free(asset->ea);
	}
}

int	file_open(const char *file, int *fd, t_data *data)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		error("Cannot open file");
		free_data(data, NULL);
		return (1);
	}
	return (0);
}

int	file_read(int fd, t_data *data)
{
	t_list	*node;
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		node = ft_lstnew(line);
		if (!node)
		{
			error("Malloc error");
			free(line);
			free_data(data, NULL);
			return (1);
		}
		ft_lstadd_back(&data->file, node);
	}
	return (0);
}

int	file_init(const char *file, t_data *data)
{
	int		fd;

	if (file_open(file, &fd, data))
		return (1);
	if (file_read(fd, data))
		return (1);
	close(fd);
	return (0);
}

bool	is_empty(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str)
		return (false);
	return (true);
}

int	init_type(char ***type)
{
	*type = malloc(sizeof(char *) * 6);
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

int	format_asset_number(char *str, size_t *rgb)
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
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_arrayclear(color);
		error("Out of range color");
		return (1);
	}
	*rgb = (r << 16) + (g << 8) + b;
	ft_arrayclear(color);
	return (0);
}

int	insert_asset_string(char *info, t_asset *asset, int i)
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

int	insert_asset_number(char *info, t_asset *asset, int i)
{
	if (i == 4)
	{
		if (format_asset_number(info, &asset->fl))
			return (1);
	}
	else
	{
		if (format_asset_number(info, &asset->ce))
			return (1);
	}
	return (0);
}

int	insert_asset(char *info, t_asset *asset, int i)
{
	if (i < 4 && insert_asset_string(info, asset, i))
		return (1);
	else if (i > 3 && insert_asset_number(info, asset, i))
		return (1);
	return (0);
}

int	map_asset(const char *str, t_asset *asset, int i)
{
	char	**type;
	char	**info;

	if (init_type(&type))
		return (1);
	info = ft_split(str, ' ');
	if (!info)
	{
		error("Malloc error");
		return (1);
	}
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
	if (insert_asset(info[1], asset, i))
	{
		ft_arrayclear(info);
		ft_free(type);
		return (1);
	}
	ft_arrayclear(info);
	ft_free(type);
	return (0);
}

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
			if (map_asset(cur->content, asset, i))
			{
				free_data(data, asset);
				return (1);
			}
			i++;
		}
		else if (!is_empty(cur->content))
		{
			data->map = cur;
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

bool	map_extension(const char *filename)
{
	const char	*dot;

	dot = NULL;
	if (ft_strlen(filename) < 5)
		return (false);
	while (*filename)
	{
		if (*filename == '.')
			dot = filename;
		filename++;
	}
	if (!dot || ft_strncmp(dot, ".cub", 5) != 0)
		return (false);
	return (true);
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
	if (!map_extension(argv[1]))
	{
		error("Wrong file extension");
		return (1);
	}
	return (0);
}

void	display_asset(t_asset *asset)
{
	ft_printf("NO: %s\n", asset->no);
	ft_printf("SO: %s\n", asset->so);
	ft_printf("WE: %s\n", asset->we);
	ft_printf("EA: %s\n", asset->ea);
	ft_printf("F: %d\n", asset->fl);
	ft_printf("C: %d\n", asset->ce);
}

void	display_map(t_data *data)
{
	while (data->map)
	{
		ft_printf("%s\n", data->map->content);
		data->map = data->map->next;
	}
}

void	init_struct(t_data *data, t_asset *asset)
{
	data->file = NULL;
	data->map = NULL;
	asset->no = NULL;
	asset->so = NULL;
	asset->we = NULL;
	asset->ea = NULL;
}

int	main(int argc, const char *argv[])
{
	t_data	data;
	t_asset	asset;

	init_struct(&data, &asset);
	if (args_check(argc, argv))
		return (1);
	if (file_init(argv[1], &data))
		return (1);
	if (map_init(&data, &asset))
		return (1);
	display_asset(&asset);
	display_map(&data);
	free_data(&data, &asset);
	return (0);
}

/*
	while (data->map)
	{
	ft_printf("%s", data->map->content);
	data->map = data->map->next;
	}
*/