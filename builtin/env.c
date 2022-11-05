
#include "../minishell.h"

int	ft_env(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*after_eq;
	int		index_eq;

	(void) x;
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
			ft_putstr_fd(before_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
			ft_putstr_fd("=", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
			ft_putstr_fd(after_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
			ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
			free(before_eq);
			free(after_eq);
		}
		tmp = tmp->next;
	}
	return (0);
}
