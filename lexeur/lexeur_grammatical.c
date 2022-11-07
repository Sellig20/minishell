/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_grammatical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:00:34 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/05 02:57:35 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	syntax_error(t_list *tmp, int i)
{
	if (i == 1 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		write(2, "Minimichel: syntax error near unexpected token `", 48);
		if (i == 4)
			tmp = tmp->next;
		write(2, ((t_words *) tmp->content)->word,
			ft_strlen(((t_words *)tmp->content)->word));
		write(2, "'\n", 2);
	}
	else if (i == 7)
		write(2, "Minimichel: syntax error near unexpected token `newline'\n",
			57);
	else if (i == 2)
	{
		write(2, "Minimichel: syntax error near unexpected token `", 48);
		write(2, ((t_words *)tmp->content)->word, 2);
		write(2, "'\n", 2);
	}
	else if (i == 8)
		write(2, "Minimichel: wrong number of quotes\n", 35);
	g_status = 2;
}

int	token_validity(t_list **lst_words)
{
	t_list	*tmp;

	tmp = *lst_words;
	while (tmp)
	{
		if ((((t_words *)tmp->content)->token == TOK_PIPE
				|| ((t_words *)tmp->content)->token == TOK_DOLL)
			&& ft_strlen(((t_words *)tmp->content)->word) > 1)
			return (syntax_error(tmp, 1), 1);
		else if ((((t_words *)tmp->content)->token == TOK_TO
				|| ((t_words *)tmp->content)->token == TOK_FROM)
			&& ft_strlen(((t_words *)tmp->content)->word) > 2)
			return (syntax_error(tmp, 2), 1);
		else if (((t_words *)tmp->content)->token == TOK_TO
			&& ft_strlen(((t_words *)tmp->content)->word) == 2)
			((t_words *)tmp->content)->token = TOK_TOTO;
		else if (((t_words *)tmp->content)->token == TOK_FROM
			&& ft_strlen(((t_words *)tmp->content)->word) == 2)
			((t_words *) tmp->content)->token = TOK_FRFR;
		tmp = tmp->next;
	}	
	return (0);
}

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

int	token_order(t_list **lst_words)
{
	t_list	*tmp;

	tmp = *lst_words;
	if (tmp && ((t_words *) tmp->content)->token == TOK_SPAC)
		tmp = tmp->next;
	if (tmp && ((t_words *) tmp->content)->token == TOK_PIPE)
		return (syntax_error(tmp, 3), 1);
	while (tmp && tmp->next)
	{
		if (check_redir(tmp) == 0 && check_after_redir(&tmp) == 0)
			return (syntax_error(tmp, 4), 1);
		else if (((t_words *)tmp->content)->token == TOK_PIPE
			&& ((t_words *)(tmp->next)->content)->token == TOK_PIPE)
			return (syntax_error(tmp, 5), 1);
		else
			tmp = tmp->next;
	}
	if (tmp && ((t_words *)tmp->content)->token == TOK_PIPE)
		return (syntax_error(tmp, 6), 1);
	else if (tmp && ((t_words *)tmp->content)->token != TOK_WORD
		&& ((t_words *)tmp->content)->token != TOK_DOLL
		&& ((t_words *)tmp->content)->token != TOK_QUOT)
		return (syntax_error(tmp, 7), 1);
	return (0);
}
