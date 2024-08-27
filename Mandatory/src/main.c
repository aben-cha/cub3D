/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/27 10:20:20 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void convert_abgr_to_rgba(t_data *data, mlx_texture_t* texture)
{
    uint8_t     *pixels;
    uint32_t    i;
    uint8_t     a;
    uint8_t     b;
    uint8_t     g;
    uint8_t     r;
    
    if (!texture || !texture->pixels)
    {
        (free_array(data->map->arr_map), free_data(data, 1));
        print_error("Texture or its pixels are not available.");
    }
    i = -1;
    pixels = texture->pixels;
    while (++i < texture->width * texture->height)
    {
        a = pixels[4 * i + 0];
        b = pixels[4 * i + 1];
        g = pixels[4 * i + 2];
        r = pixels[4 * i + 3];
        pixels[4 * i + 0] = r;
        pixels[4 * i + 1] = g;
        pixels[4 * i + 2] = b;
        pixels[4 * i + 3] = a;
    }
}

void load_images(t_data *data)
{
    t_list *head;

    head = data->texturel;
    while (head)
    {
        if (head->c == 'N')
        {
            data->texture->walltexteur_n = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->texture->walltexteur_n); 
        }
        else if (head->c == 'S')
        {
            data->texture->walltexteur_s = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->texture->walltexteur_s);
        }
        else if (head->c == 'E')
        {
            data->texture->walltexteur_e = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->texture->walltexteur_e);
        }
        else if (head->c == 'W')
        {
            data->texture->walltexteur_w = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->texture->walltexteur_w);
        }
        if (!data->texture->walltexteur_n || !data->texture->walltexteur_w ||!data->texture->walltexteur_s ||!data->texture->walltexteur_e)
        {
            free_array(data->map->arr_map);
            free_data(data, 1);
            print_error("Error load png.");
        }
        head = head->next;
    }
}

void    inite_data_player(t_data *data)
{
    load_images(data);
    data->player->radius = 5;
    data->player->turnDirection = 0;
    data->player->walkDirection = 0;
    data->player->moveSpeed = 10;
    data->player->rotationSpeed = 5 * (M_PI / 180);
    if (data->player->isFacing == '0')
    {
        free_array(data->map->arr_map), free_data(data, 1);
        print_error("Player is not found.");
    }
    if (data->player->isFacing== 'N')
        data->player->rotationAngle =  3 * M_PI / 2;
    else if (data->player->isFacing== 'E')
        data->player->rotationAngle =  0;
    else if (data->player->isFacing== 'S')
        data->player->rotationAngle = M_PI / 2;
    else if (data->player->isFacing== 'W')
        data->player->rotationAngle =  M_PI;
}

void parsing(t_data *data, char *av)
{
    fill_list(data, av);
    is_valid_Map(data);
    inite_data_player(data);
}

int		main(int ac, char **av)
{
    t_data  data_mlx;
    parsing(&data_mlx, av[1]);
    data_mlx.mlx = mlx_init(WINDOW_WHIDTH,WINDOW_HEIGHT,"cub3D",1);
    data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,data_mlx.mlx->width,data_mlx.mlx->height);
    // load_images(&data_mlx);
    ft_player(&data_mlx);
    mlx_image_to_window(data_mlx.mlx,data_mlx.player->img_player,0,0);
    // mlx_loop_hook(data_mlx.mlx, ft_wait_move_animation, &data_mlx);
    mlx_loop_hook(data_mlx.mlx,ft_update_env,&data_mlx);
    mlx_loop(data_mlx.mlx);
    return 0;
}
