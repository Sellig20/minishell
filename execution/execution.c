
#include "../minishell.h"

extern int g_status;

int	ft_is_redirection_in(t_list **list)
{
	t_list *redir;

	redir = *list;
	if (((t_words *)redir->content) == NULL)
		return 0;
	if (ft_strcmp(((t_words *)redir->content)->word, "<") == 0 || ft_strcmp(((t_words *)redir->content)->word, "<<") == 0)
		return (1);
	return (0);
}

int	ft_is_redirection_out(t_list **list)
{
	t_list *redir;

	redir = *list;
	if (((t_words *)redir->content) == NULL)
		return 0;
	if (ft_strcmp(((t_words *)redir->content)->word, ">") == 0 || ft_strcmp(((t_words *)redir->content)->word, ">>") == 0)
		return (1);
	return (0);
}

void	ft_processus_pipe(t_list **tmpafterd, t_data *x, t_list **cpenv)
{
	t_list *cmd;
	t_list *redir;
	t_list *tmp;

	tmp = *tmpafterd;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (((t_cmdredir *)tmp->next))
		close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
	while (redir)
	{
		if (ft_is_redirection_in(&redir) == 1)
			ft_pipe_redirection_in(&tmp, redir, x, cpenv);
		if (ft_is_redirection_out(&redir) == 1)
			ft_pipe_redirection_out(&tmp, redir, x);
		redir = redir->next;
	}
	if (cmd->content)
	{
		if (ft_is_builtin(&tmp, x, cpenv) == 0)
			ft_exit_bis("1", x);
	}
	else
		ft_exit_bis("1", x);
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
	ft_cmd_constructor(&cmd, x, cpenv);
	if (x->pc != NULL)
		execve(x->pc, x->option, get_env(*cpenv));
	free(x->pc);
	free(x->option);
}

void	ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x, int nb_cmd)
{
	t_list *tmp;
	tmp = *after_doll;
	(void)nb_cmd;

	ft_set_fdcmd(&tmp, x);
	while (tmp)
	{
		if (x->flag_stop == 2)
			return ;
		if (((t_cmdredir *)tmp->next))
		{
			if (pipe(x->fd_pipe) == -1)
				return (perror("Minimichel: pipe: "));
			((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
			((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
		}
		((t_cmdredir *)tmp->content)->process_id = fork();
		if (((t_cmdredir *)tmp->content)->process_id < 0)
			return (perror("Minimichel: fork: "));
		signal(SIGQUIT, handle_sig_child);
		signal(SIGINT, handle_sig_child);
		if (((t_cmdredir *)tmp->content)->process_id == 0)
			ft_processus_pipe(&tmp, x, cpenv);
		if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
			close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
		if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
			close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
		ft_free_array(x->option);
		tmp = tmp->next;
	}
}

int	ft_waitpid(t_list **after_doll, t_data *x)
{
	t_list *tmp;
	tmp = *after_doll;
	(void)x;
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

