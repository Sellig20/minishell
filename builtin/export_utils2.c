/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:22:19 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/08 19:26:53 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_error(char *cmdnext)
{
	write(2, "Minimichel: export: `", 21);
	write(2, cmdnext, ft_strlen(cmdnext));
	write(2, "':not a valid identifier\n", 25);
}

void	write_exp_one(char *before_eq, char *after_eq, t_list *cmdredir)
{
	ft_putstr_fd("export ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd(before_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd("=", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd(after_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
}

void	write_exp_two(char *content, t_list *cmdredir)
{
	ft_putstr_fd("export ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd(content, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
}
