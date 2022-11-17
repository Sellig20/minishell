/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:34 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/09 22:30:05 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_case(int index_eq, t_words *content, t_list **cpenv)
{
	if (index_eq == 0)
		case_no_eq(content->word, cpenv);
	else if (index_eq > 0)
		case_eq(index_eq, content->word, cpenv);
	else
		case_pl_eq(index_eq, content->word, cpenv, 0);
}

void	case_no_eq(char *cmd, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*new;
	t_words	*content;
	char	*with_eq;
	int		check;

	tmp = *cpenv;
	check = 0;
	new = NULL;
	with_eq = ft_strjoin(cmd, "=");
	while (tmp && check == 0)
	{
		content = (t_words *)tmp->content;
		if (ft_strcmp(cmd, content->word) == 0
			|| ft_strncmp(with_eq, content->word, ft_strlen(with_eq)) == 0)
			check++;
		tmp = tmp->next;
	}
	if (check == 0)
	{
		new = ft_lstnew((void *) words_init(cmd, TOK_EXP));
		ft_lstadd_back(cpenv, new);
	}
	free(with_eq);
}

void	case_eq(int index_eq, char *cmd, t_list **cpenv)
{
	t_list	*new;
	char	*with_eq;

	new = NULL;
	if (!cmd)
		return ;
	with_eq = ft_substr(cmd, 0, index_eq);
	ft_unset_first(cpenv, with_eq);
	ft_unset_others(*cpenv, with_eq);
	new = ft_lstnew((void *) words_init(cmd, TOK_ENV));
	free(with_eq);
	ft_lstadd_back(cpenv, new);
}

int	replace_in_env(t_list **tmp, char *before_eq, char *with_eq, char *after_eq)
{
	char	*swp;
	t_words	*content;

	swp = NULL;
	content = (t_words *)(*tmp)->content;
	if (ft_strncmp(before_eq, content->word,
			ft_strlen(before_eq) + ft_strlen(content->word)) == 0
		|| ft_strncmp(with_eq, content->word, ft_strlen(with_eq)) == 0)
	{
		if (ft_strncmp(before_eq, content->word,
				ft_strlen(before_eq) + ft_strlen(content->word)) == 0)
			swp = ft_strjoin(with_eq, after_eq);
		else
			swp = ft_strjoin(content->word, after_eq);
		free(content->word);
		content->word = ft_strndup(swp, ft_strlen(swp));
		content->token = TOK_ENV;
		return (free(swp), 1);
	}
	*tmp = (*tmp)->next;
	return (free(swp), 0);
}

void	case_pl_eq(int index_eq, char *cmd, t_list **cpenv, int i)
{
	t_list	*new;
	t_list	*tmp;
	char	*with_eq;
	char	*before_eq;
	char	*after_eq;

	new = NULL;
	index_eq *= (-1);
	tmp = *cpenv;
	before_eq = ft_strndup(cmd, index_eq - 1);
	with_eq = ft_strjoin(before_eq, "=");
	after_eq = ft_substr(cmd, index_eq + 1, ft_strlen(cmd));
	while (tmp && i == 0)
		i = replace_in_env(&tmp, before_eq, with_eq, after_eq);
	if (i == 0)
	{
		free(before_eq);
		before_eq = ft_strjoin(with_eq, after_eq);
		new = ft_lstnew((void *) words_init(before_eq, TOK_ENV));
		ft_lstadd_back(cpenv, new);
	}
	return (free(before_eq), free(after_eq), free(with_eq));
}
