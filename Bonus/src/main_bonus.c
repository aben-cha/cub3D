/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:01:00 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 11:54:06 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	parsing(t_data *data, char *av)
{
	fill_list(data, av);
	is_valid_map(data);
	init_data_player(data);
	load_textures(data);
}

void	ft_cub3d(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WHIDTH, WINDOW_HEIGHT, "cub3D", 1);
	if (data->mlx == NULL)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("mlx_init failed.");
	}
	data->player->img_player = mlx_new_image(data->mlx,
			data->mlx->width, data->mlx->height);
	data->map->img_map = mlx_new_image(data->mlx, TILE_MAP, TILE_MAP);
	if (data->player->img_player == NULL)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("mlx_image failed.");
	}
	load_images(data);
	ft_player(data);
	mlx_image_to_window(data->mlx, data->player->img_player, 0, 0);
	mlx_image_to_window(data->mlx, data->map->img_map, 40, 600);
}

int	main(int ac, char **av)
{
	t_data	data_mlx;

	parsing(&data_mlx, av[1]);
	ft_cub3d(&data_mlx);
	mlx_loop_hook(data_mlx.mlx, ft_update_env, &data_mlx);
	mlx_set_cursor_mode(data_mlx.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(data_mlx.mlx);
	return (0);
}
