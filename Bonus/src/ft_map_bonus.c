/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:01:17 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/02 17:06:24 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	rest_image(mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			mlx_put_pixel(image, x, y, 0);
			y++;
		}
		x++;
	}
}

void	set_color_pixel(t_data *data, t_pos *map, t_pos *p1, int sig)
{
	int	color;

	color = ft_color(data->element.floor_color.red, \
					data->element.floor_color.green, \
					data->element.floor_color.blue, 100);
	if (map->x >= 0 && map->x < data->map->width
		&& map->y >= 0 && map->y < data->map->height)
	{
		if (data->map->arr_map[(int)map->y][(int)map->x] == '1')
			mlx_put_pixel(data->map->img_map, p1->x, p1->y, 0x808080FF);
		else if (data->map->arr_map[(int)map->y][(int)map->x] == 'D')
			mlx_put_pixel(data->map->img_map, p1->x, p1->y, 0x808FA0FF);
		else
			mlx_put_pixel(data->map->img_map, p1->x, p1->y, color);
	}
	else if (sig == 1 || map->x >= data->map->width
		|| map->y >= data->map->height)
		mlx_put_pixel(data->map->img_map, p1->x, p1->y, color);
}

void	ft_scale_mp(t_data *data, t_pos *p1)
{
	float		scale_factor;

	scale_factor = (float)TILE_SIZE / TILE_SIZE_MAP;
	p1->x = (int)(data->player->x / (scale_factor)) - TILE_MAP / 2;
	p1->y = (int)(data->player->y / scale_factor) - TILE_MAP / 2;
}

void	ft_minimap(t_data *data)
{
	int			i;
	int			j;
	t_pos		first;
	t_pos		map;
	int			sig;

	sig = 0;
	i = 0;
	j = 0;
	ft_scale_mp(data, &first);
	if (first.x <= 0 || first.y <= 0)
		sig = 1;
	while (i < TILE_MAP)
	{
		j = 0;
		while (j < TILE_MAP)
		{
			map.x = (i + first.x) / TILE_SIZE_MAP;
			map.y = (j + first.y) / TILE_SIZE_MAP;
			set_color_pixel(data, &map, &(t_pos){i, j}, sig);
			j++;
		}
		i++;
	}
	ft_border_map(data);
}

void	ft_border_map(t_data *data)
{
	int		x;
	int		y;
	float	mx;
	float	my;
	int		r2;

	r2 = (TILE_MAP / 2) - 6;
	x = -(TILE_MAP / 2);
	y = -(TILE_MAP / 2);
	while (x < (TILE_MAP / 2))
	{
		y = -(TILE_MAP / 2);
		while (y < (TILE_MAP / 2))
		{
			mx = (TILE_MAP / 2) + x;
			my = (TILE_MAP / 2) + y;
			if (pow(x, 2) + pow(y, 2) < pow((TILE_MAP / 2), 2)
				&& pow(x, 2) + pow(y, 2) >= pow(r2, 2))
				mlx_put_pixel(data->map->img_map, mx, my, 0x000000FF);
			if (pow(x, 2) + pow(y, 2) >= pow((TILE_MAP / 2), 2))
				mlx_put_pixel(data->map->img_map, mx, my, 0);
			y++;
		}
		x++;
	}
}
