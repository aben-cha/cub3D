/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:32:59 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/02 17:06:24 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*ft_png_name(char *str1, char *str2, int n)
{
	char	*str;
	char	*index;
	char	*temp;

	index = ft_itoa(n);
	temp = ft_strjoin(str1, index);
	str = ft_strjoin(temp, str2);
	return (str);
}

void	ft_load_imges_wait(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = 0;
	while (i < NUM_IMAGES_WAIT)
	{
		str = ft_png_name(str1, ".png", i + 1);
		data->animation->textures_wait[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_wait[i])
		{
			fprintf(stderr, "Failed to load image wait %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_load_imges_shot(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = 0;
	while (i < NUM_IMAGES_SHOT)
	{
		str = ft_png_name(str1, ".png", i + 1);
		data->animation->textures_shot[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_shot[i])
		{
			fprintf(stderr, "Failed to load image shot %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_load_imges_load(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = 0;
	while (i < NUM_IMAGES_LOAD)
	{
		str = ft_png_name(str1, ".png", i + 1);
		data->animation->textures_load[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_load[i])
		{
			fprintf(stderr, "Failed to load image  load %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	load_images(t_data *data)
{
	data->animation->current_frame_wait = 0;
	data->animation->frame_delay_wait = 9;
	data->animation->delay_counter_wait = 0;
	data->animation->current_frame = 0;
	data->animation->frame_delay = 3;
	data->animation->frame_delay_load = 6;
	data->animation->delay_counter = 3;
	ft_load_imges_wait(data, "png/wait/wait_");
	ft_load_imges_shot(data, "png/shot/shot_");
	ft_load_imges_load(data, "png/load/load_");
}
