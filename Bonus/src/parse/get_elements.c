/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:16:11 by aben-cha          #+#    #+#             */
/*   Updated: 2024/08/02 19:16:11 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int     set_color(t_color *color, char *color_path)
{
    int i;
    int size;
    char **type;
    
    i = -1;
    size = ft_strlen(color_path);
    if (color_path[0] == ',' || (size > 0 && color_path[size - 1] == ','))
        return (1);
    while (color_path[++i])
    {
        if ((!ft_isdigit(color_path[i]) && color_path[i] != ',') ||
            (color_path[i] == ',' && color_path[i + 1] == ','))
            return (1);
    }
    type = ft_split(color_path, ',');
    if (!type)
        return (free(color_path), 1);
    i = -1;
    while (type && type[++i])
    {
        if (ft_atoi(type[i]) > 255 || i == 3)
            return (1);
    }
    (color->red = ft_atoi(type[0]), color->green = ft_atoi(type[1]),
        color->blue = ft_atoi(type[2]));
    return (free(color_path), free_array(type), 0);
}

void    set_element(t_data *data, char *s, int *size, char c)
{
    int i;
    
    i = 0;
    handle_space(s, &i, size);
    if (s[0] == '\n' || s[i] == '\n')
    {
        if (data->texturel)
            ft_lstclear(&data->texturel);
        free_data(data, 0);
        print_error("Invalid Path.");
    }
    ft_lstadd_back(&data->texturel, ft_lstnew(ft_substr(s, i, *size - i + 1), c));
}

void    get_element(t_data *data, char *s, int *size, int *i)
{
    if (!ft_strncmp(s, "NO", 2))
        (set_element(data, s + 2, size, 'N'), (*i)++);
    else if (!ft_strncmp(s, "SO", 2))
        (set_element(data, s + 2, size, 'S'), (*i)++);
    else if (!ft_strncmp(s, "WE", 2))
        (set_element(data, s + 2, size, 'W'), (*i)++);
    else if (!ft_strncmp(s, "EA", 2))
        (set_element(data, s + 2, size, 'E'), (*i)++);
    else if (!ft_strncmp(s, "F", 1))
        (set_element(data, s + 1, size, 'F'), (*i)++);
    else if (!ft_strncmp(s, "C", 1))
        (set_element(data, s + 1, size, 'C'), (*i)++);
}

int     get_color(t_element *element, char *color, char type)
{
    if (type == 'F')
    {
        if (set_color(&element->floor_color, color))
            return (1);
    }
    else if (type == 'C')
    {
        if (set_color(&element->ceiling_color, color))
            return (1);
    }
    return (0);
}

void    setup_colors(t_data *data)
{
    t_list *head;
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

t_list  *get_map(t_data *data)
{
    char	*s;
    t_list	*ptr;
    
    ptr = NULL;
    while (data->list)
    {
        s = data->list->content;
        handle_space(s, &data->j, &data->size);
        get_element(data, s + data->j, &data->size, &data->i);
        if (data->i == 6 || s[data->j] == '1')
        {   
            if (data->list->next)
                ptr = data->list->next;
            while (ptr && ft_strlen(ptr->content) == 1)
                ptr = ptr->next;
            break;
        }
        data->list = data->list->next;
    }
    // setup_textures_colors(data);
    setup_colors(data);
	return (ptr);
}
