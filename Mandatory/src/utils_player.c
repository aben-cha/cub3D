/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:14:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/02 16:03:22 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void rest_image(mlx_image_t *image)
{
    uint32_t x = 0;
    uint32_t y = 0;
    while (x < image->width)
    {
        y = 0;
        while (y < image->height)
        {
            mlx_put_pixel(image, x, y, 0);
            y++;
        }
        x++;
    }
}

int	ft_check_arr(t_data *data, t_pos *p1, t_pos *point)
{
	int	x_map;
	int	y_map;

	x_map = floor((p1->x + point->x) / TILE_SIZE);
	y_map = floor((p1->y + point->y) / TILE_SIZE);
	if (x_map >= 0 && x_map < data->map->width
		&& y_map >= 0 && y_map < data->map->height)
	{
		if (data->map->arr_map[y_map][x_map] == '1')
			return (1);
	}
	return (0);
}
