/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection3d_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:57:48 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/04 22:39:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

uint32_t	ft_width_texteur(t_data *data)
{
	uint32_t	width;

	width = 0;
	if (data->flagdoor == 1)
		width = data->texture->wall_tex_d->width;
	else if (data->n == 1)
		width = data->texture->wall_tex_n->width;
	else if (data->n == 2)
		width = data->texture->wall_tex_s->width;
	else if (data->n == 3)
		width = data->texture->wall_tex_e->width;
	else if (data->n == 4)
		width = data->texture->wall_tex_w->width;
	return (width);
}

int	ft_init_offset(t_data *data, t_ray *ray, int sig)
{
	int			offset_x;
	uint32_t	width;

	width = ft_width_texteur(data);
	if (sig == 0)
		offset_x = (int)ray->y_intercept % width;
	else
		offset_x = (int)ray->x_intercept % width;
	return (offset_x);
}

void	ft_prepare_projection(t_data *data, float x, float raydis, t_pos *t1)
{
	float	wallheight;
	int		top_pixel;

	t1->x = x;
	wallheight = ft_init_wallheight(data, raydis);
	top_pixel = (WINDOW_HEIGHT / 2) - (wallheight / 2);
	t1->y = top_pixel;
	ft_ceil(data, x, top_pixel);
	ft_floor(data, x, top_pixel + wallheight);
}

void	ft_draw_projection(t_data *data, t_pos t1, int sig, t_ray *ray)
{
	int		offset_x;
	float	wallheight;
	int		top_pixel;

	wallheight = ft_init_wallheight(data, data->distance);
	top_pixel = (WINDOW_HEIGHT / 2) - (wallheight / 2);
	data->flagdoor = ray->flag;
	while (t1.y < (wallheight + top_pixel))
	{
		if (t1.y >= 0 && t1.y < WINDOW_HEIGHT)
		{
			if (sig == 0 && ray->ray_is_left)
				data->n = 1;
			else if (sig == 0 && ray->ray_is_right)
				data->n = 2;
			else if (sig != 0 && ray->ray_is_up)
				data->n = 3;
			else
				data->n = 4;
			offset_x = ft_init_offset(data, ray, sig);
			ft_set_texteur(data, wallheight, &t1, offset_x);
		}
		t1.y++;
	}
}

void	ft_projection3d(t_data *data, float x, int sig, t_ray *ray)
{
	t_pos	t1;

	ft_prepare_projection(data, x, data->distance, &t1);
	ft_draw_projection(data, t1, sig, ray);
}
