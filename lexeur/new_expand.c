/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:44:28 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/14 23:14:25 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_btw_del(t_list *end, t_list **start)
{
	t_list	*swp;

	swp = NULL;
	if (start == NULL || *start == NULL)
		return ;
	while (*start && ((!end) || (end && *start != end)))
	{
		if ((*start)->next)
			swp = (*start)->next;
		else
			swp = NULL;
		ft_lstdelone(*start, ft_free_words);
		(*start) = swp;
	}
}

static void	first_word(t_list **tmp, t_list **lst, t_list **envcp, t_data *x)
{
	char	**words;
	t_list	*new;
	t_list	*end;

	x->checkbis = 0;
	end = find_end_del(*tmp);
	words = until_next_del(*tmp, end, envcp, x);
	delete_btw_del(end, tmp);
	if (!words)
		words[0] = ft_calloc(sizeof(char), 1);
	words[0] = put_null(words[0], x);
	new = put_new(x, words[0]);
	if (!end)
		*lst = new;
	else
	{
		*lst = end;
		ft_lstadd_front(lst, new);
		(*lst)->next = end;
	}
	*tmp = *lst;
	insert_words(words, tmp, x);
}

static void	other_word(t_list **tmp, t_list **envcp, t_data *x)
{
	t_list	*start;
	t_list	*end;
	char	**words;
	t_list	*new;
	int		i;

	i = 0;
	x->checkbis = 0;
	start = (*tmp)->next;
	end = find_end_del(start);
	words = until_next_del(start, end, envcp, x);
	delete_btw_del(end, &start);
	while (words[i])
	{
		words[i] = put_null(words[i], x);
		new = put_new(x, words[i]);
		ft_insert(new, *tmp);
		*tmp = (*tmp)->next;
		i++;
	}
	if (end && end->next)
		(*tmp)->next = end;
	else
		(*tmp)->next = NULL;
	free(words);
}

void	new_expand(t_list **lst_words, t_list **envcp, t_data *x)
{
	t_list	*tmp;

	tmp = *lst_words;
	ft_check_ambi(&tmp, x);
	if (tmp && check_del(tmp) == 0)
		first_word(&tmp, lst_words, envcp, x);
	while (tmp && tmp->next)
	{
		x->file = 0;
		if (check_redir(tmp) == 0
			&& ((t_words *)tmp->next->content)->token == TOK_SPAC)
		{
			x->file = 42;
			tmp = tmp->next;
		}
		if (tmp->next && check_del(tmp->next) == 0)
		{
			if (check_redir(tmp) == 0)
				x->file = 42;
			other_word(&tmp, envcp, x);
		}
		else
			tmp = tmp->next;
	}
}
