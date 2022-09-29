/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:01:54 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/23 12:55:38 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_player	ft_create_player(int i, int j)
{
	t_player	play;
	t_coor		coord;

	coord.x = j;
	coord.y = i;
	play.coord = coord;
	play.dir = -1;
	return (play);
}

int	ft_convert_in_char(t_map **tab, t_data *data)
{
	t_map	*tmp;
	t_map	*map;
	int		i;

	map = *tab;
	tmp = map;
	i = 0;
	data->dtab = malloc(sizeof(char *) * data->len_y);
	if (data->dtab == NULL)
		return (0);
	while (map)
	{
		data->dtab[i] = map->x;
		map = map->next;
		i++;
	}
	ft_index(data);
	return (1);
}

void	ft_index(t_data *x)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	str = NULL;
	while (x->dtab[i])
	{
		j = 0;
		while (x->dtab[i][j])
		{
			if (x->dtab[i][j] == 'P')
			{
				x->player = ft_create_player(i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_invocation_render(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->texture[g_lookup[data->ri].index],
		data->pos[X] + g_lookup[data->ri].offset[X],
		data->pos[Y] + g_lookup[data->ri].offset[Y]);
}

int	render(t_data *data)
{
	char	*str;
	t_map	*map;

	map = data->map;
	data->pos[Y] = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (map)
	{
		data->pos[X] = 0;
		str = map->x;
		while (*str)
		{
			data->ri = 0;
			while (g_lookup[data->ri].c != 'J' && *str != g_lookup[data->ri].c)
				data->ri++;
			if (g_lookup[data->ri].c != 'J')
				ft_invocation_render(data);
			data->pos[X] += 128;
			str++;
		}
		data->pos[Y] += 128;
		map = map->next;
	}
	return (0);
}
