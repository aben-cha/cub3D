/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:01:13 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/02 18:03:22 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_wait_move_animation(void *d)
{
	t_data		*data;
	t_animation	*anim;

	data = (t_data *)d;
	anim = data->animation;
	if (anim->delay_counter_wait >= anim->frame_delay_wait)
	{
		if (anim->image)
			mlx_delete_image(data->mlx, anim->image);
		anim->image = mlx_texture_to_image(data->mlx,
				anim->textures_wait[anim->current_frame_wait]);
		if (!anim->image)
		{
			free_array(data->map->arr_map);
			free_data(data, 1);
			print_error("Failed to convert texture to image for frame");
		}
		mlx_image_to_window(data->mlx, anim->image, 200, 184);
		anim->current_frame_wait = (anim->current_frame_wait + 1)
			% NUM_IMAGES_WAIT;
		anim->delay_counter_wait = 0;
	}
	anim->delay_counter_wait++;
}

void	ft_shoot_move_animation(void *d)
{
	t_data		*data;
	t_animation	*anim;

	data = (t_data *)d;
	anim = data->animation;
	if (anim->delay_counter >= anim->frame_delay)
	{
		if (anim->image)
			mlx_delete_image(data->mlx, anim->image);
		anim->image = mlx_texture_to_image(data->mlx,
				anim->textures_shot[anim->current_frame]);
		if (!anim->image)
		{
			free_array(data->map->arr_map);
			free_data(data, 1);
			print_error("Failed to convert texture to image for frame");
		}
		mlx_image_to_window(data->mlx, anim->image, 200, 184);
		anim->current_frame = (anim->current_frame + 1)
			% NUM_IMAGES_SHOT;
		anim->delay_counter = 0;
	}
	anim->delay_counter++;
}

void	ft_load_move_animation(void *d)
{
	t_data		*data;
	t_animation	*anim;

	data = (t_data *)d;
	anim = data->animation;
	if (anim->delay_counter >= anim->frame_delay)
	{
		if (anim->image)
			mlx_delete_image(data->mlx, anim->image);
		anim->image = mlx_texture_to_image(data->mlx,
				anim->textures_load[anim->current_frame]);
		if (!anim->image)
		{
			free_array(data->map->arr_map);
			free_data(data, 1);
			print_error("Failed to convert texture to image for frame");
		}
		mlx_image_to_window(data->mlx, anim->image, 200, 184);
		usleep(90000);
		anim->current_frame = (anim->current_frame + 1)
			% NUM_IMAGES_LOAD;
		anim->delay_counter = 0;
	}
	anim->delay_counter++;
}
