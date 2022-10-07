/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:36:31 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 19:20:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_read_text(int fd, char *final)
{
	int		var_read;
	char	*buf;
	char	*tmp;

	buf = malloc(sizeof(char) * 2);
	if (!buf)
		return (free(final), NULL);
	var_read = 1;
	while (ft_is_a_line(final) == 0 && var_read > 0)
	{
		var_read = ft_read_buffer(fd, buf);
		if (var_read > 0)
		{
			buf[var_read] = '\0';
			tmp = ft_strjoin(final, buf);
			if (tmp == NULL)
				return (free(final), free(buf), NULL);
			final = tmp;
		}
	}
	free(buf);
	if (var_read == -1)
		return (NULL);
	return (final);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = s;
	while (n > 0)
	{
		str[i] = 0;
		i++;
		n--;
	}
}

char	*ft_extract_line(char *s1)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!s1[i])
		return (0);
	while (s1[i] && s1[i] != '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	ft_bzero(new_line, i + 2);
	i = 0;
	while (s1[i] && (s1[i] != '\n'))
	{
		new_line[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		new_line[i] = '\n';
		i++;
	}
	return (new_line);
}

char	*ft_save_line(char *str)
{
	int		i;
	int		j;
	char	*final;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	final = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!final)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		final[j++] = str[i++];
	final[j] = '\0';
	free(str);
	return (final);
}

/**
 * Get the next line object
 *
 *
 * @param reset	used for free the static variable
 * 				0 is for not free the static
 * 				1 is for free the static
 *  @return char*
 */

char	*get_next_line(int fd, int reset)
{
	char		*line;
	static char	*buf;

	if (reset)
		return (free(buf), NULL);
	if (fd < 0)
		return (0);
	buf = ft_read_text(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_extract_line(buf);
	if (!line)
	{
		return (NULL);
	}
	buf = ft_save_line(buf);
	return (line);
}
