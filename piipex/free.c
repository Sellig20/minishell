/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:21:42 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 17:21:51 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char	**option)
{
	char	**tmp;

	tmp = option;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(option);
}
