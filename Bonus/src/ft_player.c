/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/11 13:11:08 by ataoufik         ###   ########.fr       */
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
int ft_check_wall_intersection(t_data *data ,float x , float y)
{
    int x_map = floor(x/ TILE_SIZE);
    int y_map = floor(y / TILE_SIZE);
    if (x_map < 0 || x_map >=data->map->width || y_map < 0 || y_map >= data->map->height)
        return 1;
    printf("x  %d  y   %d  \n",x_map,y_map);
    if (data->map->arr_map[y_map][x_map] == '1' && data->map->arr_map[y_map  + 1][x_map -1]=='1')
        return 1;
        // ||(data->map->arr_map[y_map][x_map] == '1' && data->map->arr_map[y_map  + 1][x_map + 1]=='1'))
    return 0;
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
    double new_x;
    double new_y;
    move_step = data->player->walkDirection * data->player->moveSpeed;
    new_x = data->player->x + cos(data->player->rotationAngle) * move_step;
    new_y = data->player->y + sin(data->player->rotationAngle) * move_step;
    
    if (ft_check_wall(data, new_x,new_y) != 1)
    {
        data->player->x = new_x;
        data->player->y = new_y;
    }
    return (0);
}



void view_player(t_data *data, int color)
{

    float centerX = TILE_MAP /2; 
    float centerY = TILE_MAP /2;
    float x1 = centerX + cos(data->player->rotationAngle) * 30;
    float y1 = centerY + sin(data->player->rotationAngle) * 30;
    draw_line(data, centerX,centerY, x1,y1, color);
}

void    ft_player(t_data *data)
{
    int color = 0x00FF00FF;
    int fcolor = 0x00FFFFFF;
    int raycolor = 0xC47D7DFF;
    rest_image(data->map->img_map);
    ft_cast_all_rays(data,raycolor);
    ft_minimap(data);
    draw_circle(data,color);
    view_player(data,fcolor);
}
