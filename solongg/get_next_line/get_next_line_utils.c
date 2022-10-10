/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:38:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 19:20:02 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_is_a_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	else
		return (0);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_read_buffer(int fd, char *buf)
{
	int	var_read;

	var_read = read(fd, buf, 1);
	return (var_read);
}

char	*free_join(char *str, int count)
{
	while (count >= 0)
	{
		free(str);
		count--;
	}
	free(str);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*final;

	i = 0;
	j = 0;
	final = malloc(sizeof(char) * (ft_strlen_gnl(s1)
				+ (ft_strlen_gnl(s2)) + 1));
	if (!final)
		return (free_join(final, i), NULL);
	while (s1 && (char)s1[i])
	{
		final[i] = (char)s1[i];
		i++;
	}
	free(s1);
	while ((char)s2[j])
	{
		final[i] = (char)s2[j];
		i++;
		j++;
	}
	final[i] = '\0';
	return (final);
}
