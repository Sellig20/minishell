/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_no_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:39:40 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 06:09:48 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_redirection_in(int infile)
{
	dup2(infile, STDIN_FILENO);
	close(infile);
}

void	ft_redirection_out(int outfile)
{
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

void	ft_annexe_in_out_no_pipe(t_list **list, t_data *x)
{
	t_list	*tmp;

	tmp = *list;
	if (x->redir_key == 1)
	{
		x->infile = ft_read_infile(((t_words *)tmp->next->content)->word, x);
		if (x->flag_redir == 1)
		{
			if (x->flag_no_pipe_no_cmd_ok_redir == 1)
			{
				if (x->infile)
					close(x->infile);
				if (x->outfile)
					close(x->outfile);
			}
			return ;
		}
		else
			ft_redirection_in(x->infile);
	}
	if (x->redir_key == 2)
	{
		x->outfile = ft_read_outfile(((t_words *)tmp->next->content)->word, x);
		if (x->flag_redir == 1)
		{
			if (x->flag_no_pipe_no_cmd_ok_redir == 1)
			{
				if (x->infile)
					close(x->infile);
				if (x->outfile)
					close(x->outfile);
			}
			return ;
		}
		else
			ft_redirection_out(x->outfile);
	}
}

void	ft_no_pipe_redirection_in(t_list **redir, t_data *x)
{
	t_list	*tmp;

	tmp = *redir;
	x->redir_key = 1;
	if (((t_words *)tmp->content) == NULL)
		return ;
	while (tmp)
	{
		if (((t_words *)tmp->content)->token == TOK_FROM)
			ft_annexe_in_out_no_pipe(&tmp, x);
		tmp = tmp->next;
	}
}

void	ft_no_pipe_redirection_out(t_list **redir, t_data *x)
{
	t_list	*tmp;

	tmp = *redir;
	x->redir_key = 2;
	if (((t_words *)tmp->content) == NULL)
		return ;
	if (((t_words *)tmp->content)->token == TOK_TOTO)
	{
		x->outfile = ft_read_outfile_append(((t_words *)
					tmp->next->content)->word, x);
		if (x->flag_redir == 1)
			return ;
		else
			ft_redirection_out(x->outfile);
	}
	else if (((t_words *)tmp->content)->token == TOK_TO)
		ft_annexe_in_out_no_pipe(&tmp, x);
}
