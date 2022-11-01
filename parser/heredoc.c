/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/01 18:31:05 by jecolmou         ###   ########.fr       */
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

char	*ft_supp_quotes(char *lim, int len)
{
	char	*new_lim;
	int		i;
	int		j;

	new_lim = calloc(sizeof(char), len);
	if (!new_lim)
		return (NULL);
	i = 0;
	j = 0;
	while (lim[i])
	{
		if (lim[i] == '"' && lim[i + 1] == '"')
			i += 2;
		else if (lim[i] == '\'' && lim[i + 1] == '\'')
			i += 2;
		else
		{
			if (((lim[i] == '"') && (lim[i + 1] != '"') && (lim[i + 1 ] != '\'')))
			{
				while (lim[i] != '"')
				{
					new_lim[j] = lim[i];
					i++;
					j++;
				}
				i++;
			}
			else if (((lim[i] == '\'') && (lim[i + 1] != '"') && (lim[i + 1 ] != '\'')) )
			{
				while (lim[i] != '"')
				{
					new_lim[j] = lim[i];
					i++;
					j++;
				}
				i++;
			}
			new_lim[j] = lim[i];
			i++;
			j++;
		}
	}
	return (new_lim);
}

int	ft_lim_is_quotes(char *lim)
{
	int		i;

	i = 0;
	while (lim[i])
	{
		if (lim[i] == '"' || lim[i] == '\'')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_read_infile_heredoc(t_list **list, char *lim, char *line, t_list **cpenv, t_data *x)
{
	int		fd;
	char	*word;
	t_list *letter;
	t_list *words;
	int		len;

	len = ft_strlen(lim);
	(void)list;
	letter = malloc(sizeof(t_letters));
	words = malloc(sizeof(t_words));
	word = ".HEREDOC";
	word = ft_strjoin(word, x->hered);
	fd = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("error heredoc\n", 2), EXIT_FAILURE);
	if (ft_lim_is_quotes(lim) == 0)
		lim = ft_supp_quotes(lim, len);
	dprintf(2, "lim = %s\n", lim);
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(lim, line, ft_strlen(lim)) == 0)
			break;
		pre_lexeur(x, line, &letter);
		group_letters(&letter, &words);
		new_expand(&words, cpenv, x);
		while (words)
		{
			write(fd, ((t_words *)words->content)->word, ft_strlen(((t_words *)words->content)->word));
			words = words->next;
		}
		write(fd, "\n", 1);
		line = ft_strjoin(line, "\n");
	}
	free(line);
	close(fd);
	return (fd);
}

void	ft_heredoc(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list *list;
	t_list *redir;
	char	c;

	list = *tmp;
	redir = (t_list *)((t_cmdredir *)list->content)->redirection;//necessaire ?
	c = 'a';
	x->hered = malloc(sizeof(char) * 2);
	while (list)
	{
		if (((t_cmdredir *)list->content)->redirection)
		{
			redir = (t_list *)((t_cmdredir *)list->content)->redirection;
			while (redir)
			{
				if ((t_words *)redir->content && ((t_words *)redir->content)->token == TOK_FRFR)
				{
					x->hered[0] = c;
					x->hered[1] = '\0';
					x->infile = ft_read_infile_heredoc(&redir, ((t_words *)redir->next->content)->word, x->line, cpenv, x);
					((t_words *)redir->content)->token = TOK_FROM;
					free(((t_words *)redir->next->content)->word);
					((t_words *)redir->next->content)->word = ft_strdup(ft_strjoin(".HEREDOC", x->hered));
					c++;
				}
				redir = redir->next;
			}
			list = list->next;
		}
	}
	free(x->hered);
}
