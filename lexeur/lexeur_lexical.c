/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_lexical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:19:08 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/17 20:37:18 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_words	*words_init(char *word, int token)
{
	t_words	*list;

	list = malloc(sizeof(t_words));
	if (!list)
		return (NULL);
	list->word = ft_strdup(word);
	list->token = token;
	return (list);
}

void	diff_doll(t_list **tmp)
{
	if (((t_letters *)(*tmp)->content)->token == TOK_DOLL
		&& (((*tmp)->next
		&& ((t_letters *)(*tmp)->next->content)->token == TOK_SPAC)
			|| !((*tmp)->next)
			|| ((t_letters *)(*tmp)->next->content)->token == TOK_PIPE))
		((t_letters *)(*tmp)->content)->token = TOK_WORD;
	if (((t_letters *)(*tmp)->content)->token == TOK_DOLL
		&& (((*tmp)->next
		&& ((t_letters *)(*tmp)->next->content)->token == TOK_QUOT)
			|| !((*tmp)->next))
		&& (((*tmp)->next->next
		&& ((t_letters *)((*tmp)->next->next)->content)->token == TOK_SPAC)
			|| !((*tmp)->next->next)))
		((t_letters *)(*tmp)->content)->token = TOK_WORD;
	if (((t_letters *)(*tmp)->content)->token == TOK_DOLL
		&& (((*tmp)->next
		&& ((t_letters *)(*tmp)->next->content)->token == TOK_QUOT)
			|| !((*tmp)->next)))
		*tmp = (*tmp)->next;
}

int	put_one_space(t_list **tmp, t_list **lst_words, t_list *new)
{
	char	*word;
	int		token;

	word = NULL;
	while (*tmp && (*tmp)->next
		&& ((t_letters *)(*tmp)->next->content)->token == TOK_SPAC
		&& (((t_letters *)(*tmp)->content)->token == TOK_SPAC))
		*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->next
		&& (((t_letters *)(*tmp)->content)->token == TOK_SPAC))
	{
		token = ((t_letters *)(*tmp)->content)->token;
		new = ft_lstnew((void *) words_init(" ", token));
		ft_lstadd_back(lst_words, new);
		free(word);
		*tmp = (*tmp)->next;
		return (1);
	}
	else if (!((*tmp)->next)
		&& (((t_letters *)(*tmp)->content)->token == TOK_SPAC))
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	put_word(t_list **lst_words, t_list **tmp)
{
	t_list		*new;
//	t_list		*swp;
	int			len;
	int			token;
	char		*word;

	token = ((t_letters *)(*tmp)->content)->token;
	word = NULL;
	new = NULL;
	if (token == TOK_QUOT)
		len = 42;
	else
		len = len_group_letters(tmp);
//	printf("len = %i\n", len);
	word = build_word(len, tmp);
	new = ft_lstnew((void *) words_init(word, token));
	ft_lstadd_back(lst_words, new);
	free(word);
/*	if (token == TOK_QUOT)
	{
		*tmp = (*tmp)->next;
//		free(*tmp);
//		*tmp = (*tmp)->next;
	}*/
}

void	group_letters(t_list **lst_letters, t_list **lst_words)
{
	t_list		*tmp;
	t_list		*new;

	*lst_words = NULL;
	tmp = *lst_letters;
	new = NULL;
	while (tmp)
	{
		if (tmp && put_one_space(&tmp, lst_words, new) == 0)
		{
			diff_doll(&tmp);
			put_word(lst_words, &tmp);
		}
	}
}
