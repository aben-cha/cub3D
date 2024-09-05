/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:16:25 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/05 15:18:39 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	convert_abgr_to_rgba(t_data *data, mlx_texture_t *texture)
{
	t_con_var	vars;

	if (!texture || !texture->pixels)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("Texture or its pixels are not available.");
	}
	vars.i = -1;
	vars.pixels = texture->pixels;
	while (++vars.i < texture->width * texture->height)
	{
		vars.a = vars.pixels[4 * vars.i + 0];
		vars.b = vars.pixels[4 * vars.i + 1];
		vars.g = vars.pixels[4 * vars.i + 2];
		vars.r = vars.pixels[4 * vars.i + 3];
		vars.pixels[4 * vars.i + 0] = vars.r;
		vars.pixels[4 * vars.i + 1] = vars.g;
		vars.pixels[4 * vars.i + 2] = vars.b;
		vars.pixels[4 * vars.i + 3] = vars.a;
	}
}

void	free_textures(t_data *data, t_number *number)
{
	if (number->n == 1)
		mlx_delete_texture(data->texture->wall_tex_n);
	if (number->s == 1)
		mlx_delete_texture(data->texture->wall_tex_s);
	if (number->e == 1)
		mlx_delete_texture(data->texture->wall_tex_e);
	if (number->w == 1)
		mlx_delete_texture(data->texture->wall_tex_w);
	if (number->d == 1)
		mlx_delete_texture(data->texture->wall_tex_d);
	print_error("load png.");
}

int	load_png(t_data *data, mlx_texture_t **mlx_texture, char *path, char c)
{
	*mlx_texture = mlx_load_png(path);
	if (!*mlx_texture)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		if (c == 'D')
			data->number.d = 0;
		if (c == 'N')
			data->number.n = 0;
		if (c == 'S')
			data->number.s = 0;
		if (c == 'E')
			data->number.e = 0;
		if (c == 'W')
			data->number.w = 0;
		free_textures(data, &data->number);
		return (1);
	}
	convert_abgr_to_rgba(data, *mlx_texture);
	return (0);
}

void	load_textures(t_data *data, t_list *head)
{
	load_png(data, &data->texture->wall_tex_d, "./texture/door.png", 'D');
	while (head)
	{
		if (head->c == 'N')
		{
			data->number.n = 1;
			load_png(data, &data->texture->wall_tex_n, head->content, head->c);
		}
		else if (head->c == 'S')
		{
			data->number.s = 1;
			load_png(data, &data->texture->wall_tex_s, head->content, head->c);
		}
		else if (head->c == 'E')
		{
			data->number.e = 1;
			load_png(data, &data->texture->wall_tex_e, head->content, head->c);
		}
		else if (head->c == 'W')
		{
			data->number.w = 1;
			load_png(data, &data->texture->wall_tex_w, head->content, head->c);
		}
		head = head->next;
	}
}

void	loading_sprites(t_data *data)
{
	static int	i;

	if (data->counter == 0)
		ft_wait_move_animation(data);
	if (i > 5)
		i = 0;
	if (i == 5)
	{
		ft_load_move_animation(data);
		if (data->animation->current_frame == 36)
		{
			(1) && (i = 0, data->counter = 0);
			data->animation->current_frame = 0;
		}
	}
	if (data->counter != 0)
	{
		ft_shoot_move_animation(data);
		if (data->animation->current_frame == 13)
		{
			data->animation->current_frame = 0;
			i += data->counter;
			data->counter = 0;
		}
	}
}
