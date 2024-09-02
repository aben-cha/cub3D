/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:05:53 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/02 18:05:53 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	map(t_list *ptr, t_data *data)
{
	char	*s;
	int		i;
	int		len_s;
	int		min_w;

	min_w = ft_strlen((char *)ptr->content);
	data->map->width = min_w;
	while (ptr)
	{
		s = (char *)ptr->content;
		if ((int)ft_strlen(s) > min_w)
			data->map->width = ft_strlen(s);
		if (data->map->height == 0 || ptr->next == NULL)
		{
			if (check_wall(s, '1'))
				return (free_data(data, 1), 0);
		}
		handle_space(s, &i, &len_s);
		if (s[i] != '1' || (len_s > 0 && s[len_s] != '1'))
			return (free_data(data, 1), 0);
		data->map->height++;
		ptr = ptr->next;
	}
	return (1);
}

void	allocate_new_map(t_data *data)
{
	data->map->arr_map = malloc(sizeof(char *) * (data->map->height + 1));
	if (!data->map->arr_map)
	{
		free_data(data, 1);
		print_error("Malloc Failed.");
	}
}

void	join_space(t_data *data, int size, int *i)
{
	if (size < data->map->width)
	{
		data->j = 0;
		while (++(data->j) <= (data->map->width - size))
		{
			data->map->arr_map[*i] = ft_free(data->map->arr_map[*i],
					ft_strdup(" "));
			if (!data->map->arr_map[*i])
			{
				free_memory(data->map->arr_map, *i);
				free_data(data, 1);
				print_error("Malloc Failed.");
			}
		}
	}
}

int	set_map(t_list *ptr, t_data *data, int size)
{
	data->i = -1;
	allocate_new_map(data);
	while (++(data->i) < data->map->height)
	{
		if (!ptr)
			return (free_memory(data->map->arr_map, data->i), 1);
		size = ft_strlen((char *)ptr->content);
		if (data->i == data->map->height - 1)
		{
			if (((char *)ptr->content)[size - 1] == '\n')
				return (free_memory(data->map->arr_map, data->i),
					free_data(data, 1),
					print_error("the map should be at the last"), 1);
			if (((char *)ptr->content)[size - 1] != ' ')
				size++;
		}
		data->map->arr_map[data->i] = ft_substr((char *)ptr->content, 0,
				size - 1);
		if (!data->map->arr_map[data->i])
			return (free_memory(data->map->arr_map, data->i), 1);
		join_space(data, size, &data->i);
		ptr = ptr->next;
	}
	return (data->map->arr_map[data->i] = NULL, 0);
}

int	is_valid_map(t_data *data)
{
	t_list	*head;

	if (!all_element_exist(data))
		return (1);
	head = get_map(data);
	if (!head)
		return (free_data(data, 1), print_error("Map doesn't exist."), 1);
	if (!map(head, data))
		return (print_error("The map should closed by walls."), 1);
	if (set_map(head, data, 0))
		return (free_data(data, 1), print_error("Malloc Failed."), 1);
	if (position_of_player(data, data->map->arr_map))
		return (print_error("Invalid position of player."), 1);
	if (is_adjacent(data, data->map->arr_map))
		return (print_error("Player out."), 1);
	return (0);
}
