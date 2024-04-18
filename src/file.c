/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:04:36 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/18 02:22:13 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
