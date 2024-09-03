/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:47:00 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 10:57:13 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_variables(t_data *data)
{
	data->list = NULL;
	data->texturel = NULL;
	data->string = NULL;
	data->i = 0;
	data->j = 0;
	data->size = 0;
}

void	data_init(t_data *data)
{
	init_variables(data);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		(ft_lstclear(&data->list), exit(1));
	data->map->arr_map = NULL;
	data->map->height = 0;
	data->map->width = 0;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		(ft_lstclear(&data->list), free(data->map), exit(1));
	data->texture = malloc(sizeof(t_texture));
	if (!data->texture)
		(ft_lstclear(&data->list), free(data->map),
			free(data->player), exit(1));
	data->player->x = 0.0;
	data->player->y = 0.0;
	data->player->isfacing = '0';
}

int	position_of_player(t_data *data, char **map)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (++y < data->map->height - 1)
	{
		x = 0;
		while (++x < data->map->width - 1)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'W' || map[y][x] == 'E')
			{
				data->player->isfacing = data->map->arr_map[y][x];
				data->player->x = (float)x * TILE_SIZE + TILE_SIZE / 2;
				data->player->y = (float)y * TILE_SIZE + TILE_SIZE / 2;
				i++;
			}
		}
	}
	if (i > 1)
		return (free_array(data->map->arr_map), free_data(data, 1), 1);
	return (0);
}

void	init_data_player(t_data *data)
{
	data->player->radius = 5;
	data->player->turndir = 0;
	data->player->walkdirection = 1;
	data->player->movespeed = 100;
	data->player->view_player = 0;
	data->player->rotspeed = 20 * (M_PI / 180);
	if (data->player->isfacing == '0')
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("Player is not found.");
	}
	if (data->player->isfacing == 'N')
		data->player->rotangle = 3 * (M_PI / 2);
	else if (data->player->isfacing == 'E')
		data->player->rotangle = 0;
	else if (data->player->isfacing == 'S')
		data->player->rotangle = M_PI / 2;
	else if (data->player->isfacing == 'W')
		data->player->rotangle = M_PI;
}
