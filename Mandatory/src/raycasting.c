/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 raycasting.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: ataoufik <ataoufik@student.42.fr>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/07/28 16:28:39 by ataoufik		   #+#	  #+#			  */
/*	 Updated: 2024/08/26 19:04:30 by ataoufik		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_cast_all_rays(t_data *data)
{
	t_ray	*ray;
	t_ray	horizontal;
	t_ray	vertical;
	int		i;
	float	rayangle;

	i = 0;
	rayangle = data->player->rotangle - ((60 * (M_PI / 180)) / 2);
	while (i < NBR_RAYS)
	{
		ray = malloc(sizeof(t_ray));
		if (!ray)
			(free_data_mlx(data, 2), exit(1));
		rayangle = ft_normalizeangle(rayangle);
		ft_rays_where_is_facing(ray, rayangle);
		horizontal = ft_rays_horizontal(data, ray, rayangle);
		vertical = ft_rays_vertical(data, ray, rayangle);
		ft_rays_where_is_facing(&horizontal, rayangle);
		ft_rays_where_is_facing(&vertical, rayangle);
		data->rayangle = rayangle;
		ft_which_ray_used(data, &vertical, &horizontal, i);
		rayangle += (60 * (M_PI / 180)) / NBR_RAYS;
		free(ray);
		i++;
	}
}

float	ft_normalizeangle(float rayangle)
{
	rayangle = fmod(rayangle, 2.0 * M_PI);
	if (rayangle < 0)
		rayangle += 2.0 * M_PI;
	return (rayangle);
}

t_ray	ft_rays_horizontal(t_data *data, t_ray *ray, float rangle)
{
	t_pos	step;
	t_pos	hitwall;
	t_pos	new;
	t_pos	d;

	hitwall.y = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_is_down == true)
		hitwall.y += TILE_SIZE;
	hitwall.x = data->player->x + (hitwall.y - data->player->y) / tan(rangle);
	step.y = TILE_SIZE;
	if (ray->ray_is_up == true)
		step.y *= -1;
	step.x = TILE_SIZE / tan(rangle);
	if (ray->ray_is_left == true && step.x > 0)
		step.x *= -1;
	if (ray->ray_is_right == true && step.x < 0)
		step.x *= -1;
	new.x = hitwall.x;
	new.y = hitwall.y;
	ft_find_wall_hor(data, &new, &step, ray);
	d.x = new.x - data->player->x;
	d.y = new.y - data->player->y;
	return ((t_ray){d.x, d.y, new.x, new.y, 0, 0, 0, 0, 0});
}

t_ray	ft_rays_vertical(t_data *data, t_ray *ray, float rangle)
{
	t_pos	step;
	t_pos	hitwall;
	t_pos	new;
	t_pos	d;

	hitwall.x = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_is_right == true)
		hitwall.x += TILE_SIZE;
	hitwall.y = data->player->y + (hitwall.x - data->player->x) * tan(rangle);
	step.x = TILE_SIZE;
	if (ray->ray_is_left == true)
		step.x *= -1;
	step.y = TILE_SIZE * tan(rangle);
	if (ray->ray_is_up == true && step.y > 0)
		step.y *= -1;
	if (ray->ray_is_down == true && step.y < 0)
		step.y *= -1;
	new.x = hitwall.x;
	new.y = hitwall.y;
	ft_find_wall_ver(data, &new, &step, ray);
	d.x = new.x - data->player->x;
	d.y = new.y - data->player->y;
	return ((t_ray){d.x, d.y, new.x, new.y, 0, 0, 0, 0, 0});
}
