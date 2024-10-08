/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:53:05 by aben-cha          #+#    #+#             */
/*   Updated: 2024/07/07 15:55:13 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(const char *set, char c)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	begin;
	int	end;
	int	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (s1[begin] && check_char(set, s1[begin]))
		begin++;
	while ((end >= 0) && check_char(set, s1[end]))
		end--;
	size = end - begin + 1;
	return (ft_substr(s1, begin, size));
}
