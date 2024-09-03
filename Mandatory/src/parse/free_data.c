/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:15:29 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 17:52:39 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	free_structs(t_data *data)
{
	free(data->map);
	free(data->player);
	free(data->texture);
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
	free_structs(data);
}

void	free_data_mlx(t_data *data, int flag)
{
	mlx_delete_texture(data->texture->walltexteur_n);
	mlx_delete_texture(data->texture->walltexteur_e);
	mlx_delete_texture(data->texture->walltexteur_s);
	mlx_delete_texture(data->texture->walltexteur_w);
	if (flag == 2)
		mlx_delete_image(data->mlx, data->player->img_player);
	free_array(data->map->arr_map);
	free_data(data, 1);
	if (flag == 1 || flag == 2)
		mlx_terminate(data->mlx);
}
