/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:12:39 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/03 10:55:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	handle_space(char *s, int *i, int *j)
{
	*i = 0;
	*j = ft_strlen(s) - 1;
	if (*j && s[*j] == '\n')
		(*j)--;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	while (*j && s[*j] && (s[*j] == ' '))
		(*j)--;
}

int	check_wall(char *s, char c)
{
	while (s && *s)
	{
		while (*s && *s == ' ')
			s++;
		if (*s && *s != '\n' && *s != c)
			return (1);
		if (*s)
			s++;
	}
	return (0);
}

int	another_char(char *s, char *ptr)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_check_line(ptr, s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_adjacent(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (++y < data->map->height - 1)
	{
		x = 0;
		while (++x < data->map->width - 1)
		{
			if (!another_char(data->map->arr_map[y], "01NSEWDC "))
				return (free_array(data->map->arr_map), free_data(data, 1),
					print_error("another char exist"), 1);
			if (map[y][x] == '0' || map[y][x] == data->player->isfacing
				|| map[y][x] == 'D')
			{
				if (map[y][x + 1] == 32 || map[y][x - 1] == 32
					|| map[y - 1][x] == 32 || map[y + 1][x] == 32)
					return (free_array(data->map->arr_map),
						free_data(data, 1), 1);
			}
		}
	}
	return (0);
}

void	set_element(t_data *data, char *s, int *size, char c)
{
	int	i;

	i = 0;
	handle_space(s, &i, size);
	if (s[0] == '\n' || s[i] == '\n')
	{
		if (data->texturel)
			ft_lstclear(&data->texturel);
		free_data(data, 0);
		print_error("Invalid Path.");
	}
	ft_lstadd_back(&data->texturel,
		ft_lstnew(ft_substr(s, i, *size - i + 1), c));
}
