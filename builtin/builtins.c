/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/28 15:31:28 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins(char *cmd, char *cmdnext)
{
	dprintf(2,"BUILTIN : ");
	dprintf(2, "%s\n", cmd);
	dprintf(2, "%s\n", cmdnext);
}

int	ft_is_builtin(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list *tmp_cmd;
	(void)cpenv;

	tmp_cmd = *cmd;
	(void)x;
	(void)cpenv;
	while (tmp_cmd)
	{
		while((g_lookup[x->i_gl].builtin_name))
		{
			if (ft_strcmp(((t_words *)tmp_cmd->content)->word, g_lookup[x->i_gl].builtin_name) == 0)
			{
				g_lookup[x->i_gl].fonction(tmp_cmd, cpenv);
				//dprintf(2, "coucou la mif\n");
				return (EXIT_SUCCESS);
			}
			x->i_gl++;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (EXIT_FAILURE);
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
