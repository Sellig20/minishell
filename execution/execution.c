
#include "../minishell.h"

extern int g_status;



























void	ft_dup_stdin_pipe(t_data *x, t_list *tmp)
{
	((t_cmdredir *) tmp->content)->fd_cmd[0] = x->fd_pipe[0];
	close(x->fd_pipe[0]);
}

void	ft_dup_stdout_pipe(t_data *x, t_list *tmp)
{
	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
}

// void	ft_processus_pipe_1(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	dprintf(2, "je rentre dans processus 1 ! \n");
// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
// 	if (ft_is_builtin(&tmp, x, cpenv) == 0)
// 		return ;
// 	ft_catch_file_tekflemme(&tmp,  x);
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "1) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }

// void	ft_processus_pipe_3(t_list *tmp, t_data *x, t_list **cpenv)
// {
// 	t_list *cmd;
// 	t_list *redir;

// 	//dprintf(2, "je rentre dans processus 3 ! \n");
// 	ft_catch_file_tekflemme(&tmp,  x);
// 	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
// 	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
// 	if (ft_is_builtin(&tmp, x, cpenv) == 0)
// 		return ;
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
// 		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
// 	}
// 	if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
// 	{
// 		dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
// 		close (((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 	}
// 	ft_cmd_constructor(&cmd, x, cpenv);
// 	if (x->pc != NULL)
// 	{
// 		//dprintf(2, "3) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
// 		execve(x->pc, x->option, x->env);
// 	}
// 	free(x->pc);
// 	free(x->option);
// }

int	ft_if_is_redirection(t_list **list)
{
	t_list *redir;

	redir = *list;
	if (((t_words *)redir->content) == NULL)
		return 0;
	if (ft_strcmp(((t_words *)redir->content)->word, "<") == 0 || ft_strcmp(((t_words *)redir->content)->word, "<<") == 0)
		return (1);
	return (0);
}


int	ft_if_is_redirection_2(t_list **list)
{
	t_list *redir;

	redir = *list;
	if (((t_words *)redir->content) == NULL)
		return 0;
	if (ft_strcmp(((t_words *)redir->content)->word, ">") == 0 || ft_strcmp(((t_words *)redir->content)->word, ">>") == 0)
		return (1);
	return (0);
}

void	ft_processus_pipe_2(t_list **tmpafterd, t_data *x, t_list **cpenv)
{
	t_list *cmd;
	t_list *redir;
	t_list *tmp;

	tmp = *tmpafterd;
	(void)cpenv;
	(void)x;
	(void)redir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (((t_cmdredir *)tmp->next))
		close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
	if (ft_is_builtin(&tmp, x, cpenv) == 0)
		return ;
	while (redir)
	{
		if (ft_if_is_redirection(&redir) == 1)
			ft_catch_file_tekinfile(&tmp, redir, x);
		if (ft_if_is_redirection_2(&redir) == 1)
			ft_catch_file_tekoutfile(&tmp, redir, x);
		redir = redir->next;
	}
	dprintf(2, "cmd = %s, fd cmd 0 = %d | fd cmd 1 = %d\n", ((t_words *)cmd->content)->word, ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
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
		execve(x->pc, x->option, x->env);
	free(x->pc);
	free(x->option);
}


void	ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x, int nb_cmd)
{
	t_list *tmp;
	pid_t *processus;

	int	i;
	processus = malloc(sizeof(pid_t) * nb_cmd);
	i = 0;
	tmp = *after_doll;
	int j = 0;
	(void)cpenv;
	int flag = 0;
	while (j < nb_cmd)
	{
		((t_cmdredir *) tmp->content)->fd_cmd[0] = STDIN_FILENO;
		((t_cmdredir *)tmp->content)->fd_cmd[1] = STDOUT_FILENO;
		j++;
	}
	//ls > A | < PO wc -l > B | < B cat > C | ls -lma > D | < D wc -l > E
	while (tmp)
	{
		if (((t_cmdredir *)tmp->next))
		{
			if (pipe(x->fd_pipe) == -1)
				return (perror("Minimichel: pipe: "));
			((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
			((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
			//close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
		}
		else
		{
			flag = 2;
		}
		processus[i] = fork();
		if (processus[i] < 0)
			return (perror("Minimichel: fork: "));
		signal(SIGQUIT, handle_sig_child);
		signal(SIGINT, handle_sig_child);
		if (processus[i] == 0)
		{
			ft_processus_pipe_2(&tmp, x, cpenv);
			if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
				close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
			if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
				close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
			close(x->fd_pipe[0]);
			close(x->fd_pipe[1]);
		}
		ft_free_array(x->option);
		if (flag == 2)
		{
			close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
			while (i < nb_cmd)
			{
				waitpid(processus[i], &g_status, 0);
				if (WIFEXITED(g_status))
					g_status = WEXITSTATUS(g_status);
				if (WIFSIGNALED(g_status))
					g_status = WTERMSIG(g_status) + 128;
				i++;
			}
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, handle_sig_parent);
			ft_free_array(x->option);
		}
		i++;
		tmp = tmp->next;
	}

}








































// void	ft_dup_stdin_pipe(t_data *x, t_list *tmp)
// {
// 	((t_cmdredir *) tmp->content)->fd_cmd[0] = x->fd_pipe[0];
// 	close(x->fd_pipe[0]);
// }

// void	ft_dup_stdout_pipe(t_data *x, t_list *tmp)
// {
// 	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
// }


