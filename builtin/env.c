
#include "../minishell.h"

int	ft_env(t_list *cmd, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*after_eq;
	int		index_eq;

	(void) x;
	(void) cmd;
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
			dprintf(((t_cmdredir *)cmd->content)->fd_cmd[1], "%s=%s\n", before_eq, after_eq);
			free(before_eq);
			free(after_eq);
		}
		tmp = tmp->next;
	}
	return (0);
}
