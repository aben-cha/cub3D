/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_projection3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:41:31 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/04 22:39:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_set_texteur(t_data *data, float wallheight, t_pos *t1, int offset_x)
{
	int				top;
	mlx_texture_t	*wall_tex;
	uint32_t		texcolor;
	int				y;

	top = (WINDOW_HEIGHT / 2) - (wallheight / 2);
	wall_tex = ft_texteur_valid(data);
	y = ((t1->y - top) * wall_tex->width) / wallheight;
	texcolor = get_pixel_color(wall_tex, offset_x, y);
	if (t1->x >= 0 && t1->x < data->mlx->width)
		mlx_put_pixel(data->player->img_player, t1->x, t1->y, texcolor);
}

float	ft_init_wallheight(t_data *data, float raydistance)
{
	float	d_projectplan;
	float	wallheight;

	d_projectplan = ((float)data->mlx->width / 2.0)
		/ tan((60 * (M_PI / 180)) / 2.0);
	wallheight = ((float)TILE_SIZE / raydistance) * d_projectplan;
	return (wallheight);
}

mlx_texture_t	*ft_texteur_valid(t_data *data)
{
	mlx_texture_t	*wall_tex;

	wall_tex = NULL;
	if (data->n == 1)
		wall_tex = data->texture->wall_tex_n;
	else if (data->n == 2)
		wall_tex = data->texture->wall_tex_s;
	else if (data->n == 3)
		wall_tex = data->texture->wall_tex_e;
	else if (data->n == 4)
		wall_tex = data->texture->wall_tex_w;
	return (wall_tex);
}
