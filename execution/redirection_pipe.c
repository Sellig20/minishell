/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:02:06 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 05:40:39 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_annexe_in_out_pipe(t_list **cmdredir, t_list **redir, t_data *x)
{
	t_list	*tmp;
	t_list	*tmp_redir;

	tmp = *cmdredir;
	tmp_redir = *redir;
	if (x->redir_key == 1)
	{
		x->infile = ft_read_infile(((t_words *)
					tmp_redir->next->content)->word, x);
		if (x->infile < 0)
			ft_error_nsfod(((t_words *)tmp_redir->next->content)->word, x);
		if (x->infile)
			((t_cmdredir *)tmp->content)->fd_cmd[0] = x->infile;
	}
	if (x->redir_key == 2)
	{
		x->outfile = ft_read_outfile(((t_words *)
					tmp_redir->next->content)->word, x);
		if (x->outfile < 0)
			ft_perm_error(((t_words *)tmp_redir->next->content)->word, x);
		if (x->outfile)
			((t_cmdredir *)tmp->content)->fd_cmd[1] = x->outfile;
	}
}

void	ft_pipe_redirection_in(t_list **cmdredir, t_list *redir, t_data *x)
{
	t_list	*tmp;

	tmp = *cmdredir;
	x->redir_key = 1;
	if (((t_words *)tmp->content) == NULL)
		return ;
	if (((t_words *)redir->content)->token == TOK_FRFR)
	{
		if (x->here_infile < 0)
			ft_error_nsfod(((t_words *)tmp->next->content)->word, x);
		((t_cmdredir *) tmp->content)->fd_cmd[0] = x->here_infile;
	}
	else if (((t_words *)redir->content)->token == TOK_FROM)
		ft_annexe_in_out_pipe(&tmp, &redir, x);
	else
		((t_cmdredir *) tmp->content)->fd_cmd[0] = STDIN_FILENO;
}

void	ft_pipe_redirection_out(t_list **after_doll, t_list *redir, t_data *x)
{
	t_list	*tmp;

	tmp = *after_doll;
	x->redir_key = 2;
	if (((t_words *)tmp->content) == NULL)
		return ;
	if (((t_words *)redir->content)->token == TOK_TOTO)
	{
		x->append_outfile = ft_read_outfile_append(((t_words *)
					redir->next->content)->word, x);
		if (x->append_outfile < 0)
			ft_perm_error(((t_words *)tmp->next->content)->word, x);
		((t_cmdredir *) tmp->content)->fd_cmd[1] = x->append_outfile;
	}
	else if (((t_words *)redir->content)->token == TOK_TO)
		ft_annexe_in_out_pipe(&tmp, &redir, x);
	else
		((t_cmdredir *) tmp->content)->fd_cmd[1] = STDOUT_FILENO;
}
