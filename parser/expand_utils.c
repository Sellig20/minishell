/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_annexe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:20:15 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/15 19:41:23 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_new_word_4(char *new_word, t_dollar *d)
{
	char	*word;

	word = ft_strdup(new_word);
	free(new_word);
	new_word = ft_strjoin(word, d->save);
	return (free(word), new_word);
}
