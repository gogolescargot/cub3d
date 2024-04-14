/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/14 06:12:55 by ggalon           ###   ########.fr       */
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

int	atoi_color(char	**color, int *r, int *g, int *b)
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

int	format_asset_color(char *str, int *rgb)
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
	if (atoi_color(color, &r, &g, &b))
		return (1);
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

int	get_max_strlen(t_list *lst)
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

int	insert_string_array(t_data *data, char *str, int max_len, char **dst)
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

int	init_string_array(t_data *data, t_list *map)
{
	int		i;
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
			return (init_string_array(data, cur));
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
	int	i;

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

bool	is_border(t_data *data, int i, int j)
{
	if (i == 0 || i == data->height - 1)
		return (true);
	if (j == 0 || j == data->lengh - 1)
		return (true);
	return (false);
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

int	dup_map(t_data *data, char ***dst)
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

int	check_map_border(t_data *data)
{
	int		i;
	int		j;
	char	**map_dfs;

	if (dup_map(data, &map_dfs))
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

int	check_map_entities(t_data *data)
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

bool	is_outside(t_data *data, t_point *point)
{
	if (point->x <= 1.01 || point->x >= data->lengh - 1.01)
		return (true);
	if (point->y <= 1.01 || point->y >= data->height - 1.01)
		return (true);
	return (false);
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

void	move(t_data *data, t_cam *cam, int keycode)
{
	t_vector	move_dir;
	t_point		tmp;

	move_dir.x = cam->dir.x * MOVE_SPEED;
	move_dir.y = cam->dir.y * MOVE_SPEED;
	move_point(cam, &tmp, &move_dir, keycode);
	if (!is_outside(data, &tmp))
	{
		cam->pos.x = tmp.x;
		cam->pos.y = tmp.y;
	}
}

void	camera(t_cam *cam, int keycode)
{
	double	rotate_speed;
	double	old_plane_x;
	double	old_dir_x;

	rotate_speed = ROTATE_SPEED;
	if (keycode == L_ARR)
		rotate_speed *= -1;
	old_dir_x = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(rotate_speed)
		- cam->dir.y * sin(rotate_speed);
	cam->dir.y = old_dir_x * sin(rotate_speed)
		+ cam->dir.y * cos(rotate_speed);
	old_plane_x = cam->plane.x;
	cam->plane.x = cam->plane.x * cos(rotate_speed)
		- cam->plane.y * sin(rotate_speed);
	cam->plane.y = old_plane_x * sin(rotate_speed)
		+ cam->plane.y * cos(rotate_speed);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		destroy(data);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		move(data, data->cam, keycode);
	else if (keycode == L_ARR || keycode == R_ARR)
		camera(data->cam, keycode);
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
	return (0);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_line(t_img *img, int x, int drawStart, int drawEnd, int color)
{
	int	y;

	y = drawStart;
	while (y <= drawEnd)
	{
		img_pixel_put(img, x, y, color);
		y++;
	}
}

void	draw_color(t_asset *asset, t_img *img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < HEIGHT - 1)
	{
		if (y < HEIGHT / 2)
			color = asset->ce;
		else
			color = asset->fl;
		while (x < WIDTH - 1)
		{
			img_pixel_put(img, x, y, color);
			x++;
		}
		y++;
		x = 0;
	}
}

double	absolute(double nbr)
{
	if (nbr < 0)
		return (nbr *= -1);
	return (nbr);
}

int	draw(t_data *data)
{
	int		x;
	t_img	img;
	t_cam	*cam;
	t_mlx	*mlx;

	mlx = data->mlx;
	cam = data->cam;
	x = 0;
	img.ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.size_line, &img.endian);
	draw_color(data->asset, &img);
	while (x < WIDTH)
	{
		//calculate ray position and direction
		cam->camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		cam->ray.x = cam->dir.x + cam->plane.x * cam->camera_x;
		cam->ray.y = cam->dir.y + cam->plane.y * cam->camera_x;
		//which box of the map we're in
		int mapX = (int)cam->pos.x;
		int mapY = (int)cam->pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (cam->ray.y * cam->ray.y) / (cam->ray.x * cam->ray.x))
		//deltaDistY = sqrt(1 + (cam->ray.x * cam->ray.x) / (cam->ray.y * cam->ray.y))
		//which can be simplified to abs(|rayDir| / cam->ray.x) and abs(|rayDir| / cam->ray.y)
		//where |rayDir| is the length of the vector (cam->ray.x, cam->ray.y). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = absolute(1 / cam->ray.x);
		double deltaDistY = absolute(1 / cam->ray.y);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (cam->ray.x < 0)
		{
			stepX = -1;
			sideDistX = (cam->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cam->pos.x) * deltaDistX;
		}
		if (cam->ray.y < 0)
		{
			stepY = -1;
			sideDistY = (cam->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cam->pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[mapY][mapX] == '1')
				hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / cam->ray.x for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int	color;
		color = 0xFFFFFF;
		//give x and y sides different brightness
		if (side == 1)
			color = 0x888888;

		//draw the pixels of the stripe as a vertical line
		draw_line(&img, x, drawStart, drawEnd, color);
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, img.ptr);
	return (0);
}

void	get_coord(t_data *data, t_cam *cam)
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

void	get_dir(t_data *data, t_cam *cam)
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

void	get_plane(t_data *data, t_cam *cam)
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

void	camera_init(t_data *data, t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	get_coord(data, cam);
	get_dir(data, cam);
	get_plane(data, cam);
}

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
	camera_init(&data, &cam);
	display_asset(&asset);
	display_map(data.map);
	if (window_init(&data, &mlx))
		return (1);
	mlx_loop_hook(mlx.ptr, &draw, &data);
	mlx_loop(mlx.ptr);
	free_data(&data);
	return (0);
}
