/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_projection3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:43:31 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/01 19:45:30 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_set_texteur(t_data *data, float wallheight, t_pos *t1, int offset_x)
{
	int				top;
	mlx_texture_t	*walltexteur;
	uint32_t		texcolor;
	int				y;

	top = (WINDOW_HEIGHT / 2) - (wallheight / 2);
	walltexteur = ft_texteur_valid(data);
	if (data->flagdoor == 1)
	{
		y = ((t1->y - top) * data->texture->walltexteur_d->width) / wallheight;
		texcolor = get_pixel_color(data->texture->walltexteur_d, offset_x, y);
		if (t1->x >= 0 && t1->x < data->mlx->width)
			mlx_put_pixel(data->player->img_player, t1->x, t1->y, texcolor);
	}
	else
	{
		y = ((t1->y - top) * walltexteur->width) / wallheight;
		texcolor = get_pixel_color(walltexteur, offset_x, y);
		if (t1->x >= 0 && t1->x < data->mlx->width)
			mlx_put_pixel(data->player->img_player, t1->x, t1->y, texcolor);
	}
}

float	ft_init_wallheight(t_data *data, float raydistance)
{
	float	d_projectplan;
	float	wallheight;

	d_projectplan = ((float)data->mlx->width / 2.0) / tan(FOV_ANGLE / 2.0);
	wallheight = ((float)TILE_SIZE / raydistance) * d_projectplan;
	return (wallheight);
}

mlx_texture_t	*ft_texteur_valid(t_data *data)
{
	mlx_texture_t	*walltexteur;

	if (data->n == 1)
		walltexteur = data->texture->walltexteur_n;
	else if (data->n == 2)
		walltexteur = data->texture->walltexteur_s;
	else if (data->n == 3)
		walltexteur = data->texture->walltexteur_e;
	else if (data->n == 4)
		walltexteur = data->texture->walltexteur_w;
	return (walltexteur);
}
