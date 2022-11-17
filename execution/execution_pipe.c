/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:16:05 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 18:53:13 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_execution_pipe(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;

	tmp = *cmdredir;
	ft_set_fdcmd(&tmp, x);
	while (tmp)
	{
		if (((t_cmdredir *)tmp->next))
			ft_create_pipe(&tmp, x);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		((t_cmdredir *)tmp->content)->process_id = fork();
		if (((t_cmdredir *)tmp->content)->process_id < 0)
			return (perror("Minimichel: fork: "));
		if (((t_cmdredir *)tmp->content)->process_id == 0)
		{
			signal(SIGQUIT, handle_sig_child);
			signal(SIGINT, handle_sig_child);
			ft_proc_pipe(&tmp, x, cpenv);
		}
		if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
			close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
		if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
			close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
		tmp = tmp->next;
	}
}

void	ft_builtin_execution_pipe(t_data *x, t_list **cmdredir)
{
	t_list	*tmp;

	tmp = *cmdredir;
	if (x->fd_pipe[0] != STDIN_FILENO)
		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	if (x->fd_pipe[1] != STDOUT_FILENO)
		close(x->fd_pipe[1]);
}

void	ft_connectors(t_list **cmdredir, t_data *x, int nb, t_list **cpenv)
{
	t_list	*tmp;

	tmp = *cmdredir;
	if (nb == 6)
	{
		ft_connector_std_fdcmd(&tmp);
		ft_connector_redirections(&tmp, x);
	}
	else if (nb == 12)
	{
		if (ft_is_builtin(&tmp, x, cpenv) == 0)
		{
			x->bretzel++;
			ft_lstclear(cpenv, ft_free_words);
			ft_close_files(x);
		}
	}
}

void	ft_proc_pipe2(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;

	tmp = *cmdredir;
	g_status = 0;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	if (ft_is_exe(&cmd) == 0)
		ft_no_pipe_is_executable(&tmp, cpenv, x);
	if (x->bretzel == 0 && x->flag_exua != 2)
		ft_cmd_constructor(&cmd, x, cpenv);
	if (x->bretzel == 0 && x->pc != NULL)
	{
		g_status = 0;
		execve(x->pc, x->option, get_env(*cpenv));
	}
	if (x->flag_stop == 2)
		return (free(x->option), ft_lstclear(cpenv, ft_free_words),
			ft_exit_bis("1", x));
	if (x->bretzel > 0)
		ft_builtin_execution_pipe(x, &tmp);
	ft_exit_bis("0", x);
}

void	ft_proc_pipe(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*cmd;
	t_list	*redir;
	t_list	*tmp;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (((t_cmdredir *)tmp->next))
		close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
	if (cmd && cmd->content
		&& ft_is_is_builtin(((t_words *)cmd->content)->word) != 0)
		ft_connectors(&tmp, x, 6, cpenv);
	if (cmd->content)
		ft_connectors(&tmp, x, 12, cpenv);
	else
	{
		ft_perm_error(((t_words *)redir->next->content)->word, x, 2, cpenv);
		return (ft_lstclear(cpenv, ft_free_words));
	}
	ft_proc_pipe2(&tmp, x, cpenv);
}
