/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_organisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/08 18:19:19 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_organisor(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;

	tmp = *cmdredir;
	ft_heredoc(&tmp, x, cpenv);
	if (tmp->next)
	{
		ft_execution_pipe(&tmp, cpenv, x);
		ft_waitpid(&tmp, x);
	}
	else
		ft_exec_no_pipes(&tmp, cpenv, x);
	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
}
