/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:32:53 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 19:21:29 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_parsing_map_e(t_map **tab, t_data *x, char *c)
{
	t_map	*map;

	map = *tab;
	while (map)
	{
		if ((ft_strncmp(c, "E", 1) == 0 && ft_strnstr(map->x, c, 1000)))
		{
			x->count_e++;
		}
		map = map->next;
	}
	return (x->count_e);
}

int	ft_return_count_e(t_data *x)
{
	if (x->count_e < 1)
	{
		ft_putstr_fd("Error :\nMissing at least one exit\n", 2);
		return (0);
	}
	return (1);
}
