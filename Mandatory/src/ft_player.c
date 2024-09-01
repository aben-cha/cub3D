/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 13:29:24 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"


void rest_image(mlx_image_t *image)
{
    uint32_t x = 0;
    uint32_t y = 0;
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
int ft_check_wall_intersection(t_data *data, float px, float py)
{
    int r = data->player->radius + 150;
    int x = -r;
    int y = -r;
    while (x < r)
    {
        y = -r;
        while(y < r)
        {
            if (pow(x, 2) + pow(y, 2) < pow(r, 2))
            {
                int x_map = floor((px + x) / TILE_SIZE);
                int y_map = floor((py + y) / TILE_SIZE);
                if (x_map >= 0 && x_map < data->map->width && y_map >= 0 && y_map < data->map->height)
                {
                    if (data->map->arr_map[y_map][x_map] == '1')
                        return (1);
                }
            }
            y++;
        }
        x++;
    }
    return (0);
}
int ft_check_wall(t_data *data, float x,float y)
{
    int x_map = floor(x / TILE_SIZE);
    int y_map = floor(y / TILE_SIZE);
    if (x_map < 0 || x_map >=data->map->width || y_map < 0 || y_map >= data->map->height)
        return 1;
    if (data->map->arr_map[y_map][x_map] == '1')
        return 1;
    return 0;
    
}

int ft_update_position_player(t_data *data)
{
    data->player->rotationAngle += (data->player->turnDirection * data->player->rotationSpeed);
    int move_step;
    float angle;
    float new_x;
    float new_y;
    angle = data->player->rotationAngle;
    if (data->player->view_player ==1)
    {
        angle -=3*M_PI/2;   
    }
    else if (data->player->view_player ==2)
    {
        angle +=3*M_PI/2;
    }
    data->player->view_player = 0;
    move_step = data->player->walkDirection * data->player->moveSpeed;
    new_x = data->player->x+ cos(angle) * move_step;
    new_y = data->player->y + sin(angle) * move_step;
    

    if (ft_check_wall_intersection(data, new_x,new_y) != 1)
    {
        data->player->x = new_x;
        data->player->y = new_y;
    }
    return (0);
}


void    ft_player(t_data *data)
{
    int color = 0x00FF00FF;
    int fcolor = 0x00FFFFFF;
    int raycolor = 0xC47D7DFF;
    rest_image(data->player->img_player);
    ft_cast_all_rays(data,raycolor);
}
