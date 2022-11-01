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

/*t_words *ft_init_words_kezako(char *word)
{
	t_words *new_cp_env;

	new_cp_env = malloc(sizeof(t_words));
	if (!new_cp_env)
		return (NULL);
	new_cp_env->word = ft_strdup(word);
	return (new_cp_env);
}

t_words *ft_init_words(char *word, int token)
{
	t_words *new_cp_env;
	(void)token;
	(void)word;

	new_cp_env = malloc(sizeof(t_words));
	// if (!new_cp_env)
	// 	return (NULL);
	// new_cp_env->word = ft_strdup(word);
	return (new_cp_env);
}*/
int		get_size(t_list *cpenv)
{
	int	i;

	i = 1;
	while(cpenv)
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
	int	e;
	t_list *new;

	e = 0;
	new = NULL;
	*cpenv = NULL;
	(void)x;
	while (env[e])
	{
		new = ft_lstnew((void *) words_init(env[e], TOK_ENV));
		cpenv = (t_list **)ft_lstadd_back2(cpenv, new);
		e++;
	}
}
