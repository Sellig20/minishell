/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:22:59 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 12:04:12 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_command_not_found(char *cmd)
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
}

int	ft_error_ambigous_redirect(char *word, int len)
{
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	(void)len;
	tmp = ft_strjoin(word, ": ambigous redirect");
	tmp1 = ft_strjoin("Minimichel: ", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
	free(tmp1);
	return (false);
}
