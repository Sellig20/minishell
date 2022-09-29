/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents_annexe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:45:13 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/21 20:21:33 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_annexe_parent_one(t_data *x)
{
	close(x->pipe_fd[1]);
	close(x->f1);
}

void	ft_annexe_parent_two(t_data *x)
{
	close(x->pipe_fd[0]);
	close(x->f2);
	waitpid(x->child1, NULL, 0);
	waitpid(x->child2, NULL, 0);
}

void	ft_error_child(char **option, char *pc)
{
	ft_free_array(option);
	free(pc);
	return (perror("fork: "));
}

void	ft_if(char	*argv, char **pc, char ***option)
{
	*option = ft_split(argv, ' ');
	if (access(*(option[0]), X_OK) == 0)
		*pc = *(option[0]);
	else
	{
		ft_argv_error(*(option[0]));
		return ;
	}
}

void	ft_else(char *argv, char ***opt, char **env, char **pc)
{
	*opt = ft_split(argv, ' ');
	if (access(*(opt[0]), X_OK) == 0)
		*pc = *(opt[0]);
	else
	{
		*pc = ft_path_command(argv, env);
		ft_free_array(*opt);
		*opt = ft_get_command(argv, *pc);
	}
}
