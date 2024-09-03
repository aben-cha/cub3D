/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:06:08 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/02 18:06:08 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	read_data(int *fd, char *av)
{
	if (!av)
		print_error("File doesn't exist.");
	if (ft_strncmp(av + ft_strlen(av) - 4, ".cub", 4))
		print_error("Wrong extension.");
	*fd = open(av, O_RDONLY);
	if (*fd == -1)
		print_error("Error opening file.");
}

void	fill_list(t_data *data, char *av)
{
	read_data(&data->fd, av);
	data_init(data);
	while (1)
	{
		data->string = get_next_line(data->fd);
		if (!data->string)
			break ;
		ft_lstadd_back(&data->list,
			ft_lstnew((char *)ft_strdup(data->string), '0'));
		free(data->string);
	}
	if (!data->list)
	{
		close(data->fd);
		free_data(data, 0);
		print_error("Empty file.");
	}
	close(data->fd);
}

int	check_char(char *s)
{
	if (!ft_check_line("NSEWFC1\n ", s[0]))
		return (1);
	if ((s[0] == 'F' || s[0] == 'C') && s[1] != ' ')
		return (1);
	else if ((s[0] == 'N' || s[0] == 'S') && (s[1] != 'O' || s[2] != ' '))
		return (1);
	else if ((s[0] == 'E' || s[1] == 'A') && s[2] != ' ')
		return (1);
	else if ((s[0] == 'W' || s[1] == 'E') && s[2] != ' ')
		return (1);
	return (0);
}

int	element_exist(t_list *head, char *d)
{
	int		len;
	int		j;
	char	*s;

	len = 0;
	while (head)
	{
		s = (char *)head->content;
		j = 0;
		while (s && s[j] == ' ')
			j++;
		if (check_char(s + j))
			return (0);
		if (!ft_strncmp(&s[j], d, ft_strlen(d)))
			len++;
		head = head->next;
	}
	if (len == 0 || len > 1)
		return (0);
	return (1);
}

int	all_element_exist(t_data *data)
{
	if (!element_exist(data->list, "NO") || !element_exist(data->list, "SO")
		|| !element_exist(data->list, "WE") || !element_exist(data->list, "EA")
		|| !element_exist(data->list, "F") || !element_exist(data->list, "C"))
	{
		free_data(data, 0);
		return (print_error("Invalid Element."), 0);
	}
	return (1);
}
