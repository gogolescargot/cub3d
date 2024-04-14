/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:45:55 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/14 05:53:23 by ggalon           ###   ########.fr       */
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
# include <math.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define L_ARR 65361
# define R_ARR 65363

# define WIDTH 800
# define HEIGHT 600

# define PI 3.14159265359

# define ROTATE_SPEED 0.31416
# define MOVE_SPEED 0.1

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_cam
{
	t_point		pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray;
	double		camera_x;
}	t_cam;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

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
	int		fl;
	int		ce;
}	t_asset;

typedef struct s_data
{
	t_list	*file;
	char	**map;
	int		height;
	int		lengh;
	t_asset	*asset;
	t_mlx	*mlx;
	t_cam	*cam;
}	t_data;

#endif