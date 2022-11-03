/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:50:32 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 22:20:33 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_list *cmd, t_list **cpenv, t_data *x)
{
	char	*tmp;

	(void)cpenv;
	(void)cmd;
	(void)x;
	tmp = getcwd(NULL, 0);
	dprintf(2, "pwd = %s\n", tmp);
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	free(tmp);
	return (EXIT_SUCCESS);
}
