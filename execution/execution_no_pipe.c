/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:56:57 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 02:19:27 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_exec_no_pipes(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_list	*cmd;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	ft_set_fdcmd(&tmp, x);
	if (x->flag_stop == 2)
	{
		g_status = 1;
		return ;
	}
	if (cmd->content)
	{
		if (ft_exec_no_pipe_bis(&tmp, x, cpenv) == EXIT_FAILURE)
			return ;
	}
	else
		ft_no_pipe_no_cmd_redir(&tmp, x);
}

void	ft_exec_no_pipe_annexe(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;
	t_list	*redir;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	((t_cmdredir *)tmp->content)->process_id = fork();
	if (((t_cmdredir *)tmp->content)->process_id < 0)
		return (perror("Minimichel: fork: "));
	if (((t_cmdredir *)tmp->content)->process_id == 0)
		call_no_pipe(cmd, redir, cpenv, x);
	else
	{
		waitpid(((t_cmdredir *)tmp->content)->process_id, &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
	}
}

void	ft_proc_no_pipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv)
{
	t_list	*tmp_cmd;
	t_list	*tmp_redir;

	tmp_cmd = *cmd;
	tmp_redir = *redir;
	while (tmp_redir)
	{
		ft_loop_redirections_prot(&tmp_redir, x);
		tmp_redir = tmp_redir->next;
	}
	if (x->flag_stop == 2)
		return ;
	if (x->flag_exua != 2 && x->flag_exua != 3 && x->flag_exua != 4)
		ft_cmd_constructor(&tmp_cmd, x, cpenv);
	if (x->pc != NULL)
		execve(x->pc, x->option, get_env(*cpenv));
	if (x->flag_exua != 2 && x->flag_exua != 3 && x->flag_exua != 4)
	{
		free(x->pc);
		free(x->option);
		ft_lstclear(cpenv, ft_free_words);
	}
}

void	ft_no_pipe_no_cmd_redir(t_list **cmdredir, t_data *x)
{
	t_list	*tmp;
	t_list	*tmp_redir;

	tmp = *cmdredir;
	tmp_redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	x->flag_no_pipe_no_cmd_ok_redir = 1;
	while (tmp_redir)
	{
		if (ft_is_redirection_in(&tmp_redir) == 1)
			ft_no_pipe_redirection_in(&tmp_redir, x);
		if (ft_is_redirection_out(&tmp_redir) == 1)
			ft_no_pipe_redirection_out(&tmp_redir, x);
		tmp_redir = tmp_redir->next;
	}
}

int	ft_no_pipe_is_executable(t_list **cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	t_list	*tmp;

	tmp = *cmdredir;
	x->flag_exua = 2;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	x->pc = ft_is_executable(&cmd, x, cpenv);
	x->option = NULL;
	if (x->pc == NULL && x->flag_exua != 4)
	{
		x->flag_exua = 3;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
