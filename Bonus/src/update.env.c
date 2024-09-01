/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 18:47:06 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void loading_sprites(void *d)
{
    static int i;
    t_data *data = (t_data *)d;
    
    if (data->counter == 0)
        ft_wait_move_animation(data);
    if (i> 5)
        i = 0;
    if (i == 5)
    {
        ft_load_move_animation(data);
        if (data->animation->current_frame == 36)
        {
            i = 0;
            data->counter = 0;
            data->animation->current_frame = 0;
        }
    }
    if (data->counter != 0)
    {
        ft_shoot_move_animation(data);
        if (data->animation->current_frame == 13)
        {
            data->animation->current_frame = 0;
            i += data->counter;
            data->counter = 0;
            printf("i  %d\n", i);
        }
    }
}

void ft_update_env(void  *d)
{
    t_data *data = (t_data *)d;
    
    mouse(d);
    loading_sprites(d);
    data->player->walkDirection = 1;
    if ( mlx_is_key_down(data->mlx, MLX_KEY_S)
        || mlx_is_key_down(data->mlx, MLX_KEY_W)
        ||mlx_is_key_down(data->mlx, MLX_KEY_D)
        || mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->player->turnDir = 0;
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {   
        data->player->walkDirection = -1;
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_L)== 1 && data->key_hand == 0)
    {
        data->counter++;
        data->player->walkDirection = 0;
        data->player->turnDir = 0;
        ft_update_position_player(data);
        ft_player(data);
        data->key_hand = 1;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_L)== 0)
       data->key_hand = 0;  
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) == 1)
    {
        data->player->turnDir = -1;
        ft_update_position_player(data);
        ft_player(data);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == 1)
    {
        data->player->turnDir = 1;
        ft_update_position_player(data);
        ft_player(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_O)== 1)
    {
        float x1 = data->player->x + cos(data->player->rotAngle) * TILE_SIZE;
        float y1 = data->player->y + sin(data->player->rotAngle) * TILE_SIZE;
        if (data->map->arr_map[(int)y1  / TILE_SIZE][(int)x1 / TILE_SIZE] == 'D')
        {
            data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] = 'C';
            ft_player(data);
        }
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_C) == 1&&data->map->arr_map[(int)(data->player->y / TILE_SIZE)][(int )(data->player->x / TILE_SIZE)] != 'C')
    {
        float x1 = data->player->x + cos(data->player->rotAngle) * TILE_SIZE;
        float y1 = data->player->y + sin(data->player->rotAngle) * TILE_SIZE;
        if (data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] == 'C')
        {
            data->map->arr_map[(int)(y1 / TILE_SIZE)][(int )(x1 / TILE_SIZE)] = 'D';
            ft_player(data);
        }
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == 1)
       mlx_close_window(data->mlx);

}