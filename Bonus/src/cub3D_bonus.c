/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:48:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/04 12:50:14 by aben-cha         ###   ########.fr       */
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

void	image_to_window(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->player->img_player, 0, 0) == -1)
	{
		free_data_mlx(data, 3);
		print_error("mlx_image_to_window failed.");
	}
	if (mlx_image_to_window(data->mlx, data->map->img_map, 40, 600) == -1)
	{
		free_data_mlx(data, 3);
		print_error("mlx_image_to_window failed.");
	}
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
		print_error("mlx_image failed.");
	}
	data->map->img_map = mlx_new_image(data->mlx, TILE_MAP, TILE_MAP);
	if (data->player->img_player == NULL)
	{
		mlx_delete_image(data->mlx, data->player->img_player);
		free_data_mlx(data, 1);
		print_error("mlx_image failed.");
	}
	load_images(data);
	ft_player(data);
	image_to_window(data);
}

int	main(int ac, char **av)
{
	t_data	data_mlx;

	(void)ac;
	parsing(&data_mlx, av[1]);
	ft_cub3d(&data_mlx);
	mlx_loop_hook(data_mlx.mlx, ft_update_env, &data_mlx);
	mlx_set_cursor_mode(data_mlx.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(data_mlx.mlx);
	free_data_mlx(&data_mlx, 4);
	return (0);
}
