/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_grammatical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:00:34 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:00:46 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_list *tmp, int i)
{
	if (i == 1 || i == 3 || i == 5 || i == 6)
	{
		write(2, "Minimichel: syntax error near unexpected token `\n", 49);
		write(2, ((t_words *) tmp->content)->word,
			ft_strlen(((t_words *)tmp->content)->word));
		write(2, "'\n", 2);
	}
	else if (i == 7)
		write(2, "Minimichel: syntax error near unexpected token `newline'\n",
			57);
	else if (i == 4)
	{
		write(2, "Minimichel: syntax error near unexpected token `\n", 49);
		tmp = tmp->next;
		write(2, ((t_words *)tmp->content)->word,
			ft_strlen(((t_words *)tmp->content)->word));
		write(2, "'\n", 2);
	}
	else if (i == 2)
	{
		write(2, "Minimichel: syntax error near unexpected token `\n", 49);
		write(2, ((t_words *)tmp->content)->word, 2);
		write(2, "'\n", 2);
	}
	else if (i == 8)
		write(2, "Minimichel: wrong number of quotes\n", 35);
}

int	token_validity(t_list **lst_words)
{
	t_list	*tmp;

	tmp = *lst_words;
	while (tmp)
	{
		if (((t_words *)tmp->content)->token == TOK_PIPE
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

int	token_order(t_list **lst_words)
{
	t_list	*tmp;

	tmp = *lst_words;
	if (((t_words *) tmp->content)->token == TOK_PIPE)
		return (syntax_error(tmp, 3), 1);
	while (tmp->next)
	{
		if ((((t_words *)tmp->content)->token == TOK_FROM
				|| ((t_words *)tmp->content)->token == TOK_TO
				|| ((t_words *)tmp->content)->token == TOK_TOTO
				|| ((t_words *)tmp->content)->token == TOK_FRFR)
			&& ((t_words *)(tmp->next)->content)->token != TOK_WORD)
			return (syntax_error(tmp, 4), 1);
		else if (((t_words *)tmp->content)->token == TOK_PIPE
			&& ((t_words *)(tmp->next)->content)->token == TOK_PIPE)
			return (syntax_error(tmp, 5), 1);
		else
			tmp = tmp->next;
	}
	if (((t_words *)tmp->content)->token == TOK_PIPE)
		return (syntax_error(tmp, 6), 1);
	else if (((t_words *)tmp->content)->token != TOK_WORD && ((((t_words *)tmp->content)->token != TOK_DOLL)))
		return (syntax_error(tmp, 7), 1);
	return (0);
}
