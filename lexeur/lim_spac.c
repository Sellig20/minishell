/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lim_spac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:44:11 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/27 00:31:09 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	del_first(t_list **tmp, t_list **lst_words)
{
	t_list	*swp;

	*tmp = *lst_words;
	swp = NULL;
	if (*tmp && ((t_words *)(*tmp)->content)->token == TOK_SPAC)
	{
		if ((*tmp)->next)
			swp = (*tmp)->next;
		*lst_words = swp;
		ft_lstdelone(*tmp, ft_free_words);
		*tmp = *lst_words;
	}
}

int	ft_delete_space(t_list **lst_words)
{
	t_list	*tmp;
	t_list	*swp;

	tmp = *lst_words;
	swp = NULL;
	del_first(&tmp, lst_words);
	while (tmp && tmp->next)
	{
		swp = NULL;
		if (tmp && tmp->next
			&& ((t_words *) tmp->next->content)->token == TOK_SPAC)
		{
			if (tmp->next->next)
				swp = tmp->next->next;
			ft_lstdelone(tmp->next, ft_free_words);
			tmp->next = swp;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	if (!lst_words || !(*lst_words))
		return (1);
	return (0);
}

static char	*get_lim(t_list **tmp, char *lim, t_words **content)
{
	t_list	*swp;
	char	*word;

	*content = (t_words *)(*tmp)->content;
	word = lim;
	lim = ft_strjoin(word, (*content)->word);
	free(word);
	swp = *tmp;
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		*content = (t_words *)(*tmp)->content;
	}
	else
		*tmp = NULL;
	ft_lstdelone(swp, ft_free_words);
	return (lim);
}

static void	put_lim(t_list **tmp, t_list **heredoc)
{
	t_list	*new;
	t_words	*content;
	char	*lim;

	content = (t_words *)(*tmp)->content;
	lim = NULL;
	while (*tmp && (content->token != TOK_SPAC
			&& content->token != TOK_PIPE && content->token != TOK_FROM
			&& content->token != TOK_FRFR && content->token != TOK_TO
			&& content->token != TOK_TOTO))
		lim = get_lim(tmp, lim, &content);
	if (lim)
	{
		new = ft_lstnew((void *) words_init(lim, TOK_WORD));
		ft_insert(new, *heredoc);
		free(lim);
		*heredoc = (*heredoc)->next;
	}
}

void	ft_lim_protection(t_list **lst_words)
{
	t_list	*tmp;
	t_list	*heredoc;
	t_list	*swp;

	tmp = *lst_words;
	heredoc = *lst_words;
	while (heredoc)
	{
		if (((t_words *) heredoc->content)->token == TOK_FRFR)
		{
			tmp = heredoc->next;
			if (((t_words *) tmp->content)->token == TOK_SPAC)
			{
				swp = tmp;
				tmp = tmp->next;
				ft_lstdelone(swp, ft_free_words);
			}
			put_lim(&tmp, &heredoc);
			heredoc->next = tmp;
		}
		else
			heredoc = heredoc->next;
	}
}
