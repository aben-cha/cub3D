/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 18:52:09 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ft_update_env(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	data->player->walkdirection = 1;
	key_release(data);
	wasd_keys(data);
	left_right_keys(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == 1)
		mlx_close_window(data->mlx);
}
