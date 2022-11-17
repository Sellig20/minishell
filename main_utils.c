/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:29:16 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 01:16:16 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	init_list(t_list ***letters, t_list ***words,
	t_list ***btw_pipes, t_list ***segment)
{
	*letters = malloc(sizeof(t_list *));
	if (*letters == NULL)
		return (-1);
	**letters = NULL;
	*words = malloc(sizeof(t_list *));
	if (*words == NULL)
		return (ft_lstclear(*letters, ft_free_letters), -1);
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
			ft_lstclear(*btw_pipes, ft_free_btw_pipes), -1);
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
	ft_dup_env(env, *cpenv);
	g_status = 0;
	ft_bzero(x, sizeof(&x));
	return (0);
}

void	ft_reset_x(t_data *x, t_list *lst_letters,
	t_list *lst_words, t_list *lst_btw_pipes)
{
	x->file = 0;
	x->key = 0;
	x->words = lst_words;
	x->letters = lst_letters;
	x->btw_pipes = lst_btw_pipes;
	x->flag_exua = 0;
	x->flag_ambi = 0;
	x->flag_redir_builtin = 0;
	x->flag_stop = 0;
	x->flag_no_pipe_no_cmd_ok_redir = 0;
	x->finish = 0;
	x->res_echo = 0;
	x->only_n = 0;
	x->is_pi = 0;
	ft_reset_2x(x);
}

void	ft_reset_2x(t_data *x)
{
	x->bad_friend = 0;
	x->doc = 0;
	x->outfile = 0;
	x->infile = 0;
	x->count_files = 0;
	x->is_retrieve = 0;
	x->bretzel = 0;
	x->builtin = 0;
	x->cdj = 0;
	x->cdk = 0;
	x->i_ex = 0;
	x->flag_uxu = 0;
	x->dot_n_zero = 0;
	x->first_is_dot = 0;
	x->isalpha = 0;
	x->dot_space = 0;
	x->flag_file_down = 0;
	x->line = readline("$>");
}
