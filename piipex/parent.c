/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannecolmou <jeannecolmou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:51:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/15 20:09:34 by jeannecolmo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parent_one(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;
	int		i;

	i = 0;
	pc = NULL;
	option = NULL;
	if (ft_parse(&argv[2]) == 0)
		return ;
	if (!env[i])
		ft_if(argv[2], &pc, &option);
	else
		ft_else(argv[2], &option, env, &pc);
	x->child1 = fork();
	if (x->child1 < 0)
		ft_error_child(option, pc);
	if (x->child1 == 0)
		ft_child_one(x, pc, option, env);
	else
		ft_annexe_parent_one(x);
	ft_free_array(option);
	ft_parent_two(x, argv, env);
}

void	ft_parent_two(t_data *x, char **argv, char **env)
{
	char	*pc;
	char	**option;
	int		i;

	pc = NULL;
	option = NULL;
	i = 0;
	if (ft_parse(&argv[3]) == 0)
		return ;
	if (!env[i])
		ft_if(argv[3], &pc, &option);
	else
		ft_else(argv[3], &option, env, &pc);
	x->child2 = fork();
	if (x->child2 < 0)
		ft_error_child(option, pc);
	if (x->child2 == 0)
		ft_child_two(x, pc, option, env);
	else
		ft_annexe_parent_two(x);
	ft_annexe_parent_two(x);
	ft_free_array(option);
}
