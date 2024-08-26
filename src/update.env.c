/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/26 14:53:41 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void ft_update_env(void  *d)
{
    t_data *data = (t_data *)d;
    
    if (mlx_is_key_down(data->mlx, MLX_KEY_UP)|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN) || mlx_is_key_down(data->mlx, MLX_KEY_S)|| mlx_is_key_down(data->mlx, MLX_KEY_W))
        data->player->turnDirection = 0;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(data->mlx, MLX_KEY_LEFT)|| mlx_is_key_down(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->player->walkDirection = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_UP) == 1 || mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        data->player->walkDirection = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN) == 1 || mlx_is_key_down(data->mlx, MLX_KEY_S))
    {   
        data->player->walkDirection = -1;
        ft_update_position_player(data);
        ft_player(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == 1 || mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        data->player->turnDirection = -1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == 1 || mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        data->player->turnDirection = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == 1)
       mlx_close_window(data->mlx);
}