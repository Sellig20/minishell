/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_lexical_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:46:13 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/09 14:04:21 by evsuits          ###   ########.fr       */
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

char	*build_quot(t_list **tmp)
{
	char	*word;

	word = malloc(sizeof(char) * 2);
	if (!word)
		return (NULL);
	word[0] = ((t_letters *)(*tmp)->content)->letter;
	word[1] = '\0';
	*tmp = (*tmp)->next;
	return (word);
}

char	*build_word(int len, t_list **tmp)
{
	char	*word;
	int		index_word;

	index_word = 0;
	if (len < 1 && len != -42)
		return (NULL);
	if (len == -42)
		word = build_quot(tmp);
	else
	{
		word = malloc(sizeof(char) * (len + 1));
		if (!word)
			return (NULL);
		while (index_word < len)
		{
			word[index_word] = ((t_letters *)(*tmp)->content)->letter;
			index_word++;
			*tmp = (*tmp)->next;
		}
		word[index_word] = '\0';
	}
	return (word);
}
