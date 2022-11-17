/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 17:48:39 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_new(t_list **tmp, t_list **dup)
{
	t_list	*new;

	if (!((t_words *)(*tmp)->content))
		new = ft_lstnew((void *) words_init(NULL, TOK_WORD));
	else
		new = ft_lstnew((void *) words_init(((t_words *)(*tmp)->content)->word,
					((t_words *)(*tmp)->content)->token));
	ft_lstadd_back(dup, new);
	*tmp = (*tmp)->next;
}

static	t_list	**ft_dupwords(t_list **tmp)
{
	t_list	*new;
	t_list	**dup;

	dup = malloc(sizeof(t_list *));
	if (!dup)
		return (NULL);
	*dup = NULL;
	if (!tmp || !(*tmp))
		return (free(dup), NULL);
	if (((t_words *)(*tmp)->content)->token == TOK_PIPE)
		(*tmp) = (*tmp)->next;
	while (*tmp && (!((*tmp)->next) || (((*tmp)->next)
				&& ((t_words *)((*tmp)->next)->content)->token != TOK_PIPE)))
		get_new(tmp, dup);
	if (*tmp && (*tmp)->content)
	{
		new = ft_lstnew((void *) words_init(((t_words *)(*tmp)->content)->word,
					((t_words *)(*tmp)->content)->token));
		ft_lstadd_back(dup, new);
		*tmp = (*tmp)->next;
	}
	return (dup);
}

static	t_btw_pipes	*btw_pipes_init(t_list *portion_words)
{
	t_btw_pipes	*new_pipe;

	if (portion_words == NULL)
		return (NULL);
	new_pipe = malloc(sizeof(t_btw_pipes));
	if (!new_pipe)
		return (NULL);
	new_pipe->portion_words = portion_words;
	return (new_pipe);
}

void	sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes)
{
	t_list	*tmp;
	t_list	*new;
	t_list	**dup;

	*lst_btw_pipes = NULL;
	new = NULL;
	tmp = NULL;
	tmp = *lst_words;
	while (tmp)
	{
		dup = ft_dupwords(&tmp);
		new = ft_lstnew((void *)btw_pipes_init(*dup));
		free(dup);
		ft_lstadd_back(lst_btw_pipes, new);
	}
}
