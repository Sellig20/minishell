/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:56:47 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 22:48:39 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_echo(char *str, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
		ft_putstr_fd(str, x->outfile);
	else
		ft_putstr_fd(str, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
}

int	ft_echo_not_n_only(t_list *cmdredir, char *str, t_data *x)
{
	t_list	*cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	ft_print_echo(str, cmdredir, x);
	x->has_writ = 1;
	if (cmd->next && x->finish == 0)
		ft_print_echo(" ", cmdredir, x);
	return (x->has_writ);
}

int	ft_echo_n_opt(t_list *cmdredir, char *str, t_data *x)
{
	x->echo_opt = 1;
	if (x->has_writ > 1)
		ft_print_echo(str, cmdredir, x);
	return (x->echo_opt);
}

int	ft_echo_n_option_no(t_list *cmdredir, char *str, t_data *x)
{
	t_list	*cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	(void)x;
	ft_print_echo(str, cmdredir, x);
	x->has_writ = 1;
	if (cmd->next && x->finish == 0)
		ft_print_echo(" ", cmdredir, x);
	return (x->has_writ);
}

int	ft_strlenlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
