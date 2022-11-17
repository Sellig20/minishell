/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_error_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:54:44 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 02:03:54 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_error_nsfod(char *infile, t_data *x)
{
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	tmp = ft_strjoin(infile, ": No such file or directory");
	tmp1 = ft_strjoin("Minimichel: ", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
	free(tmp1);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		ft_exit_bis("1", x);
	else
		g_status = 0;
	return (false);
}

int	ft_exist_error_directory(char *infile, t_data *x)
{
	ft_putstr_fd("Minimichel: ", 2);
	write(2, infile, ft_strlen(infile));
	write(2, ": Not a directory", 18);
	write(2, "\n", 1);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
	{
		ft_lstclear(x->cpv, ft_free_words);
		ft_exit_bis("1", x);
	}
	else
		g_status = 0;
	return (false);
}

int	ft_perm_error(char *file, t_data *x, int nb, t_list **cpenv)
{
	ft_putstr_fd("Minimichel: ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": permission denied", 19);
	write(2, "\n", 1);
	if (nb == 2)
		return (ftclosep(x), ft_exit_bis("1", x), 0);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0)
	{
		ft_lstclear(cpenv, ft_free_words);
		ft_exit_bis("1", x);
	}
	else
		g_status = 0;
	return (false);
}

void	ft_isad_error(char *file, t_data *x, t_list **cpenv)
{
	ft_putstr_fd("Minimichel: ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": Is a directory", 16);
	write(2, "\n", 1);
	if (x->flag_no_pipe_no_cmd_ok_redir == 0 && x->flag_uxu != 5)
	{
		ft_lstclear(cpenv, ft_free_words);
		ft_exit_bis("1", x);
	}
	else if (x->flag_uxu == 5)
		g_status = 1;
	else
		g_status = 0;
}
