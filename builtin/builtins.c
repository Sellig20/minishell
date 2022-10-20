/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/18 18:20:03 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_fonction(t_list *cmd, t_list **cpenv, t_data *x)
{
	(void)cmd;
	(void)cpenv;
	(void)x;
	return(1);
}

int	ft_is_is_builtin(char *word, int i)
{
	while((g_lookup[i].builtin_name != 0))
	{
		if (ft_strcmp(word, g_lookup[i].builtin_name) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_is_builtin(t_list **after_doll, t_data *x, t_list **cpenv)
{
	t_list	*tmp_cmd;
	t_list	*after;
	int		i;

	x->flag = 0;
	(void)x;
	after = *after_doll;
	tmp_cmd = (t_list *)((t_cmdredir *)after->content)->cmd;
	i = 0;
	if (ft_is_is_builtin(((t_words *)tmp_cmd->content)->word, i) == 0)
	{
		x->flag = 1;
		ft_catch_file((&((t_cmdredir *)after->content)->redirection), x, cpenv);
		while((g_lookup[i].builtin_name != 0))
		{
			if (ft_strcmp(((t_words *)tmp_cmd->content)->word, g_lookup[i].builtin_name) == 0)
			{
				g_lookup[i].fonction(tmp_cmd, cpenv, x);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


/*
void	ft_env(t_list **cpenv)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*after_eq;
	int		index_eq;

	tmp = *cpenv;
	while (tmp)
	{
		content = (t_words *) tmp->content;
		if (content->token == TOK_ENV)
		{
			index_eq = check_if_equal(content->word);
			before_eq = ft_strndup(content->word, index_eq);
			after_eq = ft_substr(content->word,
					index_eq + 1, ft_strlen(content->word));
			printf("%s=%s\n", before_eq, after_eq);
			free(before_eq);
			free(after_eq);
		}
		tmp = tmp->next;
}*/
