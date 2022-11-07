/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:19:42 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/01 14:59:13 by jecolmou         ###   ########.fr       */
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
		ft_lstclear(&(x->segment), ft_free_cmd_redir);
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

	(void) x;
	(void) cpenv;
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	write(2, "exit\n", 5);
	if (!(cmd->next))
		return (ft_free_all(x), exit(0), 5);
	cmd = cmd->next;
	nb = ft_atoll(((t_words *)cmd->content)->word);
	if (ft_is_mul_digit((((t_words *)cmd->content)->word)) == 1
		&& (nb > 922337203685477807 || nb < -922337203685477808))
		return (printf("exit: numeric argument required\n"),
			ft_free_all(x), exit(2), 5);
	else
		return (ft_free_all(x), exit(get_exit(nb)), 5);
	if (cmd->next)
	{
		g_status = 2;
		return (printf("exit: too many arguments\n"), 2);
	}
	return (0);
}

void	ft_exit_bis(char *str, t_data *x)
{
	ft_free_all(x);
	g_status = ft_atoll(str);
	exit(g_status);
}
