/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:42:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/14 23:15:49 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	protect_space(char *word, int sign)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] == (32 * sign))
			word[i] *= (-1);
		i++;
	}
}

void	unprotect_space(char **words)
{
	int		i;

	i = 0;
	if (!words || !words[i])
		return ;
	while (words[i])
	{
		protect_space(words[i], -1);
		i++;
	}
}

int	get_last_index(char **btw)
{
	int	i;

	i = 0;
	if (!btw)
		return (0);
	while (btw[i] && btw[i + 1])
		i++;
	return (i);
}

char	**append_last_word(t_list *tmp, char **btw_del)
{
	int		i;
	char	*word;

	i = get_last_index(btw_del);
	word = ft_strjoin(btw_del[i], ((t_words *)tmp->content)->word);
	if (btw_del[i])
		free(btw_del[i]);
	btw_del[i] = ft_strdup(word);
	free(word);
	return (btw_del);
}

void	quotes(t_data *x, t_list *tmp)
{
	if (((t_words *)tmp->content)->token == TOK_QUOT
		&& x->check == DEFAULT_STATE && x->check_to++ >= DEFAULT_STATE)
		x->check = D_QUOTE_STATE;
	else if (((t_words *)tmp->content)->token == TOK_QUOT
		&& x->check == D_QUOTE_STATE)
		x->check = DEFAULT_STATE;
}
