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

#include"../include/cub3d.h"


void rays(t_data *data, float ray_angle, int color)
{
	float	centerX;
	float	centerY;
	float	x1;
	float	y1;
	centerX	= data->player->x;
	centerY	= data->player->y;
	x1 = centerX + cos(ray_angle) * 90;
	y1 = centerY + sin(ray_angle) * 90;
	draw_line(data, centerX, centerY, x1, y1, color);
}

void	ft_rays_where_is_facing(t_ray *ray, float rayangle)
{
	ray->ray_is_down = rayangle > 0 && rayangle < M_PI;
	ray->ray_is_up = !ray->ray_is_down;
	ray->ray_is_right = rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI;
	ray->ray_is_left = !ray->ray_is_right;
}

void	ft_cast_all_rays(t_data	*data, int color)
{
	int		i;
	float	rayangle;
	t_ray	*ray;
	t_ray	horizontal;
	t_ray	vertical;

	i =	0;
	rayangle = data->player->rotationAngle - (FOV_ANGLE / 2);
	while (i < NBR_RAYS)
	{
		ray = malloc(sizeof(t_ray));
		rayangle = ft_normalizeangle(rayangle);
		ft_rays_where_is_facing(ray, rayangle);
		horizontal = ft_rays_horizontal(data, ray, rayangle);
		vertical = ft_rays_vertical(data, ray, rayangle);
		ft_rays_where_is_facing(&horizontal, rayangle);
		ft_rays_where_is_facing(&vertical, rayangle);
		float d_h = sqrtf(pow(horizontal.dx, 2) + pow(horizontal.dy, 2));
		float d_v = sqrtf(pow(vertical.dx, 2) + pow(vertical.dy, 2));
		if (d_h <= d_v)
			ft_projection3D(data, i, 1, &horizontal, (d_h * cos(rayangle - data->player->rotationAngle)));
		else
			ft_projection3D(data, i, 0, &vertical, (d_v * cos(rayangle - data->player->rotationAngle)));
		rayangle += FOV_ANGLE / NBR_RAYS;
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

t_ray	ft_rays_horizontal(t_data *data, t_ray *ray, float ray_angle)
{
	float	xstep,ystep;
	float	x_intercept,y_intercept;
	
	y_intercept	= floor(data->player->y	/TILE_SIZE)	*TILE_SIZE;
	if (ray->ray_is_down == true)
		y_intercept	+= TILE_SIZE;
	x_intercept	= data->player->x + (y_intercept - data->player->y) / tan(ray_angle);
	ystep = TILE_SIZE;
	if (ray->ray_is_up == true)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray_angle);
	if (ray->ray_is_left == true && xstep > 0)
		xstep *= -1;
	if (ray->ray_is_right == true && xstep < 0)
		xstep *= -1;
	float new_x	= x_intercept;
	float new_y	= y_intercept;
	while (1)
	{
		if (ft_check_wall(data, new_x, new_y - (ray->ray_is_up ? 1 : 0)) == 1)
			break ;
		else
		{
			new_x += xstep;
			new_y += ystep;
		}
	}
	float dx;
	float dy;
	dx = new_x - data->player->x;
	dy = new_y - data->player->y;
	return (t_ray){dx, dy, new_x, new_y};
}

t_ray	 ft_rays_vertical(t_data *data, t_ray *ray, float ray_angle)
{
	float xstep,ystep;
	float x_intercept,y_intercept;
	
	x_intercept = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_is_right == true)
		x_intercept += TILE_SIZE;
	y_intercept = data->player->y + (x_intercept - data->player->x) * tan(ray_angle);
	xstep = TILE_SIZE;
	if (ray->ray_is_left == true)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray_angle);
	if (ray->ray_is_up == true && ystep > 0)
		ystep *= -1;
	if (ray->ray_is_down == true && ystep < 0)
		ystep *= -1;
	float new_x = x_intercept;
	float new_y	= y_intercept;
	while (1)
	{
		if (ft_check_wall(data,new_x -	(ray->ray_is_left ?1:0 ), new_y)==1)
			break;
		else
		{
			new_x +=xstep;
			new_y +=ystep;
		}
	}
	float dx;
	float dy;
	dx = new_x - data->player->x;
	dy = new_y - data->player->y;
	return (t_ray){dx,dy,new_x,new_y};
}
