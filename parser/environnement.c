/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:23 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 12:29:17 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size(t_list *cpenv)
{
	int	i;

	i = 1;
	while (cpenv)
	{
		i++;
		cpenv = cpenv->next;
	}
	return (i);
}

char	**get_env(t_list *cpenv)
{
	char	**env;
	int		len;
	int		i;

	len = get_size(cpenv);
	env = calloc(sizeof(char *), (len));
	i = 0;
	while (cpenv)
	{
		env[i] = ft_strdup(((t_words *)cpenv->content)->word);
		i++;
		cpenv = cpenv->next;
	}
	return (env);
}

void	ft_dup_env(char **env, t_list **cpenv, t_data *x)
{
	t_list	*new;
	int		e;

	e = 0;
	new = NULL;
	*cpenv = NULL;
	(void)x;
	while (env[e])
	{
		new = ft_lstnew((void *) words_init(env[e], TOK_ENV));
		ft_lstadd_back(cpenv, new);
		e++;
	}
}
