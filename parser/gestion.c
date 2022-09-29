/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/29 18:43:49 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_command_not_found(char *cmd)
{
	char	*tmp;
	char	*to_return;

	tmp = ft_strjoin("Minimichel : command not found : ", cmd);
	to_return = ft_strjoin(tmp, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
}

int	ft_is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && cmd[i + 1] == '\0')
			return (false);
		i++;
	}
	return (true);
}

int	ft_is_null(char *cmd)
{
	if (ft_strlen(cmd) == 0)
	{
		printf("Error \n");
		return (false);
	}
	else if (ft_is_space(cmd) == 0)
	{
		ft_error_command_not_found(cmd);
		return (false);
	}
	return (1);
}
