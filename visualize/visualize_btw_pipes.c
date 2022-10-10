/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize_btw_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:57:36 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/30 19:58:03 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_visualize_btw_pipes(t_list **lst)
{
    t_list *tmp; // t_btw_pipes
    t_list *portion_words; //t_words

    tmp = *lst;
    portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
    while (tmp->next)
    {
	portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
        printf("->\n");
        visualize_t_words(&portion_words);
        tmp = tmp->next;
    }
    portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
    printf("->\n");
    visualize_t_words(&portion_words);
}
