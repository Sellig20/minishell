/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:25 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/09 21:48:30 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len_words(t_list *tmp, t_list *end)
{
	t_list	*tmp2;
	int		j;

	j = 0;
	tmp2 = tmp;
	while (tmp2 && tmp2->content && tmp2 != end)
	{
		tmp2 = tmp2->next;
		j++;
	}
	return (j);
}

void	ft_free_w(char **words)
{
	int	i;

	i = 0;
	if (words)
	{
		while (words[i])
			free(words[i++]);
		free(words);
	}
}

void	put_words(char **words, t_list **tmp)
{
	t_list	*new;
	int		i;
	t_list	*tmpbis;

	i = 1;
	tmpbis = *tmp;
	if (!words || !(words[0]))
		return ;
	while (words[i])
	{
		if (ft_strcmp(words[i], "fake") == 0)
		{
			free(words[i]);
			words[i] = NULL;
		}
		new = ft_lstnew((void *) words_init(words[i++], TOK_WORD));
		ft_insert(new, tmpbis);
		(tmpbis) = (tmpbis)->next;
	}
}
