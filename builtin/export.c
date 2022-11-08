/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:25 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/08 19:26:32 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_exp(t_list **exp, t_list *cmdredir)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*after_eq;
	int		index_eq;

	tmp = *exp;
	while (tmp)
	{
		content = (t_words *) tmp->content;
		if (content->token == TOK_ENV)
		{
			index_eq = check_if_equal(content->word);
			before_eq = ft_strndup(content->word, index_eq);
			after_eq = ft_substr(content->word,
					index_eq + 1, ft_strlen(content->word));
			write_exp_one(before_eq, after_eq, cmdredir);
			free(before_eq);
			free(after_eq);
		}
		else
			write_exp_two(content->word, cmdredir);
		tmp = tmp->next;
	}
}

void	env_to_exp(t_list **tmp_exp, t_words *content, t_list **exp)
{
	t_list	*new;

	new = NULL;
	(void) new;
	if (ft_strcmp(((t_words *)(*tmp_exp)->content)->word, content->word) > 0)
	{
		new = ft_lstnew((void *) words_init(content->word, content->token));
		ft_lstadd_front(exp, new);
	}
	else if ((*tmp_exp)->next)
	{
		while ((*tmp_exp)->next
			&& ft_strcmp(((t_words *)(*tmp_exp)->next->content)->word,
			content->word) < 0)
			*tmp_exp = (*tmp_exp)->next;
		new = ft_lstnew((void *) words_init(content->word, content->token));
		ft_insert(new, *tmp_exp);
	}
}

void	ft_put_export(t_list **cpenv, t_list *cmdredir)
{
	t_list	*tmp;
	t_words	*content;
	t_list	**exp;
	t_list	*tmp_exp;

	tmp = *cpenv;
	exp = malloc(sizeof(t_list *));
	if (!exp)
		return ;
	content = (t_words *) tmp->content;
	*exp = ft_lstnew((void *)words_init(content->word, content->token));
	tmp_exp = *cpenv;
	tmp = tmp->next;
	while (tmp)
	{
		content = (t_words *) tmp->content;
		tmp_exp = *exp;
		env_to_exp(&tmp_exp, content, exp);
		tmp = tmp->next;
	}
	ft_write_exp(exp, cmdredir);
	ft_lstclear(exp, ft_free_words);
}

int	ft_export(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	int		index_eq;
	int		err;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	err = 0;
	(void)x;
	if (!(cmd->next) || !(((t_words *)cmd->next->content)->word))
		return (ft_put_export(cpenv, cmdredir), err);
	cmd = cmd->next;
	while (cmd)
	{
		index_eq = check_if_equal(((t_words *)cmd->content)->word);
		if ((index_eq == -42
				|| check_first_alpha(((t_words *)cmd->content)->word) != 0
				|| check_alnum(((t_words *)cmd->content)->word) != 0)
			&& err++ < 42)
			ft_export_error(((t_words *)cmd->content)->word);
		else
			call_case(index_eq, (t_words *)cmd->content, cpenv);
		cmd = cmd->next;
	}
	return (err);
}
