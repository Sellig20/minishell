/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:42:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/17 15:05:55 by evsuits          ###   ########.fr       */
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
		}
		else
			new_echo = ft_strdup(((t_words *)(*tmp)->content)->word);
	}
	return (new_echo);
}

static char	*doll_btw_quot(t_list **tmp, char *btw, t_list **envcp, t_data *x)
{
	char	*word;
	char	*word2;

	word = NULL;
	word2 = NULL;
	if (((t_words *)(*tmp)->next->content)->token != TOK_QUOT)
	{
		word = ft_expand_one_btw_quot(tmp, envcp, x);
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

char	*ft_until_next_quot(t_list *tmp, t_list *end, t_list **envcp, t_data *x)
{
	char	*word;
	char	*btw_quot;

	word = NULL;
	btw_quot = NULL;
	while (tmp && tmp != end && ((t_words *) tmp->content)->token == TOK_QUOT)
		tmp = tmp->next;
	while (tmp && tmp != end)//((t_words *) tmp->content)->token != TOK_QUOT)
	{
		if (((t_words *) tmp->content)->token == TOK_WORD)
		{
			word = btw_quot;
			btw_quot = ft_strjoin(word, ((t_words *) tmp->content)->word);
			free(word);
		}
		else if (((t_words *) tmp->content)->token == TOK_DOLL)
			btw_quot = doll_btw_quot(&tmp, btw_quot, envcp, x);
		tmp = tmp->next;
	}
	return (btw_quot);
}

int	check_intern_d_quot(t_list *end)
{
	int	check;

	check = 0;
	if (end && (t_words *) end->content
		&& ((t_words *) end->content)->token != TOK_QUOT
		&& end->next
		&& ((t_words *) end->next->content)->token == TOK_QUOT
		&& end->next->next
		&& ((t_words *) end->next->next->content)->token == TOK_QUOT)
		check = 1;
	return (check);
}

t_list	*ft_find_end_quot(t_list *af_quot)
{
	t_list	*end;
	t_list	*new;

	new = NULL;
	if (af_quot)
		end = af_quot;
	else
		return (NULL);
	while (end && ((t_words *) end->content)->token == TOK_QUOT && (end->next &&(((t_words *) end->next->content)->token != TOK_SPAC && check_redir(end->next) == 1)))
		end = end->next;
	while (end && end->next && ((t_words *) end->next->content)->token != TOK_SPAC && check_redir(end->next) == 1)
		end = end->next;
	if (end)
		printf("2. end = %s,\n", ((t_words *) end->content)->word);
	if (!end || (end && ((t_words *) end->content)->token == TOK_QUOT))
		return (end);
	else if (end && ((t_words *) end->content)->token == TOK_WORD)
	{
		new = ft_lstnew((void *) words_init("\"", TOK_QUOT));
		ft_insert(end, new);
		printf("1. end = %s,\n", ((t_words *) end->content)->word);
		printf("1. new = %s,\n", ((t_words *) new->content)->word);
	
		end = end->next;
	}
	if (end)
		printf("1. end = %s,\n", ((t_words *) end->content)->word);
	else
		printf("(null)\n");
	return (end);
}
