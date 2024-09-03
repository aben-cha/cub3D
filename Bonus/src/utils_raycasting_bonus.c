/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:11:04 by ataoufik          #+#    #+#             */
/*   Updated: 2024/09/03 10:56:47 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	ft_rays_where_is_facing(t_ray *ray, float rayangle)
{
	if (ray == NULL)
	{
		ft_putendl_fd("Error: ray is NULL", 2);
		exit(1);
	}
	ray->ray_is_down = rayangle > 0 && rayangle < M_PI;
	ray->ray_is_up = !ray->ray_is_down;
	ray->ray_is_right = rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI;
	ray->ray_is_left = !ray->ray_is_right;
}

void	ft_which_ray_used(t_data *data, t_ray *ver, t_ray *hor, int i)
{
	float	cdistance;
	float	d_h;
	float	d_v;

	d_h = sqrtf(pow(hor->dx, 2) + pow(hor->dy, 2));
	d_v = sqrtf(pow(ver->dx, 2) + pow(ver->dy, 2));
	if (d_h <= d_v)
	{
		cdistance = d_h * cos(data->rayangle - data->player->rotangle);
		data->distance = cdistance;
		ft_projection3d(data, i, 1, hor);
	}
	else
	{
		cdistance = d_v * cos(data->rayangle - data->player->rotangle);
		data->distance = cdistance;
		ft_projection3d(data, i, 0, ver);
	}
}

int	ft_find_wall_vertical(t_data *data, t_pos *new, t_pos *step, t_ray *ray)
{
	int	flag;
	int	n;

	n = 0;
	flag = 0;
	while (1)
	{
		if (ray->ray_is_left)
			n = 1;
		if (ft_check_wall(data, new->x - n, new->y) == 1)
			break ;
		else if (ft_check_wall(data, new->x - n, new->y) == 2)
		{
			flag = 1;
			break ;
		}
		else
		{
			new->x += step->x;
			new->y += step->y;
		}
	}
	return (flag);
}

int	ft_find_wall_horizontal(t_data *data, t_pos *new, t_pos *step, t_ray *ray)
{
	int	flag;
	int	n;

	n = 0;
	flag = 0;
	while (1)
	{
		if (ray->ray_is_up)
			n = 1;
		if (ft_check_wall(data, new->x, new->y - n) == 1)
			break ;
		else if (ft_check_wall(data, new->x, new->y - n) == 2)
		{
			flag = 1;
			break ;
		}
		else
		{
			new->x += step->x;
			new->y += step->y;
		}
	}
	return (flag);
}
