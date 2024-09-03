/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:06:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 18:44:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_data(t_data *data, int flag)
{
	if (flag)
		ft_lstclear(&data->texturel);
	ft_lstclear(&data->list);
	free(data->map);
	free(data->player);
	free(data->texture);
	free(data->animation);
}

void	delete_textures(mlx_texture_t **textures, int i)
{
	while (--i)
		mlx_delete_texture(textures[i]);
}

void	free_data_mlx(t_data *data, int flag)
{
	mlx_delete_texture(data->texture->walltexteur_n);
	mlx_delete_texture(data->texture->walltexteur_e);
	mlx_delete_texture(data->texture->walltexteur_s);
	mlx_delete_texture(data->texture->walltexteur_w);
	if (flag == 2 || flag == 3 || flag == 4)
	{
		mlx_delete_image(data->mlx, data->player->img_player);
		mlx_delete_image(data->mlx, data->map->img_map);
	}
	if (flag == 3 || flag == 4)
	{
		delete_textures(data->animation->textures_wait, N_IMAGES_WAIT + 1);
		delete_textures(data->animation->textures_shot, N_IMAGES_SHOT + 1);
		delete_textures(data->animation->textures_load, N_IMAGES_LOAD);
	}
	free_array(data->map->arr_map);
	free_data(data, 1);
	if (flag == 1 || flag == 2 || flag == 3)
		mlx_terminate(data->mlx);
}
