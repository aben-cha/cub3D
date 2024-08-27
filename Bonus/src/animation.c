/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:55:30 by ataoufik          #+#    #+#             */
/*   Updated: 2024/08/14 15:08:29 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

void ft_wait_move_animation(void  *d)
{
    t_data *data = (t_data *)d;
    t_animation *anim = data->animation;

    if (anim->delay_counter_wait >= anim->frame_delay_wait)
    {
        if (anim->image)
            mlx_delete_image(data->mlx, anim->image);

        anim->image = mlx_texture_to_image(data->mlx, anim->textures_wait[anim->current_frame_wait]);
        if (!anim->image)
        {
            fprintf(stderr, "Failed to convert texture to image for frame %d\n", anim->current_frame_wait);
            exit(EXIT_FAILURE);
        }

        mlx_image_to_window(data->mlx, anim->image, 200, 184);

        anim->current_frame_wait = (anim->current_frame_wait + 1) % NUM_IMAGES_WAIT;
        anim->delay_counter_wait = 0;
    }

    anim->delay_counter_wait++;
}


void ft_shoot_move_animation(t_data *data)
{
    t_animation *anim = data->animation;

    if (anim->delay_counter >= anim->frame_delay)
    {
        if (anim->image)
            mlx_delete_image(data->mlx, anim->image);

        anim->image = mlx_texture_to_image(data->mlx, anim->textures_shot[anim->current_frame]);
        if (!anim->image)
        {
            fprintf(stderr, "Failed to convert texture to image for frame %d\n", anim->current_frame);
            exit(EXIT_FAILURE);
        }

        mlx_image_to_window(data->mlx, anim->image, 200, 184);

        anim->current_frame = (anim->current_frame + 1) % NUM_IMAGES_SHOT;
        anim->delay_counter = 0;
    }

    anim->delay_counter++;
    
}
