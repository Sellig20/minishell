/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_y.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:35:23 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 15:43:05 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_len_x(t_map **tab, t_data *data)
{
	int		i;
	char	*str;
	t_map	*map;

	i = 0;
	map = *tab;
	str = map->x;
	while (str[i])
	{
		data->len_x = ft_strlen(str);
		i++;
	}
	data->len_x--;
}

void	ft_len_y(t_map **tab, t_data *data)
{
	t_map	*map;

	map = *tab;
	data->len_y = ft_lstsize(&map);
}

void	ft_len_xy(t_map **tab, t_data *x)
{
	t_map	*map;

	map = *tab;
	ft_len_x(&map, x);
	ft_len_y(&map, x);
}
