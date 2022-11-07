/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:40:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/07 21:06:36 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	sizeof_string_tab(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i + 1);
}

int ft_nb_pipes(t_list **lst_words)
{
	int nb_pipes;
	t_list *tmp;

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

void	handle_sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		sig = SIGCONT;
		write(2, "\n$>", 4);
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
	else if (sig == SIGINT)
	{
		sig = SIGQUIT;
		g_status = 2;
	}
	else if (sig == SIGQUIT && g_status == 42)
	{
		g_status = 3;
		write(2, "Quit (core dumped)\n",
			ft_strlen("Quit (core dumped)\n"));
	}
	else if (sig == SIGQUIT)
	{
		sig = SIGCONT;
		g_status = 3;
	}
}

int		init_list(t_list ***letters, t_list ***words, t_list ***btw_pipes, t_list ***segment)
{
		*letters = malloc(sizeof(t_list *));
		if (*letters == NULL)
			return (-1);
		**letters = NULL;
		*words = malloc(sizeof(t_list *));
		if (*words == NULL)
			return (ft_lstclear(*letters, ft_free_letters),-1);
		**words = NULL;
		*btw_pipes = malloc(sizeof(t_list *));
		if (*btw_pipes == NULL)
			return (ft_lstclear(*letters, ft_free_letters),
				ft_lstclear(*words, ft_free_words), -1);
		**btw_pipes = NULL;
		*segment = malloc(sizeof(t_list *));
		if (*segment == NULL)
			return (ft_lstclear(*letters, ft_free_letters),
				ft_lstclear(*words, ft_free_words),
				ft_lstclear(*btw_pipes, ft_free_btw_pipes ), -1);
		**segment = NULL;
		return (0);
}

void	ft_died(t_list **let, t_list **wor, t_list **btw, t_list **seg)
{
	if (let)
		ft_lstclear(let, ft_free_letters);
	let = NULL;
	if (btw)
		ft_lstclear(btw, ft_free_btw_pipes);
	btw = NULL;
	if (wor)
		ft_lstclear(wor, ft_free_words);
	wor = NULL;
	if (seg)
		ft_lstclear(seg, ft_free_cmd_redir);
	seg = NULL;
}

int	ft_born(t_list ***cpenv, char **av, char **env, t_data *x)
{
	(void) av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_parent);
	*cpenv = malloc(sizeof(t_list *));
	if (cpenv == NULL)
		return (-1);
	**cpenv = NULL;
	x->cpenv = **cpenv;
	ft_dup_env(env, *cpenv, x);
	g_status = 0;
	ft_bzero(x, sizeof(&x));
	return (0);
}

void	ft_reset_x(t_data *x, t_list *lst_letters, t_list *lst_words, t_list *lst_btw_pipes)
{
		x->words = lst_words;
		x->letters = lst_letters;
		x->btw_pipes = lst_btw_pipes;
		x->flag_executable = 0;
		x->flag_ambi = 0;
		x->flag_redir = 0;
		x->flag_stop = 0;
		x->flag_no_pipe_no_cmd_ok_redir = 0;
		x->finish = 0;
		x->res_echo = 0;
		x->only_n = 0;
		x->bad_friend = 0;
		x->flag_heredoc = 0;
		x->outfile = 0;
		x->infile = 0;
		x->count_files = 0;
		x->is_retrieve = 0;
		x->line = readline("$>");
}

int	main(int ac, char **av, char **env)
{
	t_data		x;
	t_list		**lst_letters;
	t_list		**lst_words;
	t_list		**lst_btw_pipes;
	t_list		**segment;
	t_list		**cpenv;

	(void) ac;
	rl_outstream = stderr;
	if (ft_born(&cpenv, av, env, &x) < 0)
		return (1);
	while (1)
	{
		if (init_list(&lst_letters, &lst_words, &lst_btw_pipes, &segment) < 0)
			return (ft_lstclear(cpenv, ft_free_cpenv), 1);
		ft_reset_x(&x, *lst_letters, *lst_words, *lst_btw_pipes);
		x.segment = *segment;
		if (!(x.line))
			return (write(2, " exit\n", 6), ft_lstclear(cpenv, ft_free_cpenv),
				ft_died(lst_letters, lst_words, lst_btw_pipes, segment), free(x.line), 1);
		else
			add_history(x.line);
		if (pre_lexeur(&x, x.line, lst_letters) == 0)
		{
			group_letters(lst_letters, lst_words);
			ft_lstclear(lst_letters, ft_free_letters);
			if (token_validity(lst_words) == 0 && token_order(lst_words) == 0)
			{
					x.nb_pipe = ft_nb_pipes(lst_words);
					ft_lim_protection(lst_words);
					new_expand(lst_words, cpenv, &x);
					if (ft_delete_space(lst_words) == 0)
					{
						sep_btw_pipes(lst_words, lst_btw_pipes);
						ft_lstclear(lst_words, ft_free_words);
						ft_sep_cmd_redir(lst_btw_pipes, segment);
					//	ft_visualize_cmd_redir(segment);
						ft_lstclear(lst_btw_pipes, ft_free_btw_pipes);
						ft_exec_organisor(segment, cpenv, &x);
					}
					else
					{
						ft_lstclear(lst_words, ft_free_words);
						free(lst_btw_pipes);
					}
			}
			else
			{
				ft_lstclear(lst_words, ft_free_words);
				free(lst_btw_pipes);
			}
		}
		else
		{
			ft_lstclear(lst_letters, ft_free_letters);
			free(lst_words);
			free(lst_btw_pipes);
		}
		ft_lstclear(segment, ft_free_cmd_redir);
		free(x.line);
	}
	return (rl_clear_history(), 0);
}
