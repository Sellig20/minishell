/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:30:49 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/29 19:50:53 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_get_images(t_data *data)
{
	int		height;
	int		width;

	data->texture[WALL] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./texture/GardenBed_Cucumbers_02.xpm", &width, &height);
	if (data->texture[WALL] == NULL)
	{
		ft_putstr_fd("Error :\nWall image\n", 2);
		ft_un_alloc(data);
		return (0);
	}
	data->texture[CHARAC] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./texture/Chick_Down.xpm", &width, &height);
	if (data->texture[CHARAC] == NULL)
	{
		ft_putstr_fd("Error :\nCharacter image\n", 2);
		ft_un_alloc(data);
		return (0);
	}
	if (ft_get_images_annex(data, height, width) == 0)
		return (0);
	return (1);
}

int	ft_get_images_annex(t_data *data, int height, int width)
{
	data->texture[COLLECTIBLE] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./texture/Radish.xpm", &width, &height);
	if (data->texture[COLLECTIBLE] == NULL)
	{
		ft_putstr_fd("Error :\nCollectible image\n", 2);
		ft_un_alloc(data);
		return (0);
	}
	data->texture[EXIT] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./texture/Hole.xpm", &width, &height);
	if (data->texture[EXIT] == NULL)
	{
		ft_putstr_fd("Error :\nExit image\n", 2);
		ft_un_alloc(data);
		return (0);
	}
	data->texture[GROUND] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./texture/GardenBed_Carrots_01.xpm", &width, &height);
	if (data->texture[GROUND] == NULL)
	{
		ft_putstr_fd("Error :\nGround image\n", 2);
		ft_un_alloc(data);
		return (0);
	}
	return (1);
}
