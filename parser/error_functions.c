/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:59 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 04:36:15 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int g_status;

void	ft_error_command_not_f(char *cmd)
{
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	tmp = ft_strjoin(cmd, ": command not found");
	tmp1 = ft_strjoin("Minimichel: ", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
	free(tmp1);
}

int	ft_error_ambigous_redir(char *word, int len)
{
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	(void)len;
	tmp = ft_strjoin(word, ": ambigous redirect");
	tmp1 = ft_strjoin("Minimichel: $", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
	free(tmp1);
	return (false);
}
