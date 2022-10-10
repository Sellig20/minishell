/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:54:16 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 19:21:29 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_lstclear(t_map **tab)
{
	t_map	*map;

	map = *tab;
	while (*tab)
	{
		map = (*tab)->next;
		free((*tab)->x);
		free(*tab);
		*tab = map;
	}
}

// void	ft_lstclear(t_map **liste)
// {
// 	t_map	*tmp;

// 	tmp = *liste;
// 	while (*liste)
// 	{
// 		tmp = (*liste)->next;
// 		free(*liste);
// 		*liste = tmp;
// 	}
// }
