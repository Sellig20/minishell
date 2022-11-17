/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:21:49 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/14 23:16:01 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*other_word_annexe(char *word, t_data *x)
{
	t_list	*new;

	if (x->checkbis == 1)
		new = ft_lstnew((void *) words_init(word, TOK_FILE));
	else
		new = ft_lstnew((void *) words_init(word, TOK_WORD));
	return (new);
}

t_list	*put_new(t_data *x, char *word)
{
	t_list	*new;

	if (x->file == 42)
		new = ft_lstnew((void *) words_init(word, TOK_FILE));
	else if (x->checkbis == 2)
		new = ft_lstnew((void *) words_init(word, TOK_OTHER_SPAC));
	else
		new = ft_lstnew((void *) words_init(word, TOK_WORD));
	return (free(word), new);
}

char	*put_null(char *word, t_data *x)
{
	if (!word || ft_strcmp(word, "fake\0") == 0)
	{
		free(word);
		word = malloc(sizeof(char) * 1);
		word[0] = '\0';
	}
	else if (ft_strcmp(word, "fake2\0") == 0)
	{
		x->checkbis = 2;
		free(word);
		word = malloc(sizeof(char) * 2);
		word[0] = ' ';
		word[1] = '\0';
	}
	return (word);
}

void	insert_words(char **words, t_list **tmp, t_data *x)
{
	t_list	*new;
	int		i;

	new = 0;
	i = 1;
	while (words[i])
	{
		words[i] = put_null(words[i], x);
		new = put_new(x, words[i++]);
		ft_insert(new, *tmp);
		(*tmp) = (*tmp)->next;
	}
	free(words);
}
