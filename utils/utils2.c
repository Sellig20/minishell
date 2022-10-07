/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:18:23 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/28 19:41:02 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char*s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*s1_cp;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	if (len < 1)
		return (NULL);
	s1_cp = malloc((len + 1) * sizeof(char));
	if (!s1_cp)
		return (NULL);
	//s1_cp[len] = '\0';
	while (s1[i])
	{
		s1_cp[i] = s1[i];
		i++;
	}
	s1_cp[i] = '\0';
	return (s1_cp);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cp;
	unsigned char	*s2_cp;

	if (!s1 || !s2)
		return (-1);
	s1_cp = (unsigned char *) s1;
	s2_cp = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1_cp[i] && s2_cp[i] && n > i + 1)
	{
		if (s1_cp[i] != s2_cp[i])
			return (s1_cp[i] - s2_cp[i]);
		i++;
	}
	return (s1_cp[i] - s2_cp[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!needle[j])
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && (i + j < len) && needle[j]
			&& haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
