/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/02 18:16:51 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

int	file_open(const char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		error("Cannot open file");
		return (1);
	}
	return (0);
}

int	file_read(int fd, t_list **map)
{
	t_list	*node;
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		node = ft_lstnew(line);
		if (!node)
		{
			error("Malloc error");
			ft_lstclear(map, ft_free);
			return (1);
		}
		ft_lstadd_back(map, node);
	}
	return (0);
}

int	file_init(const char *file, t_list **map)
{
	int		fd;

	*map = NULL;
	if (file_open(file, &fd))
		return (1);
	if (file_read(fd, map))
		return (1);
	close(fd);
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc != 2)
		return (error("Wrong parameters number"));
	if (file_init(argv[1], &data->map))
		return (1);
	ft_lstclear(&data->map, ft_free);
	free(data);
	return (0);
}

/*
	while (data->map)
	{
	ft_printf("%s", data->map->content);
	data->map = data->map->next;
	}
*/