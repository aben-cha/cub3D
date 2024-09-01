/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 15:58:28 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void	convert_abgr_to_rgba(t_data *data, mlx_texture_t *texture)
{
	t_con_var	vars;

	if (!texture || !texture->pixels)
	{
		(free_array(data->map->arr_map), free_data(data, 1));
		print_error("Texture or its pixels are not available.");
	}
	vars.i = -1;
	vars.pixels = texture->pixels;
	while (++vars.i < texture->width * texture->height)
	{
		vars.a = vars.pixels[4 * vars.i + 0];
		vars.b = vars.pixels[4 * vars.i + 1];
		vars.g = vars.pixels[4 * vars.i + 2];
		vars.r = vars.pixels[4 * vars.i + 3];
		vars.pixels[4 * vars.i + 0] = vars.r;
		vars.pixels[4 * vars.i + 1] = vars.g;
		vars.pixels[4 * vars.i + 2] = vars.b;
		vars.pixels[4 * vars.i + 3] = vars.a;
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
	data->player->turnDir = 0;
	data->player->walkDirection = 0;
	data->player->moveSpeed = 60;
	data->player->rotSpeed = 5 * (M_PI / 180);
	if (data->player->isFacing == '0')
	{
		(free_array(data->map->arr_map), free_data(data, 1));
		print_error("Player is not found.");
	}
	if (data->player->isFacing == 'N')
		data->player->rotAngle = 3 * M_PI / 2;
	else if (data->player->isFacing == 'E')
		data->player->rotAngle = 0;
	else if (data->player->isFacing == 'S')
		data->player->rotAngle = M_PI / 2;
	else if (data->player->isFacing == 'W')
		data->player->rotAngle = M_PI;
}

void parsing(t_data *data, char *av)
{
    fill_list(data, av);
    is_valid_map(data);
    inite_data_player(data);
	// free_array(map_array) && free_data(data, 1);
}

int		main(int ac, char **av)
{
    t_data  data_mlx;
    parsing(&data_mlx, av[1]);
    data_mlx.mlx = mlx_init(WINDOW_WHIDTH,WINDOW_HEIGHT,"cub3D",1);
    data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,data_mlx.mlx->width,data_mlx.mlx->height);
    ft_player(&data_mlx);
    mlx_image_to_window(data_mlx.mlx,data_mlx.player->img_player,0,0);
    mlx_loop_hook(data_mlx.mlx,ft_update_env,&data_mlx);
    mlx_loop(data_mlx.mlx);
    return 0;
}