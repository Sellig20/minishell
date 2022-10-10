/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:18 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:01:55 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_others(t_list *tmp, char *before_eq)
{
	t_list	*swp;
	t_words	*content;
	int		i;

	content = (t_words *) tmp->content;
	i = 0;
	while (tmp && tmp->next && i == 0)
	{
		content = (t_words *) tmp->next->content;
		if (ft_strncmp(before_eq, content->word, ft_strlen(before_eq) - 1) == 0)
		{
			swp = tmp->next->next;
			ft_lstdelone(tmp->next, ft_free_words);
			tmp->next = swp;
			i = 1;
		}
		tmp = tmp->next;
	}
	return (i);
}

int	ft_unset_first(t_list *tmp, char *before_eq)
{
	t_list	*swp;
	t_words	*content;
	int		check;

	swp = NULL;
	check = 0;
	content = (t_words *) tmp->content;
	if (ft_strncmp(before_eq, content->word, ft_strlen(before_eq)) == 0)
	{
		swp = tmp->next;
		ft_lstdelone(tmp, ft_free_words);
		tmp = swp;
		check = 1;
	}
	return (check);
}

void	ft_unset(t_list *cmd, t_list **cpenv)
{
	char	*with_eq;
	int		index_eq;
	t_words	*content;

	while (cmd)
	{
		content = (t_words *) cmd->content;
		index_eq = check_if_equal(content->word);
		with_eq = ft_substr(content->word, 0, index_eq);
		ft_unset_first(*cpenv, with_eq);
		ft_unset_others(*cpenv, with_eq);
		free(with_eq);
		cmd = cmd->next;
	}
}
