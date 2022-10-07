/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:34 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:01:30 by evsuits          ###   ########.fr       */
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
		case_pl_eq(index_eq, content->word, cpenv);
}

void	case_no_eq(char *cmd, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*new;
	t_words	*content;
	char	*with_eq;
	int		check;

	tmp = *cpenv;
	content = (t_words *)tmp->content;
	check = 0;
	new = NULL;
	with_eq = ft_strjoin(cmd, "=");
	while (tmp && check == 0)
	{
		content = (t_words *)tmp->content;
		if (strcmp(cmd, content->word) == 0
			|| ft_strncmp(with_eq, content->word, ft_strlen(with_eq)) == 0)
			check++;
		tmp = tmp->next;
	}
	if (check == 0)
	{
		new = ft_lstnew((void *) ft_init_cpenv(cmd, TOK_EXP));
		ft_lstadd_back(cpenv, new);
	}
	free(with_eq);
}

void	case_eq(int index_eq, char *cmd, t_list **cpenv)
{
	t_list	*new;
	char	*with_eq;

	new = NULL;
	with_eq = ft_substr(cmd, 0, index_eq);
	ft_unset_first(*cpenv, with_eq);
	ft_unset_others(*cpenv, with_eq);
	new = ft_lstnew((void *) ft_init_cpenv(cmd, TOK_ENV));
	free(with_eq);
	ft_lstadd_back(cpenv, new);
}

void	case_pl_eq(int index_eq, char *cmd, t_list **cpenv)
{
	t_list	*new;
	t_list	*tmp;
	t_words	*content;
	char	*with_eq;
	char	*before_eq;
	char	*after_eq;
	int		i;

	new = NULL;
	index_eq *= (-1);
	tmp = *cpenv;
	content = (t_words *) tmp->content;
	before_eq = ft_strndup(cmd, index_eq - 1);
	with_eq = ft_strjoin(before_eq, "=");
	free(before_eq);
	after_eq = ft_substr(cmd, index_eq + 1, ft_strlen(cmd));
	i = 0;
	while (tmp && i == 0)
	{
		before_eq = ft_strndup(cmd, index_eq - 1);
		content = (t_words *) tmp->content;
		if (strcmp(before_eq, content->word) == 0)
		{
			free(before_eq);
			before_eq = ft_strjoin(with_eq, after_eq);
			free(content->word);
			content->word = ft_strndup(before_eq, ft_strlen(before_eq));
			i = 1;
		}
		else if (ft_strncmp(with_eq, content->word, index_eq) == 0)
		{
			free(before_eq);
			before_eq = ft_strjoin(content->word, after_eq);
			free(content->word);
			content->word = ft_strndup(before_eq, ft_strlen(before_eq));
			i = 1;
		}
		free(before_eq);
		tmp = tmp->next;
	}
	if (i == 0)
	{
		before_eq = ft_strjoin(with_eq, after_eq);
		new = ft_lstnew((void *) words_init(before_eq, TOK_ENV));
		ft_lstadd_back(cpenv, new);
		free(before_eq);
	}
	free(after_eq);
	free(with_eq);
}
