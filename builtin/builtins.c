/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/05 06:17:44 by jecolmou         ###   ########.fr       */
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

int	ft_is_builtin(t_list **cmdredir, t_data *x, t_list **cpenv, int nb)
{
	t_list	*tmp;
	t_list	*cmd;
	t_list	*redir;
	int		i;
	(void)nb;
	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	i = 0;
	if (ft_is_is_builtin(((t_words *)cmd->content)->word) == 0)
	{
		x->flag_redir = 1;
		while (redir)
		{
			if (ft_is_redirection_in(&redir) == 1)
			{
				if (x->infile && x->count_files > 0)
					close(x->infile);
				ft_no_pipe_redirection_in(&redir, x);
			}
			if (ft_is_redirection_out(&redir) == 1)
			{
				if (x->outfile && x->count_files > 0)
					close(x->outfile);
				ft_no_pipe_redirection_out(&redir, x);
			}
			redir = redir->next;
		}
		while((g_lookup[i].b != 0))
		{
			if (ft_strcmp(((t_words *)cmd->content)->word, g_lookup[i].b) == 0)
			{
				g_lookup[i].fonction(tmp, cpenv, x);
				g_status = 0;
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
