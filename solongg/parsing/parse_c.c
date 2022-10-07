/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:35:33 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 19:21:29 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_parsing_map_c(t_map **tab, t_data *x, char *c)
{
	t_map	*map;
	char	*str;
	int		i;

	map = *tab;
	str = map->x;
	i = 0;
	while (map->x[i])
	{
		if (ft_strncmp(c, "C", 1) == 0
			&& ft_strnstr(map->x, c, ft_strlen(map->x))
			&& str[i] == 'C')
			x->count_c++;
		i++;
	}
	return (x->count_c);
}

int	ft_return_count_c(t_data *x)
{
	if (x->count_c < 1)
	{
		ft_putstr_fd("Error :\nMissing at least one collectible\n", 2);
		return (0);
	}
	return (1);
}
