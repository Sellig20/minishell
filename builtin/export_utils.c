/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:45 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/12 19:02:43 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_exp_one(char *beq, char *after_eq, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
	{
		ft_putstr_fd("export ", x->outfile);
		ft_putstr_fd(beq, x->outfile);
		ft_putstr_fd("=", x->outfile);
		ft_putstr_fd(after_eq, x->outfile);
		ft_putstr_fd("\n", x->outfile);
	}
	else
	{
		ft_putstr_fd("export ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd(beq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("=", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd(after_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	}
}

void	write_exp_two(char *content, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
	{
		ft_putstr_fd("export ", x->outfile);
		ft_putstr_fd(content, x->outfile);
		ft_putstr_fd("\n", x->outfile);
	}
	else
	{
		ft_putstr_fd("export ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd(content, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	}
}

int	check_if_equal(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1113090808);
	if (cmd[i] == '+' || cmd[i] == '=')
		return (-42);
	while (cmd[i])
	{
		if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
			return ((i + 1) * (-1));
		if (cmd[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_first_alpha(char *cmd)
{
	if ((cmd[0] >= 'A' && cmd[0] <= 'Z')
		|| (cmd[0] >= 'a' && cmd[0] <= 'z'))
		return (0);
	return (1);
}

int	check_alnum(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '=' || cmd[i] == '+')
		return (1);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
			return (0);
		else if ((cmd[i] < 'A' || cmd[i] > 'Z') && (cmd[i] < 'a'
				|| cmd[i] > 'z') && (cmd[i] < '0' || cmd[i] > '9')
			&& cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
