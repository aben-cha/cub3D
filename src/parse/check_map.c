/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:16:37 by aben-cha          #+#    #+#             */
/*   Updated: 2024/08/02 19:16:37 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int     map(t_list *ptr, t_data *data)
{
    char *s;
    int i;
    int len_s;
    int min_width;

    if (check_wall(ptr->content, '1'))
        return (free_data(data, 1), ft_lstclear(&ptr), 0);
    if (ptr->next)
        ptr = ptr->next;
    min_width = ft_strlen((char *)ptr->content);
    data->map->width = min_width;
    while (ptr->next)
    {
        s = (char *)ptr->content;
        if ((int)ft_strlen((char *)ptr->content) > min_width)
            data->map->width = ft_strlen((char *)ptr->content);
        handle_space(s, &i, &len_s);
        if (s[i] != '1' || (len_s > 0 && s[len_s] != '1'))
            return (free_data(data, 1), ft_lstclear(&ptr), 0);
        data->map->height++;
        ptr = ptr->next;
    }
    if (check_wall(ptr->content, '1') || !ft_strncmp((char *)ptr->content, "\n", 1))
        return (free_data(data, 1), ft_lstclear(&ptr), 0);
    return (data->map->height += 2, 1);
}

int    set_map(t_list *ptr, t_data *data)
{
    int end;
    
    data->i = -1;
    data->map->arr_map = malloc(sizeof (char *) * (data->map->height + 1));
    if (!data->map->arr_map)
        return (ft_lstclear(&ptr), free_data(data, 1) , 1);
    while (++(data->i) < data->map->height)
    {
        data->map->arr_map[data->i] = ft_substr((char *)ptr->content, 0, ft_strlen((char *)ptr->content) - 1);
        if (!data->map->arr_map[data->i])
            return (free_memory(data->map->arr_map, data->i), ft_lstclear(&ptr), free_data(data, 1) , 1);
        if ((int)ft_strlen((char *)ptr->content) < data->map->width)
        {
            data->j = 0;
            end  = data->map->width - (int)ft_strlen((char *)ptr->content);
            while (++(data->j) <= end)
            {
                data->map->arr_map[data->i] = ft_free(data->map->arr_map[data->i], ft_strdup(" "));
                if (!data->map->arr_map[data->i])
                    return (free_memory(data->map->arr_map, data->i), ft_lstclear(&ptr), free_data(data, 1) , 1);
            }
        }
        ptr = ptr->next;   
    }
    return (ft_lstclear(&ptr), data->map->arr_map[data->i] = NULL, 0);
}

int     position_of_player(t_data *data)
{
    int y;
    int x;
    int i;

    y = 0;
    i = 0;
    while (++y < data->map->height - 1)
    {
        x = 0;
        while (++x < data->map->width - 1)
        {
            if (data->map->arr_map[y][x] == 'N' || data->map->arr_map[y][x] == 'S'
                || data->map->arr_map[y][x] == 'E' || data->map->arr_map[y][x] == 'W')
            {
                data->player->isFacing = data->map->arr_map[y][x];
                data->player->x = (float)x * TILE_SIZE;
                data->player->y = (float)y * TILE_SIZE;
                i++;
            }
        }
    }
    if (i > 1)
        return (free_array(data->map->arr_map), free_data(data, 1), 1); 
    return (0);
}

int     is_valid_Map(t_data * data)
{
	t_list *head;

    if (!all_element_exist(data))
		return (1);
	head = get_map(data);
	if (!head)
        return (free_data(data, 1), print_error("Map doesn't exist."), 1);
    if (head && !map(head, data))
        return (print_error("The map should closed by walls."), 1);
    if (head && set_map(head, data))
        return (print_error("Malloc Failed."), 1);    
    if (is_adjacent(data, data->map->arr_map, 32, '0'))
        return (print_error("Player out."), 1);
    if (position_of_player(data))
        return (print_error("Invalid position of player."), 1);
    if (is_adjacent(data, data->map->arr_map, data->player->isFacing, 32))
        return (print_error("Player out."), 1);
    // free_array(map_array) && free_data(data, 1);
    return (0);
}
