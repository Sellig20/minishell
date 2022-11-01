/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_lexical_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:46:13 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/17 14:58:11 by evsuits          ###   ########.fr       */
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

char	*build_word(int len, t_list **tmp)
{
	char	*word;
	int		index_word;

	index_word = 0;
	if (len < 1)
		return (NULL);
	if (len == 42)
	{
		word = malloc(sizeof(char) * 2);
		word[0] = ((t_letters *)(*tmp)->content)->letter;
		word[1] = '\0';
		*tmp = (*tmp)->next;
	}
	else
	{
		word = malloc(sizeof(char) * (len + 1));
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
