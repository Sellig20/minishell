/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:44:28 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/31 19:00:50 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_btw_del(t_list *end, t_list **start)
{
	t_list	*swp;

	swp = NULL;
	if (start == NULL || *start == NULL)
		return ;
	while (*start && ((!end) || (end && *start != end)))
	{
		if ((*start)->next)
			swp = (*start)->next;
		else
			swp = NULL;
		ft_lstdelone(*start, ft_free_words);
		(*start) = swp;
	}
}

static void	first_word(t_list **tmp, t_list **lst, t_list **envcp, t_data *x)
{
	char	*word;
	t_list	*new;
	t_list	*end;

	word = NULL;
	end = find_end_del(*tmp);
	word = until_next_del(*tmp, end, envcp, x);
	delete_btw_del(end, tmp);
	if (!end)
	{
		new = ft_lstnew((void *) words_init(word, TOK_WORD));
		free(word);
		*lst = new;
	}
	else
	{
		*lst = end;
		new = ft_lstnew((void *) words_init(word, TOK_WORD));
		free(word);
		ft_lstadd_front(lst, new);
		(*lst)->next = end;
	}
}

static void	other_word(t_list **tmp, t_list **envcp, t_data *x)
{
	t_list	*start;
	t_list	*end;
	char	*word;
	t_list	*new;

	start = (*tmp)->next;
	end = find_end_del(start);
	word = until_next_del(start, end, envcp, x);
	new = ft_lstnew((void *) words_init(word, TOK_WORD));
	free(word);
	delete_btw_del(end, &start);
	ft_insert(new, *tmp);
	*tmp = (*tmp)->next;
	if (end && end->next)
		(*tmp)->next = end;
	else
		(*tmp)->next = NULL;
}

int	check_del(t_list *tmp)
{
	t_words	*content;

	content = (t_words *) tmp->content;
	if (content->token == TOK_FROM || content->token == TOK_TO
		|| content->token == TOK_FRFR || content->token == TOK_TOTO
		|| content->token == TOK_SPAC || content->token == TOK_PIPE)
		return (1);
	return (0);
}

void	new_expand(t_list **lst_words, t_list **envcp, t_data *x)
{
	t_list	*tmp;
	tmp = *lst_words;
	ft_check_ambi(&tmp, x);
	if (tmp && check_del(tmp) == 0)
	{
		first_word(&tmp, lst_words, envcp, x);
		if (*lst_words)
			tmp = *lst_words;
		else
			tmp = NULL;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next && check_del(tmp->next) == 0)
			other_word(&tmp, envcp, x);
		else
			tmp = tmp->next;
	}
}
