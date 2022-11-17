/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:33:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 16:33:30 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_not(char *executable)
{
	int	i;

	i = 0;
	while (executable[i] && executable[i] == '.')
	{
		if (executable[i + 1] == '\0')
			return (2);
		i++;
	}
	i = 0;
	while (executable[i] && executable[i] == '/')
	{
		if (executable[i + 1] == '\0')
			return (17);
		i++;
	}
	return (0);
}
