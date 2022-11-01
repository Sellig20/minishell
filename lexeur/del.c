/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:42:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/31 16:26:44 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_one_btw_quot(t_list **tmp, t_list **envcp, t_data *x)
{
	int		res;
	char	*new_echo;

	res = 0;
	new_echo = NULL;
	if ((t_words *)(*tmp)->content == NULL)
	{
		new_echo = calloc(sizeof(char), 1);
		return (new_echo);
	}
	if (*tmp && ((t_words *)(*tmp)->content)->token != TOK_QUOT)
	{
		if (((t_words *)(*tmp)->content)->token == TOK_DOLL && (*tmp)->next)
		{
			res = ft_check_after_doll(((t_words *)(*tmp)->next->content)->word);
			new_echo = ft_result(envcp, res,
					((t_words *)(*tmp)->next->content)->word, x);
			if (new_echo == NULL)
				return (NULL);
		}
		else
			new_echo = ft_strdup(((t_words *)(*tmp)->content)->word);
	}
	return (new_echo);
}

static char	*doll_btw_del(t_list **tmp, char *btw, t_list **envcp, t_data *x)
{
	char	*word;
	char	*word2;

	word = NULL;
	word2 = NULL;
	if (((t_words *)(*tmp)->next->content)->token != TOK_QUOT)
	{
		word = ft_expand_one_btw_quot(tmp, envcp, x);
		if (word == NULL)
			return (NULL);
		word2 = btw;
		btw = ft_strjoin(word2, word);
		free(word);
		free(word2);
		*tmp = (*tmp)->next;
	}
	else
	{
		btw = ft_strjoin(btw, "$\0");
		word = btw;
	}
	return (btw);
}

char	*until_next_del(t_list *tmp, t_list *end, t_list **envcp, t_data *x)
{
	char	*word;
	char	*btw_del;

	word = NULL;
	btw_del = NULL;
	while (tmp && tmp != end)
	{
		if (((t_words *) tmp->content)->token == TOK_WORD)
		{
			word = btw_del;
			btw_del = ft_strjoin(word, ((t_words *) tmp->content)->word);
			free(word);
		}
		else if (((t_words *) tmp->content)->token == TOK_DOLL)
		{
			btw_del = doll_btw_del(&tmp, btw_del, envcp, x);
			// if (btw_del == NULL)
			// 	return (NULL);
		}
		tmp = tmp->next;
	}
	//dprintf(2, "btw del = %s\n", btw_del);
	return (btw_del);
}

t_list	*find_end_del(t_list *af_del)
{
	t_list	*end;

	if (af_del)
		end = af_del;
	else
		return (NULL);
	while (end && check_del(end) == 0)
		end = end->next;
	return (end);
}