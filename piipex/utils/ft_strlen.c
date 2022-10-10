/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:31:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/11 17:26:15 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
	{
		ft_argv_error((char *)s);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (s[i])
		i++;
	return (i);
}
