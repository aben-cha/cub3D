/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:32:59 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/06 15:57:14 by aben-cha         ###   ########.fr       */
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
	free(index);
	str = ft_free(temp, str2);
	return (str);
}

void	ft_load_imges_wait(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = 0;
	while (i < N_IMAGES_WAIT)
	{
		str = ft_png_name(str1, ".png", i + 1);
		if (!str)
		{
			free_data_mlx(data, 2);
			print_error("Failed to load image.");
		}
		data->animation->textures_wait[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_wait[i])
		{
			delete_textures(data->animation->textures_wait, i);
			free_data_mlx(data, 2);
			print_error("Failed to load texture.");
		}
		i++;
	}
}

void	ft_load_imges_shot(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = 0;
	while (i < N_IMAGES_SHOT)
	{
		str = ft_png_name(str1, ".png", i + 1);
		if (!str)
		{
			delete_textures(data->animation->textures_wait, N_IMAGES_WAIT);
			free_data_mlx(data, 2);
			print_error("Failed to load image.");
		}
		data->animation->textures_shot[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_shot[i])
		{
			delete_textures(data->animation->textures_shot, i);
			delete_textures(data->animation->textures_wait, N_IMAGES_WAIT);
			free_data_mlx(data, 2);
			print_error("Failed to load texture.");
		}
		i++;
	}
}

void	ft_load_imges_load(t_data *data, char *str1)
{
	char	*str;
	int		i;

	i = -1;
	while (++i < N_IMAGES_LOAD)
	{
		str = ft_png_name(str1, ".png", i + 1);
		if (!str)
		{
			delete_textures(data->animation->textures_wait, N_IMAGES_WAIT);
			delete_textures(data->animation->textures_shot, N_IMAGES_SHOT);
			free_data_mlx(data, 2);
			print_error("Failed to load image.");
		}
		data->animation->textures_load[i] = mlx_load_png(str);
		free(str);
		if (!data->animation->textures_load[i])
		{
			delete_textures(data->animation->textures_load, i);
			delete_textures(data->animation->textures_shot, N_IMAGES_SHOT);
			delete_textures(data->animation->textures_wait, N_IMAGES_WAIT);
			free_data_mlx(data, 2);
			print_error("Failed to load texture.");
		}
	}
}

void	load_images(t_data *data)
{
	data->animation->current_frame_wait = 0;
	data->animation->frame_delay_wait = 9;
	data->animation->delay_counter_wait = 0;
	data->animation->current_frame = 0;
	data->animation->frame_delay = 3;
	data->animation->delay_counter = 3;
	ft_load_imges_wait(data, "Bonus/png/wait/wait_");
	ft_load_imges_shot(data, "Bonus/png/shot/shot_");
	ft_load_imges_load(data, "Bonus/png/load/load_");
}
