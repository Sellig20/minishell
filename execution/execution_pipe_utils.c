/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:41:45 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/02 17:07:27 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

int	ft_is_redirection_in(t_list **redir)
{
	t_list	*tmp_redir;

	tmp_redir = *redir;
	if (((t_words *)tmp_redir->content) == NULL)
		return (0);
	if (ft_strcmp(((t_words *)tmp_redir->content)->word, "<") == 0
		|| ft_strcmp(((t_words *)tmp_redir->content)->word, "<<") == 0)
		return (1);
	else
		return (0);
	return (0);
}

int	ft_is_redirection_out(t_list **redir)
{
	t_list	*tmp_redir;

	tmp_redir = *redir;
	if (((t_words *)tmp_redir->content) == NULL)
		return (0);
	if (ft_strcmp(((t_words *)tmp_redir->content)->word, ">") == 0
		|| ft_strcmp(((t_words *)tmp_redir->content)->word, ">>") == 0)
		return (1);
	else
		return (0);
	return (0);
}

void	ft_connector_redirections(t_list **cmdredir, t_data *x)
{
	t_list	*redir;
	t_list	*tmp;

	tmp = *cmdredir;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	while (redir)
	{
		if (ft_is_redirection_in(&redir) == 1)
			ft_pipe_redirection_in(&tmp, redir, x);
		if (ft_is_redirection_out(&redir) == 1)
			ft_pipe_redirection_out(&tmp, redir, x);
		redir = redir->next;
	}
}

void	ft_connector_std_fdcmd(t_list **cmdredir)
{
	t_list *tmp;

	tmp = *cmdredir;
	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
	{
		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	}
	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
	{
		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
	}
}

int	ft_waitpid(t_list **cmdredir)
{
	t_list	*tmp;

	tmp = *cmdredir;
	while(tmp)
	{
		waitpid(((t_cmdredir *)tmp->content)->process_id, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sig_parent);
		tmp = tmp->next;
	}
	return (0);
}
