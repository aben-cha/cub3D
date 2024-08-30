/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/30 22:17:57 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void ft_update_env(void  *d)
{
    t_data *data = (t_data *)d;
    mouse(d);
    data->player->walkDirection = 1;
    if ( mlx_is_key_down(data->mlx, MLX_KEY_S)
        || mlx_is_key_down(data->mlx, MLX_KEY_W)
        ||mlx_is_key_down(data->mlx, MLX_KEY_D)
        || mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->player->turnDirection = 0;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) 
        || mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
        || mlx_is_key_down(data->mlx, MLX_KEY_A) 
        || mlx_is_key_down(data->mlx, MLX_KEY_D)
        ||mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT) == 1)
        data->player->walkDirection = 0;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        data->player->walkDirection = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {   
        data->player->walkDirection = -1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        data->player->view_player = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {   
        data->player->view_player = 2;
        ft_update_position_player(data);
        ft_player(data);
    }  
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == 1)
    {
        data->player->turnDirection = -1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == 1)
    {
        data->player->turnDirection = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_O)== 1)
    {
        float x1 = data->player->x + cos(data->player->rotationAngle) * TILE_SIZE;
        float y1 = data->player->y + sin(data->player->rotationAngle) * TILE_SIZE;
        if (data->map->arr_map[(int)y1  / TILE_SIZE][(int)x1 / TILE_SIZE] == 'D')
        {
            data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] = 'C';
            ft_player(data);
        }
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_C) == 1)
    {
        float x1 = data->player->x + cos(data->player->rotationAngle) * TILE_SIZE;
        float y1 = data->player->y + sin(data->player->rotationAngle) * TILE_SIZE;
        if (data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] == 'C')
        {
            data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] = 'D';
            ft_player(data);
        }
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == 1)
       mlx_close_window(data->mlx);

}