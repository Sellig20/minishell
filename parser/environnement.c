/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:23 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/30 12:44:27 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cpenv *ft_init_cpenv_kezako(char *one_env)
{
	t_cpenv *new_cp_env;

	new_cp_env = malloc(sizeof(t_cpenv));
	if (!new_cp_env)
		return (NULL);
	new_cp_env->one_env = ft_strdup(one_env);
	return (new_cp_env);
}

t_words *ft_init_cpenv(char *one_env, int token)
{
	t_words *new_cp_env;
	(void)token;
	(void)one_env;

	new_cp_env = malloc(sizeof(t_words));
	// if (!new_cp_env)
	// 	return (NULL);
	// new_cp_env->one_env = ft_strdup(one_env);
	return (new_cp_env);
}

void	ft_dup_env(char **env, t_list **cpenv, t_data *x)
{
	int	e;
	t_list *new;

	e = 0;
	new = NULL;
	*cpenv = NULL;
	(void)x;
	while (env[e])
	{
		new = ft_lstnew((void *) ft_init_cpenv_kezako(env[e]));
		cpenv = (t_list **)ft_lstadd_back2(cpenv, new);
		e++;
	}
}
