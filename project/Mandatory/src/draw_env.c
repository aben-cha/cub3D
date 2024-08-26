/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:14:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/11 11:49:43 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    draw_circle(t_data *data,int color)
{
    int x;
    int y;
    float px;
    float py;
    int r;

    r = data->player->radius;
    x = -r;
    while (x < r)
    {
        y = -r;
        while (y < r)
        {
            if (pow(x, 2) + pow(y, 2) < pow(r, 2))
            {
                px = TILE_MAP/2 + x; 
                py = TILE_MAP/2 + y;
                if (px < TILE_MAP && py < TILE_MAP && px>=0 && py>=0)
                    mlx_put_pixel(data->map->img_map,px,py,color);
            }

            y++;
        }
        x++;
    }
    
    
}

void draw_line(t_data *data, float x0, float y0, float x1, float y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = x0;
    float Y = y0;
    float i = 0;
    while (i <= steps)
    {
        if (X < data->map->img_map->width && Y < data->map->img_map->height && X>=0 && Y>=0)
            mlx_put_pixel(data->map->img_map, X, Y, color);
        X += Xinc;
        Y += Yinc;
        i++;
    }
}