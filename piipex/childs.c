/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:52:14 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/21 20:21:24 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_one(t_data *x, char *pc, char **option, char **env)
{
	close(x->f2);
	close(x->pipe_fd[IN]);
	if (x->f1 != STDIN_FILENO)
	{
		dup2(x->f1, STDIN_FILENO);
		close(x->f1);
	}
	if (x->pipe_fd[OUT] != STDOUT_FILENO)
	{
		dup2(x->pipe_fd[OUT], STDOUT_FILENO);
		close(x->pipe_fd[OUT]);
	}
	if (pc != NULL)
		execve(pc, option, env);
	else
		free(pc);
	free(pc);
	free(option);
	exit(127);
}

void	ft_child_two(t_data *x, char *pc, char **option, char **env)
{
	if (x->pipe_fd[IN] != STDIN_FILENO)
	{
		dup2(x->pipe_fd[IN], STDIN_FILENO);
		close(x->pipe_fd[IN]);
	}
	if (x->f2 != STDOUT_FILENO)
	{
		dup2(x->f2, STDOUT_FILENO);
		close(x->f2);
	}
	if (pc != NULL)
		execve(pc, option, env);
	else
		free(pc);
	free(pc);
	free(option);
	exit(127);
}
