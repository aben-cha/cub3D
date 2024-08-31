/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 00:08:50 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	ft_check_arr(t_data *data, t_pos *p1, t_pos *point)
{
	int	x_map;
	int	y_map;

	x_map = floor((p1->x + point->x) / TILE_SIZE);
	y_map = floor((p1->y + point->y) / TILE_SIZE);
	if (x_map >= 0 && x_map < data->map->width
		&& y_map >= 0 && y_map < data->map->height)
	{
		if (data->map->arr_map[y_map][x_map] == '1'
			|| data->map->arr_map[y_map][x_map] == 'D')
			return (1);
	}
	return (0);
}

int	ft_check_wall_intersection(t_data *data, float px, float py)
{
	int	y;
	int	x;
	int	r;

	r = data->player->radius + 150;
	x = -r;
	while (x < r)
	{
		y = -r;
		while (y < r)
		{
			if (pow(x, 2) + pow(y, 2) < pow(r, 2))
			{
				if (ft_check_arr(data, &(t_pos){px, py}, &(t_pos){x, y}) == 1)
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_check_wall(t_data *data, float x, float y)
{
	int	x_map;
	int	y_map;

	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (x_map < 0 || x_map >= data->map->width
		|| y_map < 0 || y_map >= data->map->height)
		return (1);
	if (data->map->arr_map[y_map][x_map] == '1')
		return (1);
	else if (data->map->arr_map[y_map][x_map] == 'D')
		return (2);
	return (0);
}

int	ft_update_position_player(t_data *data)
{
	int		move_step;
	float	angle;
	float	new_x;
	float	new_y;

	data->player->rotationAngle += (data->player->turnDirection * data->player->rotationSpeed);
	angle = data->player->rotationAngle;
	if (data->player->view_player == 1)
		angle -= 3 * M_PI / 2;
	else if (data->player->view_player == 2)
		angle += 3 * M_PI / 2;
	data->player->view_player = 0;
	move_step = data->player->walkDirection * data->player->moveSpeed;
	new_x = data->player->x + cos(angle) * move_step;
	new_y = data->player->y + sin(angle) * move_step;
	if (ft_check_wall_intersection(data, new_x, new_y) != 1)
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
	return (0);
}

void	view_player(t_data *data, int color)
{
	float		x1;
	float		y1;
	t_pos		center;
	t_pos		last_point;

	center.x = TILE_MAP / 2;
	center.y = TILE_MAP / 2;
	x1 = center.x + cos(data->player->rotationAngle) * 30;
	y1 = center.y + sin(data->player->rotationAngle) * 30;
	last_point.x = x1;
	last_point.y = y1;
	draw_line(data, &center, &last_point, color);
}

void	ft_player(t_data *data)
{
	int	fcolor;
	int	color;

	color = 0x00FF00FF;
	fcolor = 0x00FFFFFF;
	rest_image(data->map->img_map);
	ft_cast_all_rays(data);
	ft_minimap(data);
	draw_circle(data, color);
	view_player(data, fcolor);
}
