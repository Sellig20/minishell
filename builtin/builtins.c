/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/31 19:50:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_is_builtin(char *word, int i)
{
	while((g_lookup[i].builtin_name != 0))
	{
		if (ft_strcmp(word, g_lookup[i].builtin_name) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int		ft_fonction(t_list *cmd, t_list **cpenv, t_data *x)
{
	(void)cmd;
	(void)cpenv;
	(void)x;
	return (0);
}

int	ft_is_builtin(t_list **after_doll, t_data *x, t_list **cpenv)
{
	t_list	*after;
	t_list	*tmp_cmd;
	int		i;
	after = *after_doll;
	tmp_cmd = (t_list *)((t_cmdredir *)after->content)->cmd;
	i = 0;
	if (ft_is_is_builtin(((t_words *)tmp_cmd->content)->word, i) == 0)
	{
		x->flag_redir = 1;
		ft_no_pipe_redirection_in((&((t_cmdredir *)after->content)->redirection), x);
		ft_no_pipe_redirection_out((&((t_cmdredir *)after->content)->redirection), x);
		while((g_lookup[i].builtin_name != 0))
		{
			if (ft_strcmp(((t_words *)tmp_cmd->content)->word, g_lookup[i].builtin_name) == 0)
			{
				g_lookup[i].fonction(after, cpenv, x);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
