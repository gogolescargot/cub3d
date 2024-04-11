/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:45:55 by ggalon            #+#    #+#             */
/*   Updated: 2024/04/09 20:30:07 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>

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
	t_list	*map;
	t_asset	*asset;
	t_mlx	*mlx;
}	t_data;

#endif