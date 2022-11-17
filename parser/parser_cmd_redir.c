/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:38:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 17:36:27 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_onedupcmd(t_list **portion, t_list **dup)
{
	t_list	*new;
	t_words	*content;

	content = NULL;
	if (check_words(*portion) == 1
		&& ((t_words *)(*portion)->next->content)->token == TOK_DOLL
			&& ((t_words *)(*portion)->next->next->content)->token == TOK_WORD)
		return (2);
	if ((((((t_words *)(*portion)->content)->token != TOK_DOLL))
		&& check_words(*portion) == 1)
			&& (*portion)->next->next)
		(*portion) = (*portion)->next->next;
	else
	{
		content = (t_words *)(*portion)->content;
		new = ft_lstnew((void *)words_init(content->word, content->token));
		ft_lstadd_back(dup, new);
		*portion = (*portion)->next;
	}
	return (0);
}

t_list	**ft_dupcmd(t_list *portion)
{
	t_list	**dup;

	dup = malloc(sizeof(t_list *));
	if (!dup)
		return (NULL);
	*dup = NULL;
	if (!portion)
		return (NULL);
	while (portion)
	{
		if (((t_words *)portion->content)->token != TOK_DOLL
			&& check_words(portion) == 1
			&& (!(portion->next->next)))
			break ;
		if (check_words(portion) == 1
			&& ((t_words *)portion->next->content)->token == TOK_DOLL
			&& ((t_words *)portion->next->next->content)->token == TOK_WORD
			&& portion->next->next->next)
			portion = portion->next->next->next;
		if (ft_onedupcmd(&portion, dup) > 0)
			break ;
	}
	if (!(*dup))
		(*dup) = ft_lstnew(NULL);
	return (dup);
}

static void	ft_one_dupredir(t_list **portion, t_list **dup)
{
	t_list	*new;
	t_words	*tmp;

	tmp = (t_words *)(*portion)->content;
	if (tmp->token != TOK_WORD && tmp->token != TOK_DOLL)
	{
		new = ft_lstnew((void *) words_init(tmp->word, tmp->token));
		ft_lstadd_back(dup, new);
		*portion = (*portion)->next;
		tmp = (t_words *)(*portion)->content;
		new = ft_lstnew((void *) words_init(tmp->word, tmp->token));
		ft_lstadd_back(dup, new);
	}
}

t_list	**ft_dupredir(t_list *portion)
{
	t_list	**dup;

	dup = malloc(sizeof(t_list *));
	if (!dup)
		return (NULL);
	*dup = NULL;
	if (!portion)
		return (NULL);
	while (portion)
	{
		if (!(portion->next))
			break ;
		ft_one_dupredir(&portion, dup);
		portion = portion->next;
	}
	if (!(*dup))
		(*dup) = ft_lstnew(NULL);
	return (dup);
}

void	ft_sep_cmd_redir(t_list **btw_pipes, t_list **future)
{
	t_list		*btw;
	t_list		*new;
	t_btw_pipes	*portion;

	portion = NULL;
	*future = NULL;
	btw = *btw_pipes;
	new = NULL;
	while (btw && ((t_btw_pipes *)btw->content))
	{
		portion = (t_btw_pipes *) btw->content;
		new = ft_lstnew((void *) cmdredir_init(portion->portion_words));
		ft_lstadd_back(future, new);
		btw = btw->next;
	}
}
