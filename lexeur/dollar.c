/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:42:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/12 18:11:14 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_one_btw_quot(t_list **tmp, t_list **envcp, t_data *x)
{
	int		res;
	char	*new_echo;

	res = 0;
	new_echo = NULL;
	if (*tmp && (((t_words *)(*tmp)->content)->token != TOK_QUOT))
	{
		if (((t_words *)(*tmp)->content)->token == TOK_DOLL && (*tmp)->next)
		{
			res = ft_check_after_d(((t_words *)(*tmp)->next->content)->word);
			new_echo = ft_result(envcp, res,
					((t_words *)(*tmp)->next->content)->word, x);
			if (ft_strlen(new_echo) == 0)
				return (new_echo);
		}
		else
			new_echo = ft_strdup(((t_words *)(*tmp)->content)->word);
	}
	if (x->check == D_QUOTE_STATE || x->file == 42)
		protect_space(new_echo, 1);
	return (new_echo);
}

void	append_doll(char *word, char **btw, int ok)
{
	char	*word2;
	int		i;

	i = 0;
	word2 = NULL;
	if (!word)
		return ;
	if (ok == 0)
		protect_space(word, -1);
	while (btw && btw[i])
		i++;
	if (i == 0)
		btw[0] = ft_strdup(word);
	else
	{
		word2 = ft_strjoin(btw[i - 1], word);
		free(btw[i - 1]);
		btw[i - 1] = ft_strdup(word2);
		free(word2);
	}
}

void	add_doll(char *word, char **btw)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!word)
		return ;
	words = ft_split(word, ' ');
	if (!words)
		return ;
	unprotect_space(words);
	append_doll(words[0], btw, 1);
	i++;
	while (words && words[0] && words[j])
		btw[i++] = ft_strdup(words[j++]);
	ft_free_w(words);
}
