/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:29 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/02 18:07:29 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	set_color(t_color *color, char *color_path, int i)
{
	int		size;
	char	**type;

	size = ft_strlen(color_path);
	if (color_path[0] == ',' || (size > 0 && color_path[size - 1] == ','))
		return (1);
	while (color_path[++i])
	{
		if ((!ft_isdigit(color_path[i]) && color_path[i] != ',')
			|| (color_path[i] == ',' && color_path[i + 1] == ','))
			return (1);
	}
	type = ft_split(color_path, ',');
	if (!type)
		return (free(color_path), 1);
	i = -1;
	while (type && type[++i])
	{
		if (ft_atoi(type[i]) > 255 || i == 3)
			return (free_memory(type, i), 1);
	}
	color->red = ft_atoi(type[0]);
	color->green = ft_atoi(type[1]);
	color->blue = ft_atoi(type[2]);
	return (free(color_path), free_array(type), 0);
}

void	get_element(t_data *data, char *s, int *size)
{
	if (!ft_strncmp(s, "NO", 2))
		(set_element(data, s + 2, size, 'N'));
	else if (!ft_strncmp(s, "SO", 2))
		(set_element(data, s + 2, size, 'S'));
	else if (!ft_strncmp(s, "WE", 2))
		(set_element(data, s + 2, size, 'W'));
	else if (!ft_strncmp(s, "EA", 2))
		(set_element(data, s + 2, size, 'E'));
	else if (!ft_strncmp(s, "F", 1))
		(set_element(data, s + 1, size, 'F'));
	else if (!ft_strncmp(s, "C", 1))
		(set_element(data, s + 1, size, 'C'));
}

int	get_color(t_element *element, char *color, char type)
{
	if (type == 'F')
	{
		if (set_color(&element->floor_color, color, -1))
			return (1);
	}
	else if (type == 'C')
	{
		if (set_color(&element->ceiling_color, color, -1))
			return (1);
	}
	return (0);
}

void	setup_colors(t_data *data)
{
	t_list	*head;

	if (!data->texturel)
		(free_data(data, 0), print_error("Invalid elements"));
	head = data->texturel;
	while (head)
	{
		if (get_color(&data->element, head->content, head->c))
		{
			free_data(data, 1);
			print_error("Invalid number of color.");
		}
		head = head->next;
	}
}

t_list	*get_map(t_data *data)
{
	char	*s;
	t_list	*ptr;
	t_list	*head;

	ptr = NULL;
	head = data->list;
	while (head)
	{
		s = head->content;
		handle_space(s, &data->j, &data->size);
		get_element(data, s + data->j, &data->size);
		if (s[data->j] == '1')
		{
			ptr = head;
			break ;
		}
		head = head->next;
	}
	setup_colors(data);
	return (ptr);
}
