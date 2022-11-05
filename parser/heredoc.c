/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 22:19:22 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_heredoc(char *line, t_list **cpenv, int res, t_data *x)
{
	int		i;
	int		j;
	char	*final;

	(void)res;
	(void)cpenv;
	(void)x;
	i = 1;
	j = 0;
	final = malloc(sizeof(char) * ft_strlen(line - 1) + 1);
	if (!final)
		return (NULL);
	while (line[i])
	{
		final[j] = line[i];
		i++;
		j++;
	}
	return (final);
}

char	*get_lim(t_list *letters)
{
	char	*word;
	int		len;
	t_list	*tmp_len;
	t_list	*tmp;
	int		i;

	len = 1;
	i = 0;
	tmp_len = letters;
	tmp = letters;
	while (tmp_len && len++ > 0)
		tmp_len = tmp_len->next;
	word = malloc(sizeof(char) * len);
	while (tmp)
	{
		if (((t_letters *) tmp->content)->token != TOK_QUOT)
			word[i++] = ((t_letters *) tmp->content)->letter;
		tmp = tmp->next;
	}
	word[i] = '\0';
	return (word);
}

void	write_heredoc(t_list **words, int fd)
{
	t_list	*tmp;

	tmp = *words;
	while (words && tmp && tmp->content)
	{
		write(fd, ((t_words *)tmp->content)->word,
			ft_strlen(((t_words *)tmp->content)->word));
		tmp = tmp->next;
	}
	write(fd, "\n", 1);
}

void	heredoc_loop(char *new_lim, int fd, t_list **cpenv, t_data *x)
{
	t_list	**letter;
	t_list	**words;
	char	*line;

	while (1)
	{
		line = readline(">");
		letter = malloc(sizeof(t_list *));
		*letter = NULL;
		words = malloc(sizeof(t_list *));
		*words = NULL;
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
	ft_lstclear(letter, ft_free_letters);
	ft_lstclear(words, ft_free_words);
	free(line);
}

int	ft_read_heredoc(char *lim, t_list **cpenv, t_data *x)
{
	int		fd;
	char	*word;
	char	*new_lim;
	t_list	**lim_letters;

	new_lim = NULL;
	lim_letters = malloc(sizeof(t_letters *));
	*lim_letters = NULL;
	word = ".HEREDOC";
	word = ft_strjoin(word, x->hered);
	fd = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(word);
	if (fd < 0)
		return (ft_putstr_fd("error heredoc\n", 2), EXIT_FAILURE);
	x->flag_heredoc = 42;
	pre_lexeur(x, lim, lim_letters);
	new_lim = get_lim(*lim_letters);
	heredoc_loop(new_lim, fd, cpenv, x);
	ft_lstclear(lim_letters, ft_free_letters);
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
