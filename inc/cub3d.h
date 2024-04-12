/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:45:55 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/12 17:22:14 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# define ESC 65307

# define WIDTH 800
# define HEIGHT 600

typedef	struct s_cam
{
	double	posX;
	double	posY; //x and y start position
	double	dirX;
	double	dirY; //initial direction vector
	double	planeX;
	double	planeY; //the 2d raycaster version of camera plane
	double	time; //time of current frame
	double	oldTime; //time of previous frame
	double	cameraX; //x-coordinate in camera space
	double	rayDirX;
	double	rayDirY;
}	t_cam;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct s_asset
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	size_t	fl;
	size_t	ce;
}	t_asset;

typedef struct s_data
{
	t_list	*file;
	char	**map;
	size_t	height;
	size_t	lengh;
	t_asset	*asset;
	t_mlx	*mlx;
	t_cam	*cam;
}	t_data;

#endif