/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/14 15:08:34 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void convert_abgr_to_rgba(mlx_texture_t* texture)
{
    uint8_t* pixels;
    uint32_t i;

    
    if (!texture || !texture->pixels)
        return;
    i = -1;
    pixels = texture->pixels;
    while (++i < texture->width * texture->height)
    {
        uint8_t a = pixels[4 * i + 0];
        uint8_t b = pixels[4 * i + 1];
        uint8_t g = pixels[4 * i + 2];
        uint8_t r = pixels[4 * i + 3];
        pixels[4 * i + 0] = r;
        pixels[4 * i + 1] = g;
        pixels[4 * i + 2] = b;
        pixels[4 * i + 3] = a;
    }
}

void    inite_data_player(t_data *data)
{
    
    data->player->walltexteur_n = mlx_load_png(data->texture->north_texture);
    convert_abgr_to_rgba(data->player->walltexteur_n);
    data->player->walltexteur_s = mlx_load_png(data->texture->south_texture);
    convert_abgr_to_rgba(data->player->walltexteur_s);

    data->player->walltexteur_w = mlx_load_png(data->texture->west_texture);
    convert_abgr_to_rgba(data->player->walltexteur_w);

    data->player->walltexteur_e = mlx_load_png(data->texture->east_texture);
    convert_abgr_to_rgba(data->player->walltexteur_e);

    if (!data->player->walltexteur_n || !data->player->walltexteur_w ||!data->player->walltexteur_s ||!data->player->walltexteur_e)
    {
        // ft_lstclear(data->texture);
        printf("Error \"load png\"\n");
        exit(1);
    }
    data->player->radius = 5;
    data->player->turnDirection = 0;
    data->player->walkDirection = 0;
    data->player->moveSpeed = 3;
    data->player->rotationSpeed = 10* (M_PI / 180);
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
    // print_elements(data);
}

int		main(int ac, char **av)
{
    t_data  data_mlx;
    parsing(&data_mlx, av[1]);
    data_mlx.mlx = mlx_init(WINDOW_WHIDTH,WINDOW_HEIGHT,"cub3D",1);
    data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,data_mlx.mlx->width,data_mlx.mlx->height);
    data_mlx.map->img_map = mlx_new_image(data_mlx.mlx,TILE_MAP,TILE_MAP);
    ft_map(&data_mlx);
    load_images(&data_mlx);
    // draw_circle(&data_mlx,0x00FFFFFF);
    ft_player(&data_mlx);

    mlx_image_to_window(data_mlx.mlx,data_mlx.player->img_player,0,0);
    mlx_image_to_window(data_mlx.mlx,data_mlx.map->img_map,40,600);
    //  ft_wait_move_animation(&data_mlx);
    mlx_loop_hook(data_mlx.mlx, ft_wait_move_animation, &data_mlx);
    mlx_loop_hook(data_mlx.mlx,ft_update_env,&data_mlx);
    mlx_loop(data_mlx.mlx);
    return 0;
}