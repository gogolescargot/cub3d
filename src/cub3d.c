/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/12 17:20:27 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	file_open(t_data *data, const char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		error("Cannot open file");
		free_data(data);
		return (1);
	}
	return (0);
}

int	file_read(t_data *data, int fd)
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
			free_data(data);
			return (1);
		}
		ft_lstadd_back(&data->file, node);
	}
	return (0);
}

int	file_init(t_data *data, const char *file)
{
	int		fd;

	if (file_open(data, file, &fd))
		return (1);
	if (file_read(data, fd))
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

int	format_asset_color(char *str, size_t *rgb)
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

int	insert_asset_string(t_asset *asset, char *info, int i)
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

int	insert_asset_color(t_asset *asset, char *info, int i)
{
	if (i == 4)
	{
		if (format_asset_color(info, &asset->fl))
			return (1);
	}
	else
	{
		if (format_asset_color(info, &asset->ce))
			return (1);
	}
	return (0);
}

int	insert_asset(t_asset *asset, char *info, int i)
{
	if (i < 4 && insert_asset_string(asset, info, i))
		return (1);
	else if (i > 3 && insert_asset_color(asset, info, i))
		return (1);
	return (0);
}

int	map_asset(t_asset *asset, const char *str, int i)
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
	if (insert_asset(asset, info[1], i))
	{
		ft_arrayclear(info);
		ft_free(type);
		return (1);
	}
	ft_arrayclear(info);
	ft_free(type);
	return (0);
}

size_t	get_max_strlen(t_list *lst)
{
	t_list	*cur;
	size_t	max;
	size_t	len;

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

int	insert_string_array(t_data *data, char *str, size_t max_len, char **dst)
{
	size_t	len;

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

int	init_string_array(t_data *data, t_list *map)
{
	size_t	i;
	char	*tmp;

	i = 0;
	data->lengh = get_max_strlen(map);
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
		if (insert_string_array(data, map->content, data->lengh, &tmp))
			return (1);
		data->map[i] = tmp;
		i++;
		map = map->next;
	}
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
			if (map_asset(asset, cur->content, i))
			{
				free_data(data);
				return (1);
			}
			i++;
		}
		else if (!is_empty(cur->content))
		{
			init_string_array(data, cur);
			return (0);
		}
		cur = cur->next;
	}
	error("Missing map");
	free_data(data);
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

void	display_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s|\n", map[i]);
		i++;
	}
}

int	open_asset(t_data *data, char *filepath)
{
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		perror(filepath);
		free_data(data);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_asset(t_data *data, t_asset *asset)
{
	if (open_asset(data, asset->no))
		return (1);
	if (open_asset(data, asset->so))
		return (1);
	if (open_asset(data, asset->we))
		return (1);
	if (open_asset(data, asset->ea))
		return (1);
	return (0);
}

int	check_map_char(t_data *data)
{
	size_t	i;
	size_t	j;

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

bool	is_border(t_data *data, size_t i, size_t j)
{
	if (i == 0 || i == data->height - 1)
		return (true);
	if (j == 0 || j == data->lengh - 1)
		return (true);
	return (false);
}

int	dfs(t_data *data, char **str_map, size_t i, size_t j)
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

bool	is_coord(t_data *data, char **str_map, size_t *i, size_t *j)
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

int	dup_array(t_data *data, char **src, char ***dst)
{
	size_t	i;
	char	*tmp;

	i = 0;
	*dst = ft_calloc(data->height + 1, sizeof(char *));
	while (src[i])
	{
		tmp = ft_strdup(src[i]);
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

int	check_map_border(t_data *data)
{
	size_t	i;
	size_t	j;
	char	**dfs_str;

	if (dup_array(data, data->map, &dfs_str))
		return (1);
	while (is_coord(data, dfs_str, &i, &j))
	{
		if (dfs(data, dfs_str, i, j))
		{
			error("Map not surrounded by walls");
			free_data(data);
			ft_arrayclear(dfs_str);
			return (1);
		}
	}
	ft_arrayclear(dfs_str);
	return (0);
}

int	check_map_entities(t_data *data)
{
	size_t	spawn;
	size_t	i;
	size_t	j;

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

int	map_check(t_data *data)
{
	if (check_map_char(data))
		return (1);
	if (check_map_entities(data))
		return (1);
	if (check_map_border(data))
		return (1);
	return (0);
}

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
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	mlx_destroy_display(data->mlx->ptr);
	ft_free(data->mlx->ptr);
	free_data(data);
	exit(0);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		destroy(data);
	return (0);
}

int	window_init(t_data *data, t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		error("minilibX initialization failed");
		free_data(data);
		return (1);
	}
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "ggalon - cub3d");
	if (!mlx->win)
	{
		error("minilibX window failed");
		free_data(data);
		ft_free(mlx->ptr);
		return (1);
	}
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, &destroy, data);
	mlx_loop(mlx->ptr);
	return (0);
}

// int	draw(t_data *data, t_asset *asset, t_cam *cam)
// {
// 	size_t	x;

// 	while (true)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			cam->cameraX = 2 * x / WIDTH - 1;
// 			cam->rayDirX = cam->dirX + cam->planeX * cam->cameraX;
// 			cam->rayDirY = cam->dirY + cam->planeY * cam->cameraX;
// 		}
// 	}
// 	return (0);
// }

// int	get_coord(t_data *data)
// {
// 	data->map
// }

// int	camera_init(t_data *data, t_asset *asset, t_cam *cam)
// {
// 	double	posX;
// 	double	posY; //x and y start position
// 	double	dirX;
// 	double	dirY; //initial direction vector
// 	double	planeX;
// 	double	planeY; //the 2d raycaster version of camera plane
// 	double	time; //time of current frame
// 	double	oldTime; //time of previous frame
// 	double	cameraX; //x-coordinate in camera space
// 	double	rayDirX;
// 	double	rayDirY;
// }

int	main(int argc, const char *argv[])
{
	t_data	data;
	t_asset	asset;
	t_mlx	mlx;
	t_cam	cam;

	struct_init(&data, &asset, &mlx, &cam);
	if (args_check(argc, argv))
		return (1);
	if (file_init(&data, argv[1]))
		return (1);
	if (map_init(&data, &asset))
		return (1);
	if (map_check(&data))
		return (1);
	display_asset(&asset);
	display_map(data.map);
	if (window_init(&data, &mlx))
		return (1);
	// if (camera_init(&data, &asset, &cam))
	// 	return (1);
	// if (draw(&data, &asset, &cam))
	// 	return (1);
	free_data(&data);
	return (0);
}
