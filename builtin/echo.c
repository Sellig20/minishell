/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:17:56 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/14 18:48:39 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n_option_yes_not_only(t_list *cmd, char *str, int has_writ, t_data *x)
{
	int	i;

	i = 0;
	//dprintf(2, "yes | not only => %s\n", str);
	ft_putstr_fd(str, x->outfile);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", x->outfile);
	return (has_writ);
}

int	ft_echo_n_option_yes_only(char *str, int has_writ, int n_option, t_data *x)
{
	//dprintf(2, "yes | only => %s\n", str);
	n_option = 1;
	if (has_writ > 1)
		ft_putstr_fd(str, x->outfile);
	return (n_option);
}

int	ft_echo_n_option_no(t_list *cmd, char *str, int has_writ, t_data *x)
{
	//dprintf(2, "no | => %s\n", str);
	ft_putstr_fd(str, x->outfile);
	has_writ = 1;
	if (cmd->next)
		ft_putstr_fd(" ", x->outfile);
	return (has_writ);
}

int	ft_orga_n(t_list *cmd, char *str, int has_writ, int n_option, t_data *x)
{
	int	i;

	i = 0;
	cmd = cmd->next;
	while (cmd)
	{
		str = ((t_words *)cmd->content)->word;
		if (ft_strncmp(str, "-n", 2) != 0 || has_writ == 1)
			has_writ = ft_echo_n_option_no(cmd, str, has_writ, x);
		else
		{
			while (str[i] && (str[i] == 'n' || str[i] == '-'))
					i++;
			if ((str[i] != 'n' && str[i] != '-' && str[i] != '\0'))
				has_writ = ft_echo_n_option_yes_not_only(cmd, str, has_writ, x);
			else
				n_option = ft_echo_n_option_yes_only(str, has_writ, n_option, x);
		}
		cmd = cmd->next;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", x->outfile);
	return (EXIT_SUCCESS);
}

int	ft_echo(t_list *cmd, t_list **cpenv, t_data *x)
{
	char	*str;
	int		n_option;
	int		has_writ;
	dprintf(2, "je suis dans le echo de BUILTIN !\n");
	(void)cpenv;
	has_writ = 0;
	n_option = 0;
	if (!cmd->next)
		return (ft_putstr_fd("\n", x->outfile), EXIT_FAILURE);
	str = NULL;
	if (ft_orga_n(cmd, str, has_writ, n_option, x) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
