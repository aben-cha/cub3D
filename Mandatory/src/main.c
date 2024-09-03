/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:30:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 23:16:05 by ataoufik         ###   ########.fr       */
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
		free_data_mlx(data, 0);
		print_error("mlx_init failed.");
	}
	data->player->img_player = mlx_new_image(data->mlx,
			data->mlx->width, data->mlx->height);
	if (data->player->img_player == NULL)
	{
		free_data_mlx(data, 1);
		print_error("mlx_new_image failed.");
	}
	ft_player(data);
	if (mlx_image_to_window(data->mlx, data->player->img_player, 0, 0) == -1)
	{
		free_data_mlx(data, 2);
		print_error("mlx_image_to_window failed.");
	}
}

int	main(int ac, char **av)
{
	t_data	data_mlx;

	(void)ac;
	parsing(&data_mlx, av[1]);
	ft_cub3d(&data_mlx);
	mlx_loop_hook(data_mlx.mlx, ft_update_env, &data_mlx);
	mlx_loop(data_mlx.mlx);
	mlx_delete_image(data_mlx.mlx, data_mlx.player->img_player);
	free_data_mlx(&data_mlx, 0);
	return (0);
}
