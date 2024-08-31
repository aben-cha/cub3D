/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/31 13:24:06 by ataoufik         ###   ########.fr       */
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

    data->player->walltexteur_d = mlx_load_png("./door.png");
    convert_abgr_to_rgba(data->player->walltexteur_d);
    if (!data->player->walltexteur_n || !data->player->walltexteur_w || !data->player->walltexteur_s || !data->player->walltexteur_e)
    {
        // ft_lstclear(data->texture);
        printf("Error \"load png\"\n");
        exit(1);
    }
    data->player->radius = 5;
    data->player->turnDirection = 0;
    data->player->walkDirection = 1;
    data->player->moveSpeed = 100;
    data->player->view_player = 0;
    data->player->rotationSpeed = 20* (M_PI / 180);
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

void	mouse(void *param)
{
    int x;
    int y;
	t_data	*data = (t_data *)param;
    
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->player->rotationAngle += (float)(x -  data->store_x) / (WINDOW_HEIGHT / 2);
	mlx_set_mouse_pos(data->mlx, data->store_x, (WINDOW_HEIGHT / 2));
    ft_player(data);
}

int		main(int ac, char **av)
{
    t_data  data_mlx;
    parsing(&data_mlx, av[1]);
    data_mlx.mlx = mlx_init(WINDOW_WHIDTH,WINDOW_HEIGHT,"cub3D",1);
    data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,data_mlx.mlx->width,data_mlx.mlx->height);
    data_mlx.map->img_map = mlx_new_image(data_mlx.mlx,TILE_MAP,TILE_MAP);
    load_images(&data_mlx);
    ft_player(&data_mlx);
    mlx_image_to_window(data_mlx.mlx,data_mlx.player->img_player,0,0);
    mlx_image_to_window(data_mlx.mlx,data_mlx.map->img_map,40,600);
    mlx_set_cursor_mode(data_mlx.mlx, MLX_MOUSE_DISABLED);
    mlx_loop_hook(data_mlx.mlx, ft_wait_move_animation, &data_mlx);
    mlx_loop_hook(data_mlx.mlx,ft_update_env,&data_mlx);
    mlx_loop(data_mlx.mlx);
    return 0;
}