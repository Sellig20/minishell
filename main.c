/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:40:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/03 20:55:46 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	visualize_string_tab(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		printf("str[%i] = %s\n", i, str[i]);
		i++;
	}
}

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
		sig = SIGCONT;
		write(2, "\n$>", 4);
	}
}

void	handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		sig = SIGQUIT;
		write(2, "\n", 1);
//		g_status = 2;
	}
	else if (sig == SIGQUIT)
	{
//		g_status = 3;
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
	}

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
	(void) av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_parent);
	cpenv = malloc(sizeof(t_list *));
	*cpenv = NULL;
	x.cpenv = *cpenv;
	ft_dup_env(env, cpenv, &x);
	g_status = 0;
	ft_bzero(&x, sizeof(x));
	while (1)
	{
	////////////////INITIALISATION DES MALLOCS/////////////////////
		lst_words = malloc(sizeof(t_list *));
		*lst_words = NULL;
		x.words = *lst_words;
		lst_letters = malloc(sizeof(t_list *));
		*lst_letters = NULL;
		x.letters = *lst_letters;
		segment = malloc(sizeof(t_list *));
		*segment = NULL;
		x.segment = *segment;
		lst_btw_pipes = malloc(sizeof(t_list *));
		*lst_btw_pipes = NULL;
		x.btw_pipes = *lst_btw_pipes;
		x.line = readline("$>");
		x.flag_executable = 0;
		x.flag_ambi = 0;
		x.flag_redir = 0;
		x.flag_stop = 0;
		x.flag_no_pipe_no_cmd_ok_redir = 0;
		x.finish = 0;
		x.res_echo = 0;
		x.only_n = 0;
		x.bad_friend = 0;
		if (!(x.line))
		{
			write(2, " exit\n", 6);
			ft_lstclear(lst_letters, ft_free_letters);
			ft_lstclear(lst_btw_pipes, ft_free_btw_pipes);
			ft_lstclear(lst_words, ft_free_words);
			ft_lstclear(segment, ft_free_cmd_redir);
			ft_lstclear(cpenv, ft_free_cpenv);
			free(x.line);
			return (1);
		}
		else
			add_history(x.line);
		//////////////////LEXER////////////////
		if (pre_lexeur(&x, x.line, lst_letters) == 0)
		{
			group_letters(lst_letters, lst_words);
			ft_lstclear(lst_letters, ft_free_letters);
			if (token_validity(lst_words) == 0)
			{
				if (token_order(lst_words) == 0)
				{
					x.nb_pipe = ft_nb_pipes(lst_words);
					//////////////////PARSER////////////////
					ft_lim_protection(lst_words);
					new_expand(lst_words, cpenv, &x);
					ft_delete_space(lst_words);
					sep_btw_pipes(lst_words, lst_btw_pipes);
					ft_sep_cmd_redir(lst_btw_pipes, segment);
					ft_lstclear(lst_btw_pipes, ft_free_btw_pipes);
					//////////////////EXECUTION////////////////
					ft_exec_organisation(segment, cpenv, &x);
				}
			}
		}
		//////////////FREE ALL///////////////
		ft_lstclear(lst_words, ft_free_words);
		ft_lstclear(segment, ft_free_cmd_redir);
		free(x.line);
	}
	return (0);
}
