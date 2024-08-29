/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:01:17 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/29 13:42:52 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_rect(t_data *data, float size_x, float size_y, int color)
{
    float x = 0;
    float y = 0;
    float rect_size = TILE_SIZE; 
    
    while (x < rect_size)
    {
        y = 0;
        while (y < rect_size)
        {
            if (size_x + x < TILE_MAP && size_y + y < TILE_MAP && size_x + x >= 0 && size_y + y >= 0)
                mlx_put_pixel(data->map->img_map, size_x + x, size_y + y, color);
            y++;
        }
        x++;
    }
}
void    ft_minimap(t_data *data)
{
    int i;
    int j;
    int sig = 0;
    int color = ft_color(data->element.floor_color.red, data->element.floor_color.green, 
    data->element.floor_color.blue, 100);
    float scale_factor = (float)TILE_SIZE / TILE_SIZE_MAP;
    int x1 = (int)(data->player->x / scale_factor);
    int y1 = (int)(data->player->y / scale_factor);

    int x = x1 - TILE_MAP / 2;
    int y = y1 - TILE_MAP / 2;
    if (x <= 0 | y <= 0)
        sig = 1;
    i = 0;
    j = 0;
    while (i < TILE_MAP)
    {
        j = 0;
        while (j < TILE_MAP)
        {
            int map_x = (i + x) / TILE_SIZE_MAP;
            int map_y = (j + y) / TILE_SIZE_MAP;
           if (map_x >= 0 && map_x < data->map->width && map_y >= 0 && map_y < data->map->height)
            {
                if (data->map->arr_map[map_y][map_x] == '1')
                        mlx_put_pixel(data->map->img_map,i,j,0x808080FF);
                else
                        mlx_put_pixel(data->map->img_map,i,j,color);
                
            }
            else if (sig ==1 ||map_x>= data->map->width||map_y>=data->map->height)
                mlx_put_pixel(data->map->img_map,i,j,color);
            j++;
        }
        i++;
    }
    ft_border_map(data);
}

void    ft_border_map(t_data *data)
{
    int x;
    int y;
    float mx;
    float my;
    
    int r = TILE_MAP/2;
    int r2 = TILE_MAP/2 - 6;
    x = -r;
    y = -r;
    while (x < r)
    {
        y = -r;
        while (y < r)
        {
            mx = TILE_MAP/2 + x; 
            my = TILE_MAP/2 + y;
            if(pow(x,2)+pow(y,2) < pow(r,2) && pow(x,2)+pow(y,2) >= pow(r2,2))
                mlx_put_pixel(data->map->img_map,mx,my,0x000000FF);
            if(pow(x,2)+pow(y,2) >= pow(r,2))
                mlx_put_pixel(data->map->img_map,mx,my,0);
            y++;
        }
        x++;
    }

}
