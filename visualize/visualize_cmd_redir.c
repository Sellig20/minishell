/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize_cmd_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:54:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/13 13:46:55 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_visualize_cmd_redir(t_list **list)
{
    t_list *tmp;
    t_list *tentativecmd;
    t_list *tentativeredir;

    tmp = *list;
    while (tmp)
    {
        tentativecmd = (t_list *)((t_cmdredir*)tmp->content)->cmd;
        tentativeredir = (t_list *)((t_cmdredir*)tmp->content)->redirection;
        if (tentativecmd->content == NULL)
        {
            printf("CMD === ");
            printf("(null)\n\n");
        }
        else
        {
            printf("CMD === \n");
            visualize_t_words(&tentativecmd);
            printf("\n");
        }
        if (tentativeredir->content == NULL)
        {
            printf("REDIR === ");
            printf("(null)\n\n");
        }
        else
        {
            printf("REDIR === \n");
            visualize_t_words(&tentativeredir);
            printf("\n");
        }
        tmp = tmp->next;
    }
}
