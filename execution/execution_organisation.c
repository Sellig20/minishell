/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_organisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/02 14:19:54 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_organisation(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;

	tmp = *cmdredir;
	ft_heredoc(&tmp, x, cpenv);
	if (tmp->next)
	{
		ft_execution_pipe(&tmp, cpenv, x);
		ft_waitpid(&tmp);
	}
	else
		ft_execution_no_pipe(&tmp, cpenv, x);
}

int	ft_nb_cmd(t_list **cmdredir)
{
	t_list	*tmp;
	int		count;

	tmp = *cmdredir;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	ft_set_fdcmd(t_list **cmdredir, t_data *x)
{
	t_list	*tmp;
	int		j;

	tmp = *cmdredir;
	x->nb_cmd = ft_nb_cmd(&tmp);
	while (tmp)
	{
		j = 0;
		while (j < x->nb_cmd)
		{
			((t_cmdredir *)tmp->content)->fd_cmd[0] = STDIN_FILENO;
			((t_cmdredir *)tmp->content)->fd_cmd[1] = STDOUT_FILENO;
			j++;
		}
		tmp = tmp->next;
	}
}
