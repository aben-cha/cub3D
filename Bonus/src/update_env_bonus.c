/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 19:23:00 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	key_release(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_W)
		||mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player->turndir = 0;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player->walkdirection = 0;
}

void	wasd_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player->walkdirection = 1;
		ft_update_position_player(data);
		ft_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->walkdirection = -1;
		ft_update_position_player(data);
		ft_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->view_player = 1;
		ft_update_position_player(data);
		ft_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->view_player = 2;
		ft_update_position_player(data);
		ft_player(data);
	}
}

void	left_right_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == 1)
	{
		data->player->turndir = -1;
		ft_update_position_player(data);
		ft_player(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == 1)
	{
		data->player->turndir = 1;
		ft_update_position_player(data);
		ft_player(data);
	}
}

void	open_close_door(t_data *data, char **map)
{
	float	x1;
	float	y1;

	x1 = data->player->x + cos(data->player->rotangle) * TILE_SIZE;
	y1 = data->player->y + sin(data->player->rotangle) * TILE_SIZE;
	if (mlx_is_key_down(data->mlx, MLX_KEY_O) == 1)
	{
		if (map[(int)y1 / TILE_SIZE][(int)x1 / TILE_SIZE] == 'D')
		{
			map[(int)(y1 / TILE_SIZE)][(int)(x1 / TILE_SIZE)] = 'C';
			ft_player(data);
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C) == 1
		&& map[(int)(data->player->y / TILE_SIZE)]
		[(int )(data->player->x / TILE_SIZE)] != 'C')
	{
		if (map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] == 'C')
		{
			map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] = 'D';
			ft_player(data);
		}
	}
}

void	ft_update_env(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	data->player->walkdirection = 1;
	mouse(d);
	loading_sprites(data);
	key_release(data);
	wasd_keys(data);
	left_right_keys(data);
	open_close_door(data, data->map->arr_map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_L) == 1 && data->key_hand == 0)
	{
		data->counter++;
		data->player->walkdirection = 0;
		data->player->turndir = 0;
		ft_update_position_player(data);
		ft_player(data);
		data->key_hand = 1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_L) == 0)
		data->key_hand = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == 1)
		mlx_close_window(data->mlx);
}
