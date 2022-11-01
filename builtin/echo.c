/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:17:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/31 18:44:31 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n_option_yes_not_only(t_list *cmdredir, char *str, int has_writ, t_data *x)
{
	//int	i;
	t_list *cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	//i = 0;
	//dprintf(2, "yes | not only => %s\n", str);
	(void)x;
	ft_putstr_fd(str, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	return (has_writ);
}

int	ft_echo_n_option_yes_only(t_list *cmdredir, char *str, int has_writ, int n_option, t_data *x)
{
	
	//dprintf(2, "yes | only => %s\n", str);
	(void)x;
	n_option = 1;
	if (has_writ > 1)
		ft_putstr_fd(str, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	return (n_option);
}

int	ft_echo_n_option_no(t_list *cmdredir, char *str, int has_writ, t_data *x)
{
	t_list *cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	//dprintf(2, "no | => %s\n", str);
	(void)x;
	ft_putstr_fd(str, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	return (has_writ);
}

int	ft_orga_n(t_list *cmdredir, char *str, int has_writ, int n_option, t_data *x)
{
	int	i;
	t_list *cmd;

	i = 0;
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	cmd = cmd->next;
	while (cmd)
	{
		str = ((t_words *)cmd->content)->word;
		if (ft_strncmp(str, "-n", 2) != 0 || has_writ == 1)
			has_writ = ft_echo_n_option_no(cmdredir, str, has_writ, x);
		else
		{
			while (str[i] && (str[i] == 'n' || str[i] == '-'))
					i++;
			if ((str[i] != 'n' && str[i] != '-' && str[i] != '\0'))
				has_writ = ft_echo_n_option_yes_not_only(cmdredir, str, has_writ, x);
			else
				n_option = ft_echo_n_option_yes_only(cmdredir, str, has_writ, n_option, x);
		}
		cmd = cmd->next;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	char	*str;
	int		n_option;
	int		has_writ;
	(void)cpenv;

	has_writ = 0;
	n_option = 0;
	t_list *cmd;
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	if (!cmd->next)
		return (ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]), EXIT_FAILURE);
	str = NULL;
	if (ft_orga_n(cmdredir, str, has_writ, n_option, x) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
