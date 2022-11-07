/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:41:45 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/01 18:47:01 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nb_cmd(t_list **lst)
{
	int			count;
	t_list		*buffer;

	count = 0;
	buffer = *lst;
	while (buffer)
	{
		buffer = buffer->next;
		count++;
	}
	return (count);
}

void	ft_set_fdcmd(t_list **after_doll, t_data *x)
{
	t_list	*tmp;
	int		j;

	tmp = *after_doll;
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
