/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:15:29 by aben-cha          #+#    #+#             */
/*   Updated: 2024/08/08 18:27:12 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void free_structs(t_data *data)
{
    free(data->map);
    free(data->player);
    free(data->texture);
}

void    print_error(char *str)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd(str, 2);
    exit(1);
}

void    free_data(t_data *data, int flag)
{
    if (flag)
        ft_lstclear(&data->texturel);
    ft_lstclear(&data->list);
    free_structs(data);
}
