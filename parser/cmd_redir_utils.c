/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:38:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/04 01:32:56 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmdredir	*cmdredir_init(t_list *portion)
{
	t_cmdredir	*list;
	t_list		**remplir_cmd;
	t_list		**remplir_redir;

	remplir_cmd = NULL;
	remplir_redir = NULL;
	if (!portion)
		return (NULL);
	list = malloc(sizeof(t_cmdredir));
	if (!list)
		return (NULL);
	remplir_cmd = ft_dupcmd(portion);
	remplir_redir = ft_dupredir(portion);
	list->cmd = (*remplir_cmd);
	list->redirection = (*remplir_redir);
	list->process_id = -2;
	free(remplir_cmd);
	free(remplir_redir);
	return (list);
}
