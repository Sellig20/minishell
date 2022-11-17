/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:38:01 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 13:38:21 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_action(t_list *cmdredir, char *str, t_data *x)
{
	if (x->res_echo == 2)
		x->has_writ = ft_echo_not_n_only(cmdredir, str, x);
	else if (x->res_echo == 1)
		x->echo_opt = ft_echo_n_opt(cmdredir, str, x);
}

t_list	*ft_move_echo(t_list *cmd, t_data *x)
{
	if (((t_words *)cmd->next->content)->token != 9)
		x->echo = 0;
	cmd = cmd->next;
	return (cmd);
}

t_list	*ft_echo_quotes(t_list *cmdredir, t_list *cmd, t_data *x)
{
	ft_print_echo(" ", cmdredir, x);
	x->echo = 6;
	if (cmd->next)
		cmd = ft_move_echo(cmd, x);
	else
		return (NULL);
	return (cmd);
}
