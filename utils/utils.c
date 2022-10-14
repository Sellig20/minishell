/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:43:16 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/14 16:27:31 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	int		word_ct;

	i = 0;
	word_ct = 0;
	while (*s == c)
		s++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			word_ct++;
		i++;
	}
	if (word_ct == 0 && *s == '\0')
		return (word_ct);
	return (word_ct + 1);
}

static char	**ft_free(char **res, size_t i)
{
	while (res[i] && i > 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

char	*ft_strndup(char const *s, int word_size)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * word_size + 1);
	if (!s)
		return (NULL);
	if (!word)
		return (NULL);
	j = 0;
	while (j < word_size)
	{
		word[j] = s[j];
		j++;
	}
	word[word_size] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	word_size;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		word_size = 0;
		while (s[word_size] != c && s[word_size])
			word_size++;
		if (word_size != 0)
			res[j++] = ft_strndup(s, word_size);
		if (word_size != 0 && res[j - 1] == NULL)
			return (ft_free(res, j - 1));
		s += word_size;
	}
	res[j] = NULL;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	new_s = NULL;
	i = -1;
	j = 0;
	if (!(s1 || s2))
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (new_s == NULL)
		return (NULL);
	while (s1[++i])
		new_s[i] = s1[i];
	while (s2[j])
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}
