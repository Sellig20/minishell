/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:16:05 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/02 19:19:36 by jecolmou         ###   ########.fr       */
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
		if (x->flag_stop == 2)
			return ;
		if (((t_cmdredir *)tmp->next))
			ft_create_pipe(&tmp, x);
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

void	ft_create_pipe(t_list **cmdredir, t_data *x)
{
	t_list *tmp;

	tmp = *cmdredir;
	if (pipe(x->fd_pipe) == -1)
		return (perror("Minimichel: pipe: "));
	((t_cmdredir *)tmp->next->content)->fd_cmd[0] = x->fd_pipe[0];
	((t_cmdredir *)tmp->content)->fd_cmd[1] = x->fd_pipe[1];
}

void	ft_processus_pipe(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*cmd;
	t_list	*tmp;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	if (((t_cmdredir *)tmp->next))
		close(((t_cmdredir *)tmp->next->content)->fd_cmd[0]);
	ft_connector_redirections(&tmp, x);
	if (cmd->content)
	{
		if (ft_is_builtin(&tmp, x, cpenv) == 0)
			ft_exit_bis("1", x);
	}
	else
		ft_exit_bis("1", x);
	//dprintf(2, "flag stop = %d | %s\n", x->flag_stop, x->pc);
	// if (x->flag_stop == 2)
	// 	ft_exit_bis("1", x);
	ft_connector_std_fdcmd(&tmp);
	if (ft_is_exe(&cmd, x, cpenv) == 0)
		ft_no_pipe_is_executable(&tmp, cpenv, x);
	if (x->flag_executable != 2)
		ft_cmd_constructor(&cmd, x, cpenv);
	if (x->pc != NULL)
		execve(x->pc, x->option, get_env(*cpenv));
	free(x->pc);
	free(x->option);
}
