/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:25:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/27 17:56:25 by jecolmou         ###   ########.fr       */
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
        printf("----------------------\n");
        tmp = tmp->next;
    }
}

t_list **ft_dupcmd(t_list *portion)
{
    t_list **dup;
    t_list *new;

    dup = malloc(sizeof(t_list*));
    if (!dup)
        return (NULL);
    *dup = NULL;
    if (!portion)
        return (NULL);
    while (portion)
    {
        if ((((((t_words *)portion->content)->token != TOK_DOLL)) && (((t_words *)portion->content)->token != TOK_WORD)) && (!(portion->next->next)))
            break; //C'est que y'as plus rien derriere a continuer d'organiser
        if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD && portion->next->next->next)
            portion = portion->next->next->next;
        if ( ((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL && ((t_words *)portion->next->next->content)->token == TOK_WORD)
            break;
        if ((((((t_words *)portion->content)->token != TOK_DOLL)) && ((t_words *)portion->content)->token != TOK_WORD) && portion->next->next)
            portion = portion->next->next;
        else
        {
            new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
            dup = (t_list **)ft_lstadd_back2(dup, new);
            portion = portion->next;
        }
    }
    if (!(*dup))
        (*dup) = ft_lstnew(NULL);
    return (dup);
}

t_list **ft_dupredir(t_list *portion)
{
    t_list **dup;
    t_list *new;
    char *doll = NULL;
    int     tok_doll;

    tok_doll = 0;
    dup = malloc(sizeof(t_list*));
    if (!dup)
        return (NULL);
    *dup = NULL;
    if (!portion)
        return (NULL);
    while (portion)
    {
        if (!(portion->next))
            break;
        if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->next->content)->token == TOK_DOLL)
        {
            doll = ((t_words *)portion->next->next->content)->word;
            tok_doll = ((t_words *)portion->next->next->content)->token;
        }
        if (((t_words *)portion->content)->token != TOK_WORD && ((t_words *)portion->content)->token != TOK_DOLL)
        {
            new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
            dup = (t_list **)ft_lstadd_back2(dup, new);
            portion = portion->next;
            new = ft_lstnew((void *) words_init(((t_words *)portion->content)->word, ((t_words *)portion->content)->token));
            dup = (t_list **)ft_lstadd_back2(dup, new);
            if (doll != NULL)
            {
                new = ft_lstnew((void *) words_init(doll, tok_doll));
                dup = (t_list **)ft_lstadd_back2(dup, new);
            }
        }
        portion = portion->next;
    }
    if (!(*dup))
        (*dup) = ft_lstnew(NULL);
    return (dup);
}

t_cmdredir *cmdredir_init(t_list *portion)
{
    t_cmdredir  *list;
    t_list  **remplir_cmd = NULL;
    t_list  **remplir_redir = NULL;

    if (!portion)
        return (NULL);
    list = malloc(sizeof(t_cmdredir));
    if (!list)
        return (NULL);
    remplir_cmd = ft_dupcmd(portion);
    remplir_redir = ft_dupredir(portion);
    list->cmd = (*remplir_cmd);
    list->redirection = (*remplir_redir);
    free(remplir_cmd);
    free(remplir_redir);
    return (list);
}

void ft_sep_cmd_redir(t_list **btw_pipes, t_list **future)
{
    t_list *btw;
    t_list *new;

    *future = NULL;
    btw = *btw_pipes;
    new = NULL;
    while (btw)
    {
        new = ft_lstnew((void *) cmdredir_init((t_list *)((t_btw_pipes *)btw->content)->portion_words));
        future = (t_list **)ft_lstadd_back2(future, new);
        btw = btw->next;
    }
    //ft_visualize_cmd_redir(future);
}

