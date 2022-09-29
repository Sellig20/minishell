/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:04:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/10 16:33:45 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
