/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 00:43:09 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*heredoc_loop(char *new_lim, int fd, t_list **cpenv, t_data *x)
{
	t_list	**letter;
	t_list	**words;
	char	*line;

	while (1)
	{
		line = readline(">");
		letter = NULL;
		words = NULL;
		if (init_list_heredoc(&letter, &words) < 0)
			return (free(line), NULL);
		if (!(line) || ft_strcmp(new_lim, line) == 0)
			break ;
		pre_lexeur(x, line, letter);
		group_letters(letter, words);
		new_expand(words, cpenv, x);
		write_heredoc(words, fd);
		ft_lstclear(letter, ft_free_letters);
		ft_lstclear(words, ft_free_words);
		free(line);
	}
	return (ft_lstclear(letter, ft_free_letters),
		ft_lstclear(words, ft_free_words), free(line), NULL);
}

char	*get_flag(t_data *x, char *lim)
{
	t_list	**lim_letters;
	char	*new_lim;

	lim_letters = malloc(sizeof(t_letters *));
	if (lim_letters == NULL)
		return (NULL);
	*lim_letters = NULL;
	x->flag_heredoc = 168;
	pre_lexeur(x, lim, lim_letters);
	new_lim = heredoc_get_lim(*lim_letters, x);
	if (x->flag_heredoc == 84)
		x->flag_heredoc = 42;
	else if (ft_strcmp(new_lim, lim) == 0)
		x->flag_heredoc = -1;
	else
		x->flag_heredoc = 42;
	return (ft_lstclear(lim_letters, ft_free_letters), new_lim);
}

int	ft_read_heredoc(char *lim, t_list **cpenv, t_data *x)
{
	int		fd;
	char	*word;
	char	*new_lim;

	new_lim = NULL;
	word = ".HEREDOC";
	word = ft_strjoin(word, x->hered);
	fd = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(word);
	if (fd < 0)
		return (ft_putstr_fd("error heredoc\n", 2), EXIT_FAILURE);
	new_lim = get_flag(x, lim);
	heredoc_loop(new_lim, fd, cpenv, x);
	x->flag_heredoc = 0;
	free(new_lim);
	close(fd);
	return (fd);
}

void	is_heredoc(char *c, t_list *redir, t_list **cpenv, t_data *x)
{
	char	*word;

	if ((t_words *)redir->content
		&& ((t_words *)redir->content)->token == TOK_FRFR)
	{
		x->hered = malloc(sizeof(char) * 2);
		if (x->hered == NULL)
			return ;
		x->hered[0] = *c;
		x->hered[1] = '\0';
		x->infile = ft_read_heredoc(
				((t_words *)redir->next->content)->word, cpenv, x);
		((t_words *)redir->content)->token = TOK_FROM;
		free(((t_words *)redir->next->content)->word);
		word = ft_strjoin(".HEREDOC", x->hered);
		((t_words *)redir->next->content)->word
			= ft_strdup(word);
		free(word);
		(*c)++;
		free(x->hered);
	}
}

void	ft_heredoc(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list	*list;
	t_list	*redir;
	char	c;

	list = *tmp;
	redir = (t_list *)((t_cmdredir *)list->content)->redirection;
	c = 'a';
	while (list)
	{
		if (((t_cmdredir *)list->content)->redirection)
		{
			redir = (t_list *)((t_cmdredir *)list->content)->redirection;
			while (redir)
			{
				is_heredoc(&c, redir, cpenv, x);
				redir = redir->next;
			}
		}
		list = list->next;
	}
}
