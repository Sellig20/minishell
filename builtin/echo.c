/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:17:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 22:11:20 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strn(char *str, t_data *x)
{
	int	i;

	i = 1;
	x->only_n = 0;
	if (ft_strlenlen(str) == 1)
		return (0);
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] == 'n')
				x->only_n++;
			else
				x->bad_friend++;
			i++;
		}
	}
	x->only_n++;
	if (ft_strlenlen(str) == x->only_n && x->bad_friend == 0)
		return (1);
	else if (x->bad_friend > 0)
		return (2);
	return (0);
}

int	ft_orga_n(t_list *cmdredir, char *str, t_data *x)
{
	t_list	*cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	cmd = cmd->next;
	while (cmd)
	{
		if (!(cmd->next))
			x->finish = 1;
		str = ((t_words *)cmd->content)->word;
		x->res_echo = ft_strn(str, x);
		if (x->res_echo == 0 || x->has_writ == 1)
			x->has_writ = ft_echo_n_option_no(cmdredir, str, x);
		else
		{
			if (x->res_echo == 2)
				x->has_writ = ft_echo_n_option_yes_not_only(cmdredir, str, x);
			else if (x->res_echo == 1)
				x->echo_opt = ft_echo_n_option_yes_only(cmdredir, str, x);
		}
		cmd = cmd->next;
	}
	if (x->echo_opt == 0)
		ft_print_echo("\n", cmdredir, x);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	char	*str;

	(void)cpenv;
	x->has_writ = 0;
	x->echo_opt = 0;
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	if (!cmd->next)
	{
		if (x->outfile > 2)
			return (ft_putstr_fd("\n", x->outfile), EXIT_FAILURE);
		else
			return (ft_putstr_fd("\n",
					((t_cmdredir *)cmdredir->content)->fd_cmd[1]),
				EXIT_FAILURE);
	}
	str = NULL;
	if (ft_orga_n(cmdredir, str, x) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
