/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 10:57:13 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	return (0);
}

int	ft_update_position_player(t_data *data)
{
	int		move_step;
	float	angle;
	float	new_x;
	float	new_y;

	data->player->rotangle += (data->player->turndir * data->player->rotspeed);
	angle = data->player->rotangle;
	if (data->player->view_player == 1)
		angle += M_PI / 2;
	else if (data->player->view_player == 2)
		angle -= M_PI / 2;
	data->player->view_player = 0;
	move_step = data->player->walkdirection * data->player->movespeed;
	new_x = data->player->x + cos(angle) * move_step;
	new_y = data->player->y + sin(angle) * move_step;
	if (ft_check_wall_intersection(data, new_x, new_y) != 1)
	{
		data->player->x = new_x;
		data->player->y = new_y;
	}
	return (0);
}

void	ft_player(t_data *data)
{
	rest_image(data->player->img_player);
	ft_cast_all_rays(data);
}
