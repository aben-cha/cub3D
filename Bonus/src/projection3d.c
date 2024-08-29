/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:57:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/29 15:55:30 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int    ft_color(int r, int g, int b, int a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}
void    ft_floor(t_data *data,int x, int start_y)
{
    int j;
    uint32_t floorcolor =ft_color(data->element.floor_color.red, data->element.floor_color.green, data->element.floor_color.blue, 255);
    j = start_y;
    while (j < data->mlx->height)
    {
        if (j >= 0 && j < data->mlx->height) 
        {
            if (x >= 0 && x < data->mlx->width)
                mlx_put_pixel(data->player->img_player, x, j, floorcolor);
        }
        j++;
    }
}


void    ft_ceil(t_data *data,int x, int end_y)
{
    int j;
    uint32_t ceilcolor =ft_color(data->element.ceiling_color.red, data->element.ceiling_color.green, data->element.ceiling_color.blue, 255);
    j = 0;
    while (j < end_y)
    {
        if (j >= 0 && j < data->mlx->height) 
        {
            if (x >= 0 && x < data->mlx->width)
                mlx_put_pixel(data->player->img_player, x, j, ceilcolor);
        }
        j++;
    }
}
uint32_t get_pixel_color(mlx_texture_t *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0; 
    int index = (y * texture->width) + x;
    
    return ((uint32_t *)texture->pixels)[index];
}

void    ft_projection3D(t_data *data,float x,int sig , t_ray *ray, float raydistance)
{
    float d_projectplan;
    float wallheight;
    float new_distance;

    d_projectplan = ((float)data->mlx->width / 2.0) / tan(FOV_ANGLE /2.0);
    wallheight = ((float)TILE_SIZE / raydistance) * d_projectplan;
    uint32_t texcolor;
    // texcolor = 0xFFAD00FF;
    int offset_x;
    int offset_y;
    if (sig == 0)
    {
        offset_x = (int)ray->y_intercept % TILE_SIZE;
        // texcolor = 0x00AD12FF;
    }
    else
    {
        offset_x = (int)ray->x_intercept % TILE_SIZE;
        // texcolor = 0xAADD00FF;
    }

    int top_pixel = (WINDOW_HEIGHT / 2) - (wallheight / 2);
    int y = top_pixel;
    ft_ceil(data,x,y);
    ft_floor(data,x,top_pixel + wallheight);
    while (y< (wallheight + top_pixel))
    {
        if (y >= 0 && y < WINDOW_HEIGHT) 
        {
            if (sig == 0 && ray->ray_is_left == true)
            {
                if (ray->flag== 1)//door
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_d->width) / wallheight; // door
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_d, offset_x, offset_y);   ///door
                    if (x >= 0 && x < data->mlx->width)
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                    
                }
                else
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_n->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_n, offset_x, offset_y);   
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                    
                }
            }
            else if (sig == 0 && ray->ray_is_right== true)
            {
                if (ray->flag== 1)//door
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_d->width) / wallheight; //door
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_d, offset_x, offset_y); //door
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                }
                else
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_s->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_s, offset_x, offset_y);
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                }
            }
            else if (sig != 0 && ray->ray_is_up== true)
            {
                if (ray->flag == 1)
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_d->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_d, offset_x, offset_y);
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                    
                }
                else
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_e->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_e, offset_x, offset_y);
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                    
                }
            }
            else
            {
                if (ray->flag ==1)
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_d->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_d, offset_x, offset_y);   
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                }
                else
                {
                    int offset_y =((y - top_pixel) * data->player->walltexteur_e->width) / wallheight;
                    uint32_t texcolor = get_pixel_color(data->player->walltexteur_e, offset_x, offset_y);   
                    if (x >= 0 && x < data->mlx->width) 
                        mlx_put_pixel(data->player->img_player, x,y, texcolor);
                }
            }
        }
        y++;
    }
}
