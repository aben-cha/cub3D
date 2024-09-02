/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:14 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/02 18:29:49 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	load_png(t_data *data, mlx_texture_t **mlx_texture, char *path)
{
	*mlx_texture = mlx_load_png(path);
	if (!mlx_texture)
	{
		free_array(data->map->arr_map);
		free_data(data, 1);
		print_error("Error load png.");
	}
	convert_abgr_to_rgba(data, *mlx_texture);
}

void	load_textures(t_data *data)
{
	t_list	*head;

	head = data->texturel;
	while (head)
	{
		if (head->c == 'N')
			load_png(data, &data->texture->walltexteur_n, head->content);
		else if (head->c == 'S')
			load_png(data, &data->texture->walltexteur_s, head->content);
		else if (head->c == 'E')
			load_png(data, &data->texture->walltexteur_e, head->content);
		else if (head->c == 'W')
			load_png(data, &data->texture->walltexteur_w, head->content);
		head = head->next;
	}
}
