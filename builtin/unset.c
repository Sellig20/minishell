/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:18 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/26 17:44:38 by evsuits          ###   ########.fr       */
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
		if (ft_strncmp(before_eq, content->word, ft_strlen(before_eq) - 1) == 0 && i++ == 0)
		{
			if (tmp->next->next)
				swp = tmp->next->next;
			else
				swp = NULL;
			ft_lstdelone(tmp->next, ft_free_words);
			tmp->next = swp;
		}
		tmp = tmp->next;
	}
	if (i == 0 && tmp && content && ft_strncmp(before_eq,
			content->word, ft_strlen(before_eq) - 1) == 0 && i++ == 0)
	{
		ft_lstdelone(tmp, ft_free_words);
		tmp = NULL;
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

int	ft_unset(t_list *cmd, t_list **cpenv, t_data *x)
{
	t_words	*content;

	(void) x;
	if (!(cmd->next))
		return (1);
	cmd = cmd->next;
	while (cmd)
	{
		content = (t_words *) cmd->content;
		if (ft_unset_first(*cpenv, content->word) == 0)
			ft_unset_others(*cpenv, content->word);	
		cmd = cmd->next;
	}
	return (0);
}
