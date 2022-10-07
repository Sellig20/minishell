#include "../minishell.h"

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

static t_list **ft_dupwords(t_list **tmp)
{
    t_list  *new;
	t_list **dup;
    int i;

    i = 0;
	dup = malloc(sizeof(t_list *));
	*dup = NULL;
	if (!tmp || !(*tmp))
		return (NULL);
	if (((t_words *) (*tmp)->content)->token == TOK_PIPE)
		(*tmp) = (*tmp)->next;
	while (*tmp && ((*tmp)->next) && ((t_words *)((*tmp)->next)->content)->token != TOK_PIPE)
	{
		new = ft_lstnew((void *) words_init(((t_words *) (*tmp)->content)->word, ((t_words *)(*tmp)->content)->token));
		dup = (t_list **)ft_lstadd_back2(dup, new);
		*tmp = (*tmp)->next;
		i++;
    }
	new = ft_lstnew((void *) words_init(((t_words *) (*tmp)->content)->word, ((t_words *)(*tmp)->content)->token));
	dup = (t_list **)ft_lstadd_back2(dup, new);
	*tmp = (*tmp)->next;
	return (dup);
}

static t_btw_pipes *btw_pipes_init(t_list *portion_words)
{
    t_btw_pipes *new_pipe; //t_btw_pipes

    if (portion_words == NULL)
        return (NULL);
    new_pipe = malloc(sizeof(t_btw_pipes));
    new_pipe->portion_words = portion_words;
    return (new_pipe);
}

void	sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes)
{
	t_list *tmp; //t_list de type t_words
	t_list *new; //t_list de type t_btw_pipes;
	t_list **dup; //t_list de type t_words;

	*lst_btw_pipes = NULL;
	new = NULL;
	tmp = NULL;
	tmp = *lst_words;
	while (tmp)
	{
		dup = ft_dupwords(&tmp);
		new = ft_lstnew((void *) btw_pipes_init(*dup));
		free(dup);
		lst_btw_pipes =(t_list **) ft_lstadd_back2(lst_btw_pipes, new);
	}
}



