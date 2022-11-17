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

char	**doll(char **btw, t_list **tmp, t_list **envcp, t_data *x)
{
	char	*word;

	word = ft_expand_one_btw_quot(tmp, envcp, x);
	if (x->check != D_QUOTE_STATE)
		add_doll(word, btw);
	else
		append_doll(word, btw, 0);
	*tmp = (*tmp)->next;
	return (free(word), btw);
}

static char	**doll_btw_del(t_list **tmp, char **btw, t_list **envcp, t_data *x)
{
	char	*word;
	int		i;

	i = 0;
	if (((t_words *)(*tmp)->next->content)->token != TOK_QUOT)
	{
		btw = doll(btw, tmp, envcp, x);
		return (btw);
	}
	while (btw[i] && btw[i + 1])
		i++;
	word = btw[i];
	free(btw[i]);
	btw[i] = ft_strjoin(word, "$\0");
	(*tmp) = (*tmp)->next;
	return (free(word), btw);
}

char	**until_next_del(t_list *tmp, t_list *end, t_list **envcp, t_data *x)
{
	char	**btw_del;

	x->check = DEFAULT_STATE;
	x->check_to = DEFAULT_STATE;
	btw_del = ft_calloc(sizeof(char *), 50);
	while (tmp && tmp->content && tmp != end)
	{
		quotes(x, tmp);
		if (((t_words *) tmp->content)->token == TOK_DOLL
			&& x->doc <= 0)
			btw_del = doll_btw_del(&tmp, btw_del, envcp, x);
		else if (((t_words *)tmp->content)->token != TOK_QUOT
			|| (x->doc != 0 && x->doc != 168))
			append_last_word(tmp, btw_del);
		tmp = tmp->next;
	}
	if (!(btw_del[0]) && x->check_to > DEFAULT_STATE)
		btw_del[0] = ft_strdup("fake2\0");
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
