/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_organisation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:37:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/01 19:38:13 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_organisation(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	int		nb_cmd;

	tmp = *cmdredir;
	nb_cmd = ft_nb_cmd(&tmp);
	ft_heredoc(&tmp, x, cpenv);
	if (tmp->next)
	{
		ft_execution_pipe(&tmp, cpenv, x, nb_cmd);
		ft_waitpid(&tmp, x);
	}
	else
		ft_execution_no_pipe(&tmp, cpenv, x);
}
