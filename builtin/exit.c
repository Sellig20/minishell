/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:19:42 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/15 22:40:55 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_free_all(t_data *x)
{
	if (x->letters)
		ft_lstclear(&(x->letters), ft_free_letters);
	if (x->btw_pipes)
		ft_lstclear(&(x->btw_pipes), ft_free_btw_pipes);
	if (x->words)
		ft_lstclear(&(x->words), ft_free_words);
	if (x->segment)
		ft_lstclear(x->segment, ft_free_cmd_redir);
	if (x->line)
		free(x->line);
}

int	ft_is_mul_digit(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (-1);
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	get_exit(long long nb)
{
	if (nb >= 0)
		return (nb % 256);
	else
		return (256 - ((nb * (-1)) % 256));
}

int	ft_exit(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	long long	nb;
	t_list		*cmd;

	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	if (!(cmd->next))
		return (env_error("exit\n", cmdredir, x, 1),
			ft_lstclear(cpenv, ft_free_words),
			ft_free_all(x), exit(g_status), 5);
	cmd = cmd->next;
	nb = ft_atoll(((t_words *)cmd->content)->word);
	if (cmd->next)
	{
		g_status = 1;
		return (env_error("exit: too many arguments\n", cmdredir, x, 1), 2);
	}
	if (ft_is_mul_digit((((t_words *)cmd->content)->word)) == 1
		&& (nb > 922337203685477807 || nb < -922337203685477808))
		return (env_error("exit: too many arguments\n", cmdredir, x, 1),
			ft_free_all(x), ft_lstclear(cpenv, ft_free_words), exit(2), 5);
	else
		return (env_error("exit\n", cmdredir, x, 1), ft_free_all(x),
			ft_lstclear(cpenv, ft_free_words), exit(get_exit(nb)), 5);
}

void	ft_exit_bis(char *str, t_data *x)
{
	ft_free_all(x);
	g_status = ft_atoll(str);
	exit(g_status);
}
