/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_and_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:46:39 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/04 22:39:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_AND_STRUCT_H
# define CONST_AND_STRUCT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../src/libft/libft.h"
# include "../src/get_next_line/get_next_line.h"
# include "MLX42.h"
# define TILE_SIZE 1024
# define NBR_RAYS 1500
# define WINDOW_WHIDTH 1500 
# define WINDOW_HEIGHT 900
# define TILE_MAP 250

typedef struct s_player
{
	float		x;
	float		y;
	int			radius;
	char		isfacing;
	int			view_player;
	int			turndir;
	int			walkdirection;
	float		rotangle;
	float		movespeed;
	float		rotspeed;
	mlx_image_t	*img_player;
}	t_player;

typedef struct s_texture
{
	mlx_texture_t	*wall_tex_n;
	mlx_texture_t	*wall_tex_s;
	mlx_texture_t	*wall_tex_w;
	mlx_texture_t	*wall_tex_e;
}	t_texture;

typedef struct s_map
{
	int			width;
	int			height;
	char		**arr_map;
	mlx_image_t	*img_map;
}	t_map;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_element
{
	char	*color_path;
	t_color	floor_color;
	t_color	ceiling_color;
}				t_element;

typedef struct s_ray
{
	float	dx;
	float	dy;
	float	x_intercept;
	float	y_intercept;
	bool	ray_is_up;
	bool	ray_is_down;
	bool	ray_is_left;
	bool	ray_is_right;
	float	ray_angle;
}				t_ray;

typedef struct s_number
{
	int		n;
	int 	s;
	int		e;
	int		w;
} t_number;

typedef struct s_data
{
	int			j;
	int			i;
	int			size;
	int			fd;
	int			n;
	char		*string;
	float		distance;
	float		rayangle;
	t_texture	*texture;
	t_list		*texturel;
	t_list		*list;
	t_element	element;
	mlx_t		*mlx;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	t_number	number;
}				t_data;

typedef struct s_position
{
	float	x;
	float	y;
}				t_pos;

typedef struct s_con_var
{
	uint8_t		*pixels;
	uint32_t	i;
	uint8_t		a;
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
}				t_con_var;

#endif