/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:55:45 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/15 22:48:00 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	write_env(char *before_eq, char *after_eq, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
	{
		ft_putstr_fd(before_eq, x->outfile);
		ft_putstr_fd("=", x->outfile);
		ft_putstr_fd(after_eq, x->outfile);
		ft_putstr_fd("\n", x->outfile);
	}
	else
	{
		ft_putstr_fd(before_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("=", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd(after_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	}
}

void	env_error(char	*str, t_list *cmdredir, t_data *x, int env)
{
	if (env == 0)
		g_status = 1;
	if (x->outfile > 2)
		ft_putstr_fd(str, x->outfile);
	else
		ft_putstr_fd(str, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
}

int	ft_env(t_list *cmdr, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*af;
	int		i_eq;

	if ((((t_cmdredir *)cmdr->content)->cmd)
		&& (((t_cmdredir *)cmdr->content)->cmd->next))
		return (env_error("env: too many arguments\n", cmdr, x, 0), 1);
	tmp = *cpenv;
	while (tmp)
	{
		content = (t_words *) tmp->content;
		if (content->token == TOK_ENV)
		{
			i_eq = check_if_equal(content->word);
			before_eq = ft_strndup(content->word, i_eq);
			af = ft_substr(content->word, i_eq + 1, ft_strlen(content->word));
			write_env(before_eq, af, cmdr, x);
			free(before_eq);
			free(af);
		}
		tmp = tmp->next;
	}
	return (0);
}
