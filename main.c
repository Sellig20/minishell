/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:40:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/18 18:32:31 by jecolmou         ###   ########.fr       */
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
	t_list		**after_doll;

	(void) ac;
	(void) av;
//	g_status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sig_parent);
	cpenv = malloc(sizeof(t_list *));
	*cpenv = NULL;
	x.env = env;
	ft_dup_env(env, cpenv, &x);
//	*cpenv = NULL;
	while (1)
	{
	////////////////INITIALISATION DES MALLOCS/////////////////////
		g_status = 0;
		lst_words = malloc(sizeof(t_list *));
		*lst_words = NULL;
		lst_letters = malloc(sizeof(t_list *));
		*lst_letters = NULL;
		segment = malloc(sizeof(t_list *));
		*segment = NULL;
		after_doll = malloc(sizeof(t_list *));
		*after_doll = NULL;
		lst_btw_pipes = malloc(sizeof(t_list *));
		*lst_btw_pipes = NULL;
		ft_bzero(&x, sizeof(x));
		x.line = readline("$>");
		if (!(x.line))
		{
			write(2, " exit\n", 6);
			ft_lst_clear(lst_letters, ft_free_letters);
			ft_lst_clear(lst_words, ft_free_words);
			ft_lst_clear(segment, ft_free_cmd_redir);
			ft_lst_clear(cpenv, ft_free_cpenv);
			ft_lst_clear(after_doll, ft_free_cmd_redir);
			free(x.line);
			return (1);
//			ft_exit();
		}
		else
			add_history(x.line);
	///////////////////////LEXER///////////////////////
		pre_lexeur(x.line, lst_letters);

		group_letters(lst_letters, lst_words);
	//	visualize_t_words(lst_words);
		ft_lst_clear(lst_letters, ft_free_letters);
		token_validity(lst_words);
		token_order(lst_words);
		x.nb_pipe = ft_nb_pipes(lst_words);
///////////////////////PARSER//////////////////////

//		visualize_t_words(lst_words);
		ft_dup_env(env, cpenv, &x);
		ft_lim_protection(lst_words);
//		visualize_t_words(lst_words);
		ft_expand_btw_quot(lst_words, cpenv, &x);
//		printf("-----------after_expand-----------------\n");
//		visualize_t_words(lst_words);
		ft_delete_space(lst_words);

//		visualize_t_words(lst_words);
//		visualize_t_words(lst_words);
		sep_btw_pipes(lst_words, lst_btw_pipes);
		ft_sep_cmd_redir(lst_btw_pipes, segment);
//		ft_visualize_btw_pipes(lst_btw_pipes);
		ft_lst_clear(lst_btw_pipes, ft_free_btw_pipes);
		// ft_visualize_cmd_redir(segment);

		final_doll(segment, cpenv, after_doll, &x);
		ft_execution_organisation(after_doll, cpenv, &x);
//		ft_execution_nopipe(after_doll, cpenv, &x);
//		ft_visualize_cmd_redir(after_doll);

		//visualize_t_words(cpenv);
		//ft_organize_execution(&x, after_doll, cpenv);
		//printf("\n\n");
		//ft_fork_pipes(&x);
//	if (*after_doll && (t_cmdredir *)(*after_doll)->content)
/*	{
		if (strcmp(((t_words *)((t_cmdredir *)(*after_doll)->content)->cmd->content)->word, "export") == 0)
			ft_export((((t_cmdredir *)(*after_doll)->content)->cmd->next), cpenv);
		else if (strcmp(((t_words *)((t_cmdredir *)(*after_doll)->content)->cmd->content)->word, "unset") == 0)
			ft_unset((((t_cmdredir *)(*after_doll)->content)->cmd->next), cpenv);
//		else if (strcmp(((t_words *)((t_cmdredir *)(*segment)->content)->cmd->content)->word, "env") == 0)
//			ft_env((((t_cmdredir *)(*segment)->content)->cmd->next), cpenv);
	}*/


	//////////////////////FREE ALL///////////////////////
		ft_lst_clear(lst_words, ft_free_words);
//		ft_lst_clear(segment, ft_free_cmd_redir);
//		ft_lst_clear(cpenv, ft_free_cpenv);
//		ft_lst_clear(after_doll, ft_free_cmd_redir);
		free(x.line);
	}
	return (0);
}
