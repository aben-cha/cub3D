/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/02 18:36:48 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parsing(t_data *data, char *av)
{
	fill_list(data, av);
	is_valid_map(data);
	init_data_player(data);
	load_textures(data);
}

int	main(int ac, char **av)
{
	t_data	data_mlx;

	parsing(&data_mlx, av[1]);
	data_mlx.mlx = mlx_init(WINDOW_WHIDTH, WINDOW_HEIGHT, "cub3D", 1);
	data_mlx.player->img_player = mlx_new_image(data_mlx.mlx,
			data_mlx.mlx->width, data_mlx.mlx->height);
	data_mlx.map->img_map = mlx_new_image(data_mlx.mlx, TILE_MAP, TILE_MAP);
	ft_player(&data_mlx);
	mlx_image_to_window(data_mlx.mlx, data_mlx.player->img_player, 0, 0);
	mlx_loop_hook(data_mlx.mlx, ft_update_env, &data_mlx);
	mlx_loop(data_mlx.mlx);
	return (0);
}
