/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/29 11:52:54 by aben-cha         ###   ########.fr       */
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

void load_images1(t_data *data)
{
    t_list *head;

    head = data->texturel;
    while (head)
    {
        if (head->c == 'N')
        {
            data->player->walltexteur_n = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->player->walltexteur_n); 
        }
        else if (head->c == 'S')
        {
            data->player->walltexteur_s = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->player->walltexteur_s);
        }
        else if (head->c == 'E')
        {
            data->player->walltexteur_e = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->player->walltexteur_e);
        }
        else if (head->c == 'W')
        {
            data->player->walltexteur_w = mlx_load_png(head->content);
            convert_abgr_to_rgba(data, data->player->walltexteur_w);
        }
        if (!data->player->walltexteur_n || !data->player->walltexteur_w ||!data->player->walltexteur_s ||!data->player->walltexteur_e)
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
    load_images1(data);
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
    data_mlx.store_x = WINDOW_WHIDTH / 2;
    data_mlx.mlx = mlx_init(WINDOW_WHIDTH,WINDOW_HEIGHT,"cub3D",1);
    data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,data_mlx.mlx->width,data_mlx.mlx->height);
    data_mlx.map->img_map = mlx_new_image(data_mlx.mlx,TILE_MAP,TILE_MAP);
    // ft_map(&data_mlx);
    load_images(&data_mlx);
    // draw_circle(&data_mlx,0x00FFFFFF);
    ft_player(&data_mlx);

    mlx_image_to_window(data_mlx.mlx,data_mlx.player->img_player,0,0);
    // mlx_image_to_window(data_mlx.mlx,data_mlx.map->img_map,40,600);
    //  ft_wait_move_animation(&data_mlx);
    mlx_set_cursor_mode(data_mlx.mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data_mlx.mlx, (void *)mouse, &data_mlx);
    mlx_loop_hook(data_mlx.mlx, ft_wait_move_animation, &data_mlx);
    mlx_loop_hook(data_mlx.mlx,ft_update_env,&data_mlx);
    
    mlx_loop(data_mlx.mlx);
    return 0;
}