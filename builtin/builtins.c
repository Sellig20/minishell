/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:23:01 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/11 15:12:42 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins(char *cmd, char *cmdnext)
{
	dprintf(2,"BUILTIN : ");
	dprintf(2, "%s\n", cmd);
	dprintf(2, "%s\n", cmdnext);
}

int	ft_is_builtin(t_list **after_doll, t_data *x, t_list **cpenv)
{
	t_list *tmp_cmd;
	t_list *tmp_redir;
	int	i;

	(void)x;
	t_list *after;
	after = *after_doll;
	tmp_cmd = (t_list *)((t_cmdredir *)after->content)->cmd;
	tmp_redir = (t_list *)((t_cmdredir *)after->content)->redirection;
	i = 0;
	ft_catch_file(&tmp_redir, x, cpenv);
	while((g_lookup[i].builtin_name != 0))
	{
		if (ft_strcmp(((t_words *)tmp_cmd->content)->word, g_lookup[i].builtin_name) == 0)
		{
			g_lookup[i].fonction(tmp_cmd, cpenv);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
