/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/07 16:55:16 by jecolmou         ###   ########.fr       */
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
	int	i = 0;
	(void)x;
	tmp_cmd = *cmd;
	while (tmp_cmd)
	{
		while((g_lookup[i].builtin_name != 0))
		{
			if (ft_strcmp(((t_words *)tmp_cmd->content)->word, g_lookup[i].builtin_name) == 0)
			{
				g_lookup[i].fonction(tmp_cmd, cpenv);
				return (EXIT_SUCCESS);
			}
			i++;
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
