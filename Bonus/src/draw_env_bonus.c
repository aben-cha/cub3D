/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:14:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 10:56:47 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	view_player(t_data *data, int color)
{
	float		x1;
	float		y1;
	t_pos		center;
	t_pos		last_point;

	center.x = TILE_MAP / 2;
	center.y = TILE_MAP / 2;
	x1 = center.x + cos(data->player->rotangle) * 30;
	y1 = center.y + sin(data->player->rotangle) * 30;
	last_point.x = x1;
	last_point.y = y1;
	draw_line(data, &center, &last_point, color);
}
