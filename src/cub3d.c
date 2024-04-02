/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:48 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/02 18:46:09 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	free_data(t_data **data)
{
	ft_lstclear(&(*data)->map, ft_free);
	free(*data);
}

int	file_open(const char *file, int *fd, t_data *data)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		error("Cannot open file");
		free_data(&data);
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
		node = ft_lstnew(line);
		if (!node)
		{
			error("Malloc error");
			free(line);
			free_data(&data);
			return (1);
		}
		ft_lstadd_back(&data->map, node);
	}
	return (0);
}

int	file_init(const char *file, t_data *data)
{
	int		fd;

	data->map = NULL;
	if (file_open(file, &fd, data))
		return (1);
	if (file_read(fd, data))
		return (1);
	close(fd);
	return (0);
}

int	args_check(int argc, t_data *data)
{
	if (argc != 2)
	{
		error("Wrong parameters number");
		free_data(&data);
		return (1);
	}
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (args_check(argc, data))
		return (1);
	if (file_init(argv[1], data))
		return (1);
	free_data(&data);
	return (0);
}

/*
	while (data->map)
	{
	ft_printf("%s", data->map->content);
	data->map = data->map->next;
	}
*/