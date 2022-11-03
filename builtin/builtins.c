/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/03 22:18:56 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_is_builtin(char *word, int i)
{
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

int	ft_is_builtin(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;
	int		i;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	i = 0;
	if (ft_is_is_builtin(((t_words *)cmd->content)->word, i) == 0)
	{
		x->flag_redir = 1;
		ft_no_pipe_redirection_in((&((t_cmdredir *)tmp->content)->redirection), x);
		ft_no_pipe_redirection_out((&((t_cmdredir *)tmp->content)->redirection), x);
		while((g_lookup[i].b != 0))
		{
			if (ft_strcmp(((t_words *)cmd->content)->word, g_lookup[i].b) == 0)
			{
				g_lookup[i].fonction(tmp, cpenv, x);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
