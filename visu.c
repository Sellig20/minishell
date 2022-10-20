#include "minishell.h"

void	visualize_t_words(t_list **lst_words)
{
	t_list	*tmp;
	int		i;

	tmp = *lst_words;
	i = 0;
	while (tmp->next)
	{
		if (!((t_words *)tmp->content))
			printf("3.(null)\n");
		else
			printf("1.maillon num %i : word = %s, token = %i\n",
				i, ((t_words *)tmp->content)->word,
				((t_words *) tmp->content)->token);
		tmp = tmp->next;
		i++;
	}
	printf("2.maillon num %i : word = %s, token = %i\n",
		i, ((t_words *) tmp->content)->word,
		((t_words *) tmp->content)->token);
}

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
