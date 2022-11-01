/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:56:57 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/01 19:38:11 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_execution_no_pipe_annexe(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;
	t_list	*redir;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	((t_cmdredir *)tmp->content)->process_id = fork();
	if (((t_cmdredir *)tmp->content)->process_id < 0)
		return (perror("Minimichel: fork: "));
	signal(SIGQUIT, handle_sig_child);
	signal(SIGINT, handle_sig_child);
	if (((t_cmdredir *)tmp->content)->process_id == 0)
		ft_processus_no_pipe(&cmd, &redir, x, cpenv);
	else
	{
		waitpid(((t_cmdredir *)tmp->content)->process_id, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
	}
}

void	ft_no_pipe_no_cmd_redir(t_list **redir, t_data *x)
{
	t_list	*tmp_redir;

	tmp_redir = *redir;
	x->flag_redir = 1;
	x->flag_no_pipe_no_cmd_ok_redir = 1;
	if (ft_is_redirection_in(&tmp_redir) == 1)
		ft_no_pipe_redirection_in(&tmp_redir, x);
	if (ft_is_redirection_out(&tmp_redir) == 1)
		ft_no_pipe_redirection_out(&tmp_redir, x);
}

void	ft_no_pipe_is_executable(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	t_list	*tmp;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	x->pc = ft_is_executable(&cmd, x, cpenv);
	if (x->pc == NULL)
		ft_error_nsfod(((t_words *)cmd->content)->word);
	x->flag_executable = 2;
}

void	ft_execution_no_pipe(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_list	*cmd;
	t_list	*redir;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	ft_set_fdcmd(&tmp, x);
	if (x->flag_stop == 2)
		return ;
	if (cmd->content)
	{
		if (ft_is_builtin(&tmp, x, cpenv) == 0)
			return ;
		else if (ft_is_exe(&cmd, x, cpenv) == 0)
			ft_no_pipe_is_executable(&tmp, cpenv, x);
		ft_execution_no_pipe_annexe(&tmp, x, cpenv);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sig_parent);
		if (x->flag_executable == 2)
			free(x->pc);
	}
	else
		ft_no_pipe_no_cmd_redir(&redir, x);
}

void	ft_processus_no_pipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv)
{
	t_list	*tmp_cmd;
	t_list	*tmp_redir;

	tmp_cmd = *cmd;
	tmp_redir = *redir;
	while (tmp_redir)
	{
		if (ft_is_redirection_in(&tmp_redir) == 1)
			ft_no_pipe_redirection_in(&tmp_redir, x);
		if (ft_is_redirection_out(&tmp_redir) == 1)
			ft_no_pipe_redirection_out(&tmp_redir, x);
		tmp_redir = tmp_redir->next;
	}
	if (x->flag_stop == 2)
		return ;
	if (x->flag_executable != 2)
		ft_cmd_constructor(&tmp_cmd, x, cpenv);
	if (x->pc != NULL)
		execve(x->pc, x->option, get_env(*cpenv));
	free(x->pc);
	free(x->option);
}
