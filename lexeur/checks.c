/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:16 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/09 21:52:42 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(t_list *tmp)
{
	if (((t_words *)tmp->content)->token == TOK_FROM
		|| ((t_words *)tmp->content)->token == TOK_TO
		|| ((t_words *)tmp->content)->token == TOK_TOTO
		|| ((t_words *)tmp->content)->token == TOK_FRFR)
		return (0);
	return (1);
}

int	check_after_redir(t_list **tmp)
{
	if (((t_words *)(*tmp)->next->content)->token == TOK_SPAC)
		*tmp = (*tmp)->next;
	if (((t_words *)(*tmp)->next->content)->token != TOK_WORD
		&& ((t_words *)(*tmp)->next->content)->token != TOK_DOLL
		&& ((t_words *)(*tmp)->next->content)->token != TOK_QUOT)
		return (0);
	return (1);
}

int	check_pipes(t_list *tmp)
{
	if (((t_words *)tmp->content)->token == TOK_PIPE
		&& ((t_words *)(tmp->next)->content)->token == TOK_SPAC
		&& ((t_words *)tmp->next->next->content)->token == TOK_PIPE)
		return (0);
	return (1);
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
