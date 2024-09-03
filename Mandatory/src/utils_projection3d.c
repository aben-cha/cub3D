/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_projection3d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:40:06 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 23:20:05 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_color(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	ft_floor(t_data *data, int x, int start_y)
{
	int			j;
	uint32_t	floorcolor;

	floorcolor = ft_color(data->element.floor_color.red, \
						data->element.floor_color.green, \
						data->element.floor_color.blue, 255);
	j = start_y;
	while (j < data->mlx->height)
	{
		if (j >= 0 && j < data->mlx->height)
		{
			if (x >= 0 && x < data->mlx->width)
				mlx_put_pixel(data->player->img_player, x, j, floorcolor);
		}
		j++;
	}
}

void	ft_ceil(t_data *data, int x, int end_y)
{
	int			j;
	uint32_t	ceilcolor;

	ceilcolor = ft_color(data->element.ceiling_color.red, \
						data->element.ceiling_color.green, \
						data->element.ceiling_color.blue, 255);
	j = 0;
	while (j < end_y)
	{
		if (j >= 0 && j < data->mlx->height)
		{
			if (x >= 0 && x < data->mlx->width)
				mlx_put_pixel(data->player->img_player, x, j, ceilcolor);
		}
		j++;
	}
}

uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	int	index;

	if (x < 0 || (uint32_t)x >= texture->width || y < 0 || (uint32_t)y >= texture->height)
		return (0);
	index = (y * texture->width) + x;
	return (((uint32_t *)texture->pixels)[index]);
}
