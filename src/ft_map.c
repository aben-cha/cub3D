/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:01:17 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/07 11:58:24 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void    draw_rect(t_data *data,float size_x,float size_y , int color)
{
    float x;
    float y;
    x = 0;
    y = 0;
    while (x < TILE_SIZE)// - 1 px
    {
        y = 0;
        while (y < TILE_SIZE)// - 1px 
        {
            mlx_put_pixel(data->map->img_map,size_x + x,size_y + y,color);
            y++;
        }
        x++;
    }
}
void    ft_map(t_data *data)
{
    int i = 0;
    int j;
    float tileX;
    float tileY;
    int color;
    data->map->img_map = mlx_new_image(data->mlx,data->map->width* TILE_SIZE,data->map->height* TILE_SIZE);
    while (i < data->map->height)
    {
        j= 0;
        while (j < data->map->width)
        {
            tileX = j * TILE_SIZE;
            tileY = i * TILE_SIZE;
            if (data->map->arr_map[i][j] == '1')
                color = 0x000000FF;
            else
                color = 0;
            draw_rect(data,SIZE_MINI_MAP*tileX,SIZE_MINI_MAP*tileY,color);
            j++;
        }
        i++;
    }
    // border_map(data);
}

void    border_map(t_data *data)
{
    int i = 0;
    int j = 0;
    while (i < 200)
    {
        j = 0;
        while (j < 200)
        {
            if (j == 0 || j == 199 || i == 0 || i == 199)
                mlx_put_pixel(data->map->img_map,i,j,0x0000ACFF);
            j++;
        }
        i++;
    }

    
}