#include "../minishell.h"

static t_list **ft_dupwords(t_list **tmp)
{
    t_list	*new;
	t_list	**dup;
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
    t_btw_pipes	*new_pipe;

    if (portion_words == NULL)
        return (NULL);
    new_pipe = malloc(sizeof(t_btw_pipes));
    new_pipe->portion_words = portion_words;
    return (new_pipe);
}

void	sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes)
{
	t_list	*tmp;
	t_list	*new;
	t_list	**dup;

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
