/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:38:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/04 01:32:56 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_onedupcmd(t_list **portion, t_list **dup)
{
	t_list	*new;
	t_words	*content;

	content = NULL;
	if (((t_words *)(*portion)->content)->token != TOK_WORD
			&& ((t_words *)(*portion)->next->content)->token == TOK_DOLL
			&& ((t_words *)(*portion)->next->next->content)->token == TOK_WORD)
		return (2);
	if ((((((t_words *)(*portion)->content)->token != TOK_DOLL))
		&& ((t_words *)(*portion)->content)->token != TOK_WORD)
			&& (*portion)->next->next)
		(*portion) = (*portion)->next->next;
	else
	{
		content = (t_words *)(*portion)->content;
		new = ft_lstnew((void *)words_init(content->word, content->token));
		dup = (t_list **)ft_lstadd_back2(dup, new);
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
			&& ((t_words *) portion->content)->token != TOK_WORD
			&& (!(portion->next->next)))
			break ;
		if (((t_words *)portion->content)->token != TOK_WORD
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
		dup = (t_list **)ft_lstadd_back2(dup, new);
		*portion = (*portion)->next;
		tmp = (t_words *)(*portion)->content;
		new = ft_lstnew((void *) words_init(tmp->word, tmp->token));
		dup = (t_list **)ft_lstadd_back2(dup, new);
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

t_cmdredir	*cmdredir_init(t_list *portion)
{
	t_cmdredir	*list;
	t_list		**remplir_cmd;
	t_list		**remplir_redir;

	remplir_cmd = NULL;
	remplir_redir = NULL;
	if (!portion)
		return (NULL);
	list = malloc(sizeof(t_cmdredir));
	if (!list)
		return (NULL);
	remplir_cmd = ft_dupcmd(portion);
	remplir_redir = ft_dupredir(portion);
	list->cmd = (*remplir_cmd);
	list->redirection = (*remplir_redir);
	list->process_id = -2;
	free(remplir_cmd);
	free(remplir_redir);
	return (list);
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
	while (btw)
	{
		portion = (t_btw_pipes *) btw->content;
		new = ft_lstnew((void *) cmdredir_init(portion->portion_words));
		future = (t_list **)ft_lstadd_back2(future, new);
		btw = btw->next;
	}
}
