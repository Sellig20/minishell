/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:57:48 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 20:56:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	*create(t_data *data)
{
	ft_get_images(data);
	return (data);
}

int	ft_un_alloc(t_data *data)
{
	if (data->map)
		ft_lstclear(&data->map);
	if (data->texture[WALL])
		mlx_destroy_image(data->mlx_ptr, data->texture[WALL]);
	if (data->texture[GROUND])
		mlx_destroy_image(data->mlx_ptr, data->texture[GROUND]);
	if (data->texture[EXIT])
		mlx_destroy_image(data->mlx_ptr, data->texture[EXIT]);
	if (data->texture[CHARAC])
		mlx_destroy_image(data->mlx_ptr, data->texture[CHARAC]);
	if (data->texture[COLLECTIBLE])
		mlx_destroy_image(data->mlx_ptr, data->texture[COLLECTIBLE]);
	if (data->win_ptr)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->dtab)
		free(data->dtab);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	x;

	ft_bzero(&x, sizeof(x));
	if (ft_check_args(argc, argv) == 0)
		return (ft_lstclear(&x.map), 0);
	if (ft_open_map(argv, &x) == 0)
		return (ft_un_alloc(&x), 0);
	close(x.file);
	x.mlx_ptr = mlx_init();
	if (x.mlx_ptr == NULL)
		return (ft_un_alloc(&x));
	if (ft_get_images(&x) == 0)
		return (1);
	x.win_ptr = mlx_new_window(x.mlx_ptr, x.len_x * 128,
			x.len_y * 128, "So_long.c");
	if (x.win_ptr == NULL)
	{
		ft_un_alloc(&x);
		return (MLX_ERROR);
	}
	mlx_hook(x.win_ptr, 2, 1L << 0, deal_key, &x);
	mlx_hook(x.win_ptr, 17, 0L, ft_exit_game, &x);
	refresh(&x);
	mlx_loop(x.mlx_ptr);
	return (0);
}
