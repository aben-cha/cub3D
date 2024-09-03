/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:16:25 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 22:45:13 by ataoufik         ###   ########.fr       */
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

void	load_png(t_data *data, mlx_texture_t **mlx_texture, char *path)
{
	*mlx_texture = mlx_load_png(path);
	if (!*mlx_texture)
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
	load_png(data, &data->texture->walltexteur_d, "./texture/door.png");
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

void	mouse(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->player->rotangle += (float)(x
			- (WINDOW_WHIDTH / 2)) / (WINDOW_HEIGHT / 2);
	mlx_set_mouse_pos(data->mlx, WINDOW_WHIDTH / 2, WINDOW_HEIGHT / 2);
	ft_player(data);
}
