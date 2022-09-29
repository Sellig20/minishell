/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_lexical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:19:08 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:05:10 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_group_letters(t_list **lst_letters)
{
	t_list	*tmp;
	int		len;

	tmp = *lst_letters;
	if (!tmp)
		return (0);
	len = 1;
	while (tmp->next && ((t_letters *) tmp->content)->token
		== ((t_letters *) tmp->next->content)->token)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

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

void	visualize_t_words(t_list **lst_words)
{
	t_list	*tmp;
	int		i;

	tmp = *lst_words;
	i = 0;
	while (tmp->next)
	{
		printf("1.maillon num %i : word = %s, token = %i\n", i, ((t_words *)tmp->content)->word, ((t_words *) tmp->content)->token);
		tmp = tmp->next;
		i++;
	}
	printf("2.maillon num %i : word = %s, token = %i\n", i, ((t_words *) tmp->content)->word, ((t_words *) tmp->content)->token);
}

char	*build_word(int len, t_list **tmp)
{
	char	*word;
	int		index_word;

	index_word = 0;
	if (len < 1)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (index_word < len)
	{
		word[index_word] = ((t_letters *)(*tmp)->content)->letter;
		index_word++;
		*tmp = (*tmp)->next;
	}
	word[index_word] = '\0';
	return (word);
}

void	group_letters(t_list **lst_letters, t_list **lst_words)
{
	t_list		*tmp;
	t_list		*new;
	int			len;
	int			token;
	char		*word;

	*lst_words = NULL;
	word = NULL;
	tmp = *lst_letters;
	len = 0;
	while (tmp)
	{
		while (tmp && (((t_letters *) tmp->content)->token == TOK_SPAC
				|| ((t_letters *) tmp->content)->token == TOK_QUOT))
			tmp = tmp->next;
		if (tmp)
		{
			if (((t_letters *) tmp->content)->token == TOK_DOLL
				&& ((tmp->next && ((t_letters *)(tmp->next)->content)->token == TOK_SPAC)
				|| !(tmp->next) || ((t_letters *)tmp->next->content)->token == TOK_PIPE))
				((t_letters *)tmp->content)->token = TOK_WORD;
			if (((t_letters *)tmp->content)->token == TOK_DOLL
				&& ((tmp->next && ((t_letters *)(tmp->next)->content)->token == TOK_QUOT)
				|| !(tmp->next)))
				tmp = tmp->next;
			else
			{
				token = ((t_letters *) tmp->content)->token;
				len = len_group_letters(&tmp);
				word = build_word(len, &tmp);
				new = ft_lstnew((void *) words_init(word, token));
				ft_lstadd_back(lst_words, new);
				free(word);
			}
		}
	}
}
