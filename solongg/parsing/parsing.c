/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:39:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/07/01 20:09:46 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_execution_parsing_items(t_map **tab, t_data *x)
{
	t_map	*map;

	map = *tab;
	if (ft_execution_rectangle(&map) == 0)
		return (0);
	if (ft_execution_wall(&map) == 0)
		return (0);
	ft_len_xy(&map, x);
	x->count_p = ft_parsing_map_p(&map, x, "P");
	if (ft_return_count_p(x) == 0)
		return (0);
	x->count_e = ft_parsing_map_e(&map, x, "E");
	if (ft_return_count_e(x) == 0)
		return (0);
	while (map)
	{
		x->count_c = ft_parsing_map_c(&map, x, "C");
		map = map->next;
	}
	if (ft_return_count_c(x) == 0)
		return (0);
	return (1);
}

int	ft_execution_rectangle(t_map **tab)
{
	t_map	*map;

	map = *tab;
	if (ft_is_rectangle(&map) == 0)
	{
		ft_putstr_fd("Error :\nInvalid map\n", 2);
		return (0);
	}
	return (1);
}

int	ft_execution_wall(t_map **tab)
{
	t_map	*map;
	int		i;

	map = *tab;
	if (ft_is_wall_last(&map) == 0 || ft_is_wall_first(&map) == 0
		|| ft_is_wall_first_case(&map) == 0 || ft_is_wall_last_case(&map) == 0)
	{
		ft_putstr_fd("Error :\nNo wall around the rectangle\n", 2);
		return (0);
	}
	while (map)
	{
		i = 0;
		while (map->x[i])
		{
			if (map->x[i] == '1' || map->x[i] == '0' || map->x[i] == 'C'
				|| map->x[i] == 'E' || map->x[i] == 'P' || map->x[i] == '\n')
				map->is_good++;
			else
				return (ft_putstr_fd("Error :\nInvalid map\n", 2), 0);
			i++;
		}
		map = map->next;
	}
	return (1);
}

int	ft_read_infile(char *infile)
{
	if (!(ft_strnstr(&infile[ft_strlen(infile) - 4], ".ber", 4)))
	{
		ft_putstr_fd("Error :\nInvalid argument/map\n", 2);
		return (0);
	}
	if (ft_strcmp(infile, ".ber") == 0)
	{
		ft_putstr_fd("Error :\nInvalid infile\n", 2);
		return (0);
	}
	return (1);
}

int	ft_is_rectangle(t_map **tab)
{
	t_map	*map;
	t_map	*first;
	int		i;
	int		k;
	int		l;

	map = *tab;
	first = *tab;
	i = 0;
	k = 0;
	l = 0;
	while (map->next)
	{
		l = ft_strlen(map->x);
		if (map->next->x[l] == '\0' && map->next->x[l - 1] != '\n')
			k = k - 1;
		if (ft_strlen(map->next->x) == (k + l))
			map = map->next;
		else
			return (0);
	}
	return (1);
}
