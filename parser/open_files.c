/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:21 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 00:16:36 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_read_infile(char *infile, t_data *x)
{
	int	file;
	int	errno;

	file = 0;
	if (infile == NULL)
		return (-1);
	file = open(infile, O_RDONLY);
	if (file < 0)
	{
		x->flag_file_down = 42;
		ft_putstr_fd("Minimichel : ", 2);
		perror(infile);
		ft_close_files(x);
		if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		{
			if (x->flag_redir_builtin == 1)
				return (EXIT_SUCCESS);
			ft_lstclear(x->cpv, ft_free_words);
			ft_exit_bis("1", x);
		}
		else
			g_status = 1;
	}
	x->count_files++;
	return (file);
}

int	ft_read_outfile_append(char *outfile, t_data *x)
{
	int	file;

	if (outfile == NULL)
		return (-1);
	file = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file < 0)
	{
		x->flag_file_down = 42;
		ft_putstr_fd("Minimichel : ", 2);
		perror (outfile);
		if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		{
			if (x->flag_redir_builtin == 1)
				return (EXIT_SUCCESS);
			ft_lstclear(x->cpv, ft_free_words);
			ft_exit_bis("1", x);
		}
		else
			g_status = 1;
	}
	x->count_files++;
	return (file);
}

int	ft_read_outfile(char *outfile, t_data *x)
{
	int	file;

	if (outfile == NULL)
		return (-1);
	file = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
	{
		x->flag_file_down = 42;
		ft_putstr_fd("Minimichel : ", 2);
		perror (outfile);
		if (x->flag_no_pipe_no_cmd_ok_redir == 0)
		{
			if (x->flag_redir_builtin == 1)
				return (EXIT_SUCCESS);
			ft_lstclear(x->cpv, ft_free_words);
			ft_exit_bis("1", x);
		}
		else
			g_status = 1;
	}
	x->count_files++;
	return (file);
}
