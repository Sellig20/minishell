/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:17:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/10 18:17:30 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n_option_yes_not_only(t_list *cmd, char *str, int has_writ)
{
	int	i;

	i = 0;
	ft_putstr_fd(str, 1);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", 1);
	return (has_writ);
}

int	ft_echo_n_option_yes_only(char *str, int has_writ, int n_option)
{
	n_option = 1;
	if (has_writ > 1)
		ft_putstr_fd(str, 1);
	return (n_option);
}

int	ft_echo_n_option_no(t_list *cmd, char *str, int has_writ)
{
	ft_putstr_fd(str, 1);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", 1);
	return (has_writ);
}

void	ft_orga_n(t_list *cmd, char *str, int has_writ, int n_option)
{
	int	i;

	i = 0;
	cmd = cmd->next;
	while (cmd)
	{
		str = ((t_words *)cmd->content)->word;
		if (ft_strncmp(str, "-n", 2) != 0 || has_writ == 1)
			has_writ = ft_echo_n_option_no(cmd, str, has_writ);
		else
		{
			while (str[i] && (str[i] == 'n' || str[i] == '-'))
					i++;
			if ((str[i] != 'n' && str[i] != '-' && str[i] != '\0'))
				has_writ = ft_echo_n_option_yes_not_only(cmd, str, has_writ);
			else
				n_option = ft_echo_n_option_yes_only(str, has_writ, n_option);
		}
		cmd = cmd->next;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(t_list *cmd, t_list **cpenv)
{
	char	*str;
	int		n_option;
	int		has_writ;
	int		i;
	int		shot;

	(void)cpenv;
	has_writ = 0;
	n_option = 0;
	i = 0;
	shot = 0;
	if (!cmd->next)
		return (ft_putstr_fd("\n", 1), EXIT_FAILURE);
	str = NULL;
	ft_orga_n(cmd, str, has_writ, n_option);
	return (EXIT_SUCCESS);
}
