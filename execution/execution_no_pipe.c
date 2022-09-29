/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:56:57 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/28 15:50:12 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_nopipe(t_list **after_doll, t_list **cpenv, t_data *x)
{
	t_list *tmp;
	t_list *cmd;
	t_list *redir;
	pid_t processus;

	tmp = *after_doll;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;

	//dprintf(2, "ouioui\n");
	if (ft_is_builtin(&cmd, x, cpenv) == 0)
	{
		//ft_putstr_fd("\n", 1);
		return ;
	}
	processus = fork();
	if (processus < 0)
		return (perror("Minimichel: fork: "));
	if (processus == 0)
		ft_processus_nopipe(&cmd, &redir, x, cpenv);
	else
		waitpid(processus, NULL, 0);
	ft_free_array(x->option);
}

void	ft_processus_nopipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv)
{
	 t_list *tmp_cmd;
	 t_list *tmp_redir;

	tmp_cmd = *cmd;
	tmp_redir = *redir;

	ft_catch_file(&tmp_redir,  x);
	ft_cmd_constructor(&tmp_cmd, x, cpenv);
	if (x->pc != NULL)
		execve(x->pc, x->option, x->env);
	free(x->pc);
	free(x->option);
}