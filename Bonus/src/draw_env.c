/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:14:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 00:16:50 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_circle(t_data *data, int color)
{
	int		x;
	int		y;
	float	px;
	float	py;
	int		r;

	r = data->player->radius;
	x = -r;
	while (x < r)
	{
		y = -r;
		while (y < r)
		{
			if (pow(x, 2) + pow(y, 2) < pow(r, 2))
			{
				px = TILE_MAP / 2 + x;
				py = TILE_MAP / 2 + y;
				if (px < TILE_MAP && py < TILE_MAP && px >= 0 && py >= 0)
					mlx_put_pixel(data->map->img_map, px, py, color);
			}
			y++;
		}
		x++;
	}
}

void	draw_line(t_data *data, t_pos *p1, t_pos *p2, int color)
{
	t_pos		p_increment;
	int			steps;
	float		x;
	float		y;
	float		i;

	if (fabsf(p2->x - p1->x) > fabsf(p2->y - p1->y))
		steps = fabsf(p2->x - p1->x);
	else
		steps = fabsf(p2->y - p1->y);
	p_increment.x = (p2->x - p1->x) / (float)steps;
	p_increment.y = (p2->y - p1->y) / (float)steps;
	x = p1->x;
	y = p1->y;
	i = 0;
	while (i <= steps)
	{
		if (x < data->map->img_map->width
			&& y < data->map->img_map->height && x >= 0 && y >= 0)
			mlx_put_pixel(data->map->img_map, x, y, color);
		x += p_increment.x;
		y += p_increment.y;
		i++;
	}
}
