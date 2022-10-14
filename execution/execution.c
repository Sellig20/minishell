
#include "../minishell.h"

void	ft_dup_stdin_pipe(t_data *x, t_list *tmp)
{
	((t_cmdredir *) tmp->content)->fd_cmd[0] = x->fd_pipe[0];
	close(x->fd_pipe[0]);
}

void	ft_dup_stdout_pipe(t_data *x, t_list *tmp)
{
	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
}

void	ft_processus_pipe_1(t_list *tmp, t_data *x, t_list **cpenv)
{
	t_list *cmd;
	t_list *redir;

	dprintf(2, "je rentre dans processus 1 ! \n");
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
	if (ft_is_builtin(&tmp, x, cpenv) == 0)
		return ;
	ft_catch_file_tekflemme(&redir,  x);
	// if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
	// 	close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	// }
	// if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
	// 	close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
	// }
	//ft_is_builtin(&tmp, x, cpenv);
	ft_cmd_constructor(&cmd, x, cpenv);
	if (x->pc != NULL)
	{
		//dprintf(2, "1) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
		execve(x->pc, x->option, x->env);
	}
	free(x->pc);
	free(x->option);
}

void	ft_processus_pipe_2(t_list *tmp, t_data *x, t_list **cpenv)
{
	t_list *cmd;
	t_list *redir;

	dprintf(2, "je rentre dans processus 2 ! \n");
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (ft_is_builtin(&tmp, x, cpenv) == 0)
		return ;
	ft_catch_file_tekflemme(&redir,  x);
	// if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
	// 	close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	// }
	// if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
	// 	close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
	// }
	ft_cmd_constructor(&cmd, x, cpenv);
	if (x->pc != NULL)
	{
		//dprintf(2, "2) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
		execve(x->pc, x->option, x->env);
	}
	free(x->pc);
	free(x->option);
}

void	ft_processus_pipe_3(t_list *tmp, t_data *x, t_list **cpenv)
{
	t_list *cmd;
	t_list *redir;

	dprintf(2, "je rentre dans processus 3 ! \n");
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (ft_is_builtin(&tmp, x, cpenv) == 0)
		return ;
	ft_catch_file_tekflemme(&redir,  x);
	// if (((t_cmdredir *)tmp->content)->fd_cmd[0] != STDIN_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[0], STDIN_FILENO);
	// 	close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
	// }
	// if (((t_cmdredir *)tmp->content)->fd_cmd[1] != STDOUT_FILENO)
	// {
	// 	dup2(((t_cmdredir *)tmp->content)->fd_cmd[1], STDOUT_FILENO);
	// 	close (((t_cmdredir *)tmp->content)->fd_cmd[1]);
	// }
	ft_cmd_constructor(&cmd, x, cpenv);
	if (x->pc != NULL)
	{
		//dprintf(2, "3) fd_cmd = (%i, %i)\n", ((t_cmdredir *)tmp->content)->fd_cmd[0], ((t_cmdredir *)tmp->content)->fd_cmd[1]);
		execve(x->pc, x->option, x->env);
	}
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
	(void)x;
	(void)cpenv;
	tmp = *after_doll;

	///////////////PIPE///////////////
	if (pipe(x->fd_pipe) == -1)
		return (perror("Minimichel: pipe: "));

	////////////////MAILLON 1/////////////////
	((t_cmdredir *) tmp->content)->fd_cmd[0] = STDIN_FILENO;
	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
	((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
	processus[i] = fork();//////////////////////////////////////////////////FORK 1
	if (processus[i] < 0)
		return (perror("Minimichel: fork: "));
	if (processus[i] == 0)
		ft_processus_pipe_1(tmp, x, cpenv);///////////////////////////////APPEL PROCESSUS 1
	close(((t_cmdredir *)tmp->content)->fd_cmd[1]);

	ft_free_array(x->option);
	tmp = tmp->next;
	i++;

















	// dprintf(2, "ouiouioui\n");
	while (tmp && tmp->next)
	{
		if (pipe(x->fd_pipe) == -1)
			return (perror("Minimichel: pipe: "));
		((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
		((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];


		///////////////MAILLON 2///////////////////////
		processus[i] = fork();/////////////////////////////////////////////////FORK 2
		if (processus[i] < 0)
			return (perror("Minimichel: fork: "));
		if (processus[i] == 0)
		{
			ft_processus_pipe_2(tmp, x, cpenv);///////////////////////////////////APPEL PROCESSUS 2
		}
		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
		close(((t_cmdredir *)tmp->content)->fd_cmd[1]);
		ft_free_array(x->option);
		tmp = tmp->next;

		i++;
	}
	((t_cmdredir *)tmp->content)->fd_cmd[1] = STDOUT_FILENO;

















	/////////////////MAILLON 3////////////////////////////
	processus[i] = fork();///////////////////////////////////////////////////////FORK 3
	if (processus[i] < 0)
		return (perror("Minimichel: fork: "));
	//dprintf(2, "ouiiiiii mon 3 eme maillon\n");
	if (processus[i] == 0)
	{
		ft_processus_pipe_3(tmp, x, cpenv);//////////////////////////////////////////APPEL PROCESSUS 3
	}
	else
	{
		close(((t_cmdredir *)tmp->content)->fd_cmd[0]);
		i = 0;
		while (i < nb_cmd)
		{
			waitpid(processus[i], NULL, 0);
			i++;
		}
		ft_free_array(x->option);
	}
}
