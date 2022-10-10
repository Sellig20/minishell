/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:56:05 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/30 19:59:46 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list *ft_dupwords(t_list **lst_words)
{
	t_list  *tmp; //list words
	t_list	**dup; //list words
	t_list	*new; //
	int i;

	i = 0;

	tmp = *lst_words;
	dup = malloc(sizeof(t_list *));
	*dup = NULL;
	while (tmp)
	{
		new = ft_lstnew((void *) words_init(((t_words *)tmp->content)->word, ((t_words *)tmp->content)->token));
		dup = (t_list **)ft_lstadd_back2(dup, new);
		tmp = tmp->next;
		i++;
		printf("\n\nvisualize depuis dupwords %i\n" , i);
		visualize_t_words(dup);
	}
//	visualize_t_words(dup);
	return (*dup);
}

// static t_btw_pipes *btw_pipes_init(t_list *portion_words)
// {
// 	t_list	*tmp; //t_words
// 	t_list	*dup; //t_words;
// 	t_btw_pipes	*new_pipe; //t_btw_pipes

// 	if (portion_words == NULL)
// 		return (NULL);
// 	tmp = portion_words;
// 	new_pipe = malloc(sizeof(t_btw_pipes));
// 	dup = malloc(sizeof(t_list));
// 	dup = ft_dupwords(&tmp);
// 	new_pipe->portion_words = dup;
// 	return (new_pipe);
// }

// void    ft_visualize_btw_pipes(t_list **lst)
// {
//     t_list *tmp; // t_btw_pipes
//     t_list *portion_words; //t_words

//     tmp = *lst;
//     portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
//     while (tmp->next)
//     {
// 	portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
//         printf("->\n");
//         visualize_t_words(&portion_words);
//         tmp = tmp->next;
//     }
//     portion_words = (t_list *)((t_btw_pipes *)tmp->content)->portion_words;
//     printf("->\n");
//     visualize_t_words(&portion_words);
// }
/*
void    ft_visualize_simple_cmd(t_simple_cmd **simple_cmd)
{
    t_simple_cmd *tmp_simple_cmd;

    tmp_simple_cmd = *simple_cmd;

    while (tmp_simple_cmd->next)
    {
		printf("CMD FINALE->\n");
		visualize_t_words(&tmp_simple_cmd->cmd);
		printf("REDIRECTION FINALE->\n");
		visualize_t_words(&tmp_simple_cmd->redirection);
		tmp_simple_cmd = tmp_simple_cmd->next;
    }
	printf("CMD FINALE->\n");
	visualize_t_words(&tmp_simple_cmd->cmd);
	printf("REDIRECTION FINALE->\n");
	visualize_t_words(&tmp_simple_cmd->redirection);
}*/
// ATTENTION ICI ON PARCOUR LE VRAI LST_WORD ------> Impossible a free derriere.
// t_list    *ft_sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes)
// {
//     t_list	*tmp;// list->words
//     t_list	*follow; // list_words
//     t_list	*new; //  list->btw_pipes
//  //   t_words	*follow;
// 	t_list	*cp_tmp; //list->words
// 	int		i;
//    // t_btw_pipes *tmp_btw_pipes;

// 	*lst_btw_pipes = NULL;
//     tmp = *lst_words;
//     new = NULL;
//     //lst_btw_pipes = NULL;
//     i = 0;
//     while (tmp && tmp->next && ((t_words *)(tmp->next)->content)->token != TOK_PIPE)
//     {
//         i++;
//         tmp = tmp->next;
//     }
//     if (tmp->next)
// //        follow = (t_words *)(tmp->next->next)->content;
// 	follow = tmp->next->next;
//     else
//         follow = NULL;
//     tmp->next = NULL;
//     cp_tmp = *lst_words;
//     new = ft_lstnew((void *) btw_pipes_init(cp_tmp/*, size*/));
//     lst_btw_pipes = (t_list **) ft_lstadd_back2(lst_btw_pipes, new);
//     return (follow);
// }
