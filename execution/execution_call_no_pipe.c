/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call_no_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:45:51 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 16:36:58 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	call_no_pipe(t_list *cmd, t_list *redir, t_list **cpenv, t_data *x)
{
	signal(SIGQUIT, handle_sig_child);
	signal(SIGINT, handle_sig_child);
	ft_proc_no_pipe(&cmd, &redir, x, cpenv);
}

int	ft_exec_no_pipe_bis(t_list **cmdredir, t_data *x, t_list **cpenv)
{
	t_list	*tmp;
	t_list	*cmd;

	tmp = *cmdredir;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	if (ft_is_builtin(&tmp, x, cpenv) == 0)
	{
		g_status = 1;
		return (ft_close_files(x), EXIT_FAILURE);
	}
	else if (ft_is_exe(&cmd) == 17)
		return (EXIT_FAILURE);
	else if (ft_is_exe(&cmd) == 0
		&& ft_no_pipe_is_executable(&tmp, cpenv, x) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ft_is_exe(&cmd) == 2)
		return (ft_error_command_not_f(((t_words *)cmd->content)->word),
			EXIT_FAILURE);
	ft_exec_no_pipe_annexe(&tmp, x, cpenv);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_parent);
	if (x->flag_exua == 2)
		free(x->pc);
	return (EXIT_SUCCESS);
}
