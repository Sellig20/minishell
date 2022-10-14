/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:56:57 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/14 18:41:45 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_bru(t_list **lst)
{
	int			count;
	t_list		*buffer;

	count = 0;
	buffer = *lst;
	while (buffer)
	{
		buffer = buffer->next;
		count++;
	}
	return (count);
}

void	ft_execution_organisation(t_list **after_doll, t_list **cpenv, t_data *x)
{
	t_list *tmp;
	int nb_cmd;

	tmp = *after_doll;
	nb_cmd = ft_lstsize_bru(&tmp);
	if (!(tmp->next))
	{
		// dprintf(2, "pas de pipe !\n");
		ft_execution_nopipe(&tmp, cpenv, x);
	}
	else
	{
		dprintf(2, "plusieurs pipe !\n");
		ft_execution_pipe(&tmp, cpenv, x, nb_cmd);
	}
}//echo poupou > B | wc < B > L | cat L

void	ft_execution_nopipe(t_list **after_doll, t_list **cpenv, t_data *x)
{
	t_list *tmp;
	t_list *cmd;
	t_list *redir;
	pid_t processus;
	tmp = *after_doll;
	cmd = (t_list *)((t_cmdredir *)tmp->content)->cmd;
	redir = (t_list *)((t_cmdredir *)tmp->content)->redirection;
	if (cmd->content)
	{
		if (ft_is_builtin(&tmp, x, cpenv) == 0)
		{
			// if (x->outfile != 1)
			// 	close(x->outfile);
			return ;
		}
		else
		{
			processus = fork();
			if (processus < 0)
				return (perror("Minimichel: fork: "));
			if (processus == 0)
				ft_processus_nopipe(&cmd, &redir, x, cpenv);
			else
				waitpid(processus, NULL, 0);
			ft_free_array(x->option);
		}
	}// ls > M | wc < M > E
	else
		ft_catch_file(&redir, x, cpenv);
}

void	ft_processus_nopipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv)
{
	t_list *tmp_cmd;
	t_list *tmp_redir;

	tmp_cmd = *cmd;
	tmp_redir = *redir;
	ft_cmd_constructor(&tmp_cmd, x, cpenv);
	ft_catch_file(&tmp_redir,  x, cpenv);
	if (x->pc != NULL)
	{
		execve(x->pc, x->option, x->env);
	}
	free(x->pc);
	free(x->option);
}
