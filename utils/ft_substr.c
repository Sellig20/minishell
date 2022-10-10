/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:17:29 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:25:11 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*s_sb;

	i = -1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		s_sb = malloc(1);
		len = 0;
	}
	else if (ft_strlen(s) < len)
		s_sb = malloc(sizeof(char) * (ft_strlen(s)) + 1);
	else
		s_sb = malloc(sizeof(char) * len + 1);
	if (s_sb == NULL)
		return (NULL);
	while (++i < len && s[start + i])
		s_sb[i] = s[start + i];
	s_sb[i] = '\0';
	return (s_sb);
}
