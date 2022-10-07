/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:37:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/21 15:04:52 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_parse(char **argv)
{
	int	i;

	i = 0;
	if ((ft_strlen(argv[i]) == 0))
	{
		ft_perm_error(argv[i]);
		return (0);
	}
	if (ft_is_space(argv[i]) == 0)
	{
		ft_argv_error(argv[i]);
		return (0);
	}
	return (1);
}
