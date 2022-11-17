/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:27:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/14 23:11:55 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		write(2, "\n", 1);
		g_status = 130;
		return ;
	}
}

void	handle_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		sig = SIGCONT;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sig_child(int sig)
{
	if (sig == SIGINT && g_status == 42)
	{
		sig = SIGQUIT;
		g_status = 2;
		write(2, "\n", 1);
	}
	else if (sig == SIGINT && g_status != 42)
	{
		sig = SIGQUIT;
		g_status = 2;
	}
	else if (sig == SIGQUIT && g_status == 42)
		g_status = 3;
	else if (sig == SIGQUIT && g_status != 42)
	{
		g_status = 3;
		write(2, "Quit (core dumped)\n",
			ft_strlen("Quit (core dumped)\n"));
	}
}

int	ft_nb_pipes(t_list **lst_words)
{
	int		nb_pipes;
	t_list	*tmp;

	nb_pipes = 0;
	tmp = *lst_words;
	while (tmp)
	{
		if (((t_words *)tmp->content)->token == 0)
			nb_pipes++;
		tmp = tmp->next;
	}
	return (nb_pipes);
}
