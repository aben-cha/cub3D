/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 11:14:52 by aben-cha         ###   ########.fr       */
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
	if (data->player->img_player == NULL)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("mlx_new_image failed.");
	}
	ft_player(data);
	mlx_image_to_window(data->mlx, data->player->img_player, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data_mlx;

	parsing(&data_mlx, av[1]);
	ft_cub3d(&data_mlx);
	mlx_loop_hook(data_mlx.mlx, ft_update_env, &data_mlx);
	mlx_loop(data_mlx.mlx);
	return (0);
}
