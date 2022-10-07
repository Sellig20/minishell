/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:25:02 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/27 17:20:09 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*final;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	final = (char *)malloc(sizeof(char)
			* ((ft_strlen(s1) + (ft_strlen(s2))) + 1));
	if (final == NULL)
		return (NULL);
	while ((char)s1[i])
	{
		final[i] = (char)s1[i];
		i++;
	}
	while ((char)s2[j])
	{
		final[i] = (char)s2[j];
		j++;
		i++;
	}
	final[i] = '\0';
	return (final);
}
