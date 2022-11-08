/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/08 18:18:09 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_is_is_builtin(char *word)
{
	int	i;

	i = 0;
	if (!word)
		return (EXIT_FAILURE);
	while (g_lookup[i].b != 0)
	{
		if (ft_strcmp(word, g_lookup[i].b) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_fonction(t_list *cmd, t_list **cpenv, t_data *x)
{
	(void)cmd;
	(void)cpenv;
	(void)x;
	return (0);
}

int	ft_go_builtin(t_list **cmdredir, t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*tmp_cmd;

	tmp = *cmdredir;
	tmp_cmd = *cmd;
	if (ft_strcmp(((t_words *)tmp_cmd->content)->word,
			g_lookup[x->builtin].b) == 0)
	{
		g_lookup[x->builtin].fonction(tmp, cpenv, x);
		g_status = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_is_builtin(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;
	t_list	*redir;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (ft_is_is_builtin(((t_words *)cmd->content)->word) == 0)
	{
		x->flag_redir = 1;
		while (redir)
		{
			ft_loop_redirections_prot(&redir, x);
			redir = redir->next;
		}
		while ((g_lookup[x->builtin].b != 0))
		{
			if (ft_go_builtin(&tmp, &cmd, x, cpenv) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			x->builtin++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
