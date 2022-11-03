/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:38:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 15:57:17 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_return_duped(t_list *portion, t_list *dup)
{
	t_list	**tmp_dup;
	t_list	*new;

	tmp_dup = &dup;
	new = ft_lstnew((void *)words_init(((t_words *)portion->content)->word,
				((t_words *)portion->content)->token));
	tmp_dup = (t_list **)ft_lstadd_back2(tmp_dup, new);
	return (*tmp_dup);
}

t_list	**ft_dupcmd(t_list *portion)
{
	t_list	**dup;

	dup = malloc(sizeof(t_list *));
	if (!dup)
		return (NULL);
	*dup = NULL;
	if (!portion)
		return (NULL);
	while (portion)
	{
		if (ft_sort_cmd(portion) == 1)
			break ;
		if (ft_check_cmd_followed(portion) == 1)
			portion = portion->next->next;
		if (ft_check_dollar_followed(portion) == 1)
			portion = portion->next->next->next;
		else
			*dup = ft_return_duped(portion, *dup);
		portion = portion->next;
	}
	if (!(*dup))
		(*dup) = ft_lstnew(NULL);
	return (dup);
}

t_list	**ft_dupredir(t_list *portion)
{
	t_list	**dup;

	dup = malloc(sizeof(t_list *));
	if (!dup)
		return (NULL);
	*dup = NULL;
	if (!portion)
		return (NULL);
	while (portion)
	{
		if (!(portion->next))
			break ;
		if (((t_words *)portion->content)->token != TOK_WORD
			&& ((t_words *)portion->content)->token != TOK_DOLL)
		{
			*dup = ft_return_duped(portion, *dup);
			portion = portion->next;
			*dup = ft_return_duped(portion, *dup);
		}
		portion = portion->next;
	}
	if (!(*dup))
		(*dup) = ft_lstnew(NULL);
	return (dup);
}

t_cmdredir	*cmdredir_init(t_list *btw_pipes)
{
	t_cmdredir	*cmdredir;
	t_list		**remplir_cmd;
	t_list		**remplir_redir;

	remplir_cmd = NULL;
	remplir_redir = NULL;
	if (!btw_pipes)
		return (NULL);
	cmdredir = malloc(sizeof(t_cmdredir));
	if (!cmdredir)
		return (NULL);
	remplir_cmd = ft_dupcmd(btw_pipes);
	remplir_redir = ft_dupredir(btw_pipes);
	cmdredir->cmd = (*remplir_cmd);
	cmdredir->redirection = (*remplir_redir);
	cmdredir->process_id = -2;
	free(remplir_cmd);
	free(remplir_redir);
	return (cmdredir);
}

void	ft_sep_cmd_redir(t_list **btw_pipes, t_list **cmdredir)
{
	t_list	*btw;
	t_list	*new;

	*cmdredir = NULL;
	btw = *btw_pipes;
	new = NULL;
	while (btw)
	{
		new = ft_lstnew((void *)
				cmdredir_init((t_list *)((t_btw_pipes *)btw->content)
					->portion_words));
		cmdredir = (t_list **)ft_lstadd_back2(cmdredir, new);
		btw = btw->next;
	}
}
