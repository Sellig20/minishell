/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:40:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/11 12:21:53 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_error_child(char **option, char *pc)
{
	ft_free_array(option);
	free(pc);
	return (perror("fork: "));
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

int	main(int ac, char **av, char **env)
{
	//char		*line;
	t_data		x;
	t_list		**lst_letters;
	t_list		**lst_words;
	t_list		**lst_btw_pipes;
	t_list		**segment;
	t_list		**cpenv;
	t_list		**after_doll;

	(void) ac;
	(void)av;

	while (1)
	{
	////////////////INITIALISATION DES MALLOCS/////////////////////
		lst_words = malloc(sizeof(t_list *));
		lst_letters = malloc(sizeof(t_list *));
		segment = malloc(sizeof(t_list *));
		cpenv = malloc(sizeof(t_list *));
		after_doll = malloc(sizeof(t_list *));

		ft_bzero(&x, sizeof(x));
		x.line = readline("$>");
		add_history(x.line);

	///////////////////////LEXER///////////////////////
		pre_lexeur(x.line, lst_letters);
		group_letters(lst_letters, lst_words);
		ft_lst_clear(lst_letters, ft_free_letters);
		token_validity(lst_words);
		token_order(lst_words);
		x.nb_pipe = ft_nb_pipes(lst_words);
		// printf("nb pipe = %d\n", x.nb_pipe);

	///////////////////////PARSER//////////////////////

		lst_btw_pipes = malloc(sizeof(t_list *));
		sep_btw_pipes(lst_words, lst_btw_pipes);
		//visualize_t_words(lst_words);
		ft_sep_cmd_redir(lst_btw_pipes, segment);
		//ft_visualize_btw_pipes(lst_btw_pipes);
		ft_lst_clear(lst_btw_pipes, ft_free_btw_pipes);
		//ft_visualize_cmd_redir(segment);

	///////////////////EXECUTION////////////////////////
		ft_dup_env(env, cpenv, &x);
		x.env = env;
		final_doll(segment, cpenv, after_doll, &x);
		ft_execution_organisation(after_doll, cpenv, &x);
		//ft_execution_nopipe(after_doll, cpenv, &x);
		//ft_visualize_cmd_redir(after_doll);

		//visualize_t_words(cpenv);
		//ft_organize_execution(&x, after_doll, cpenv);
		//printf("\n\n");
		//ft_fork_pipes(&x);

	//////////////////////FREE ALL///////////////////////
		ft_lst_clear(lst_words, ft_free_words);
		ft_lst_clear(segment, ft_free_cmd_redir);
		ft_lst_clear(cpenv, ft_free_cpenv);
		ft_lst_clear(after_doll, ft_free_cmd_redir);
		free(x.line);
	}
	return (0);
}
