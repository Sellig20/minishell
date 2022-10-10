/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:33:10 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/10 18:06:24 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exist_error(char *infile)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, infile, ft_strlen(infile));
	write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
	return (false);
}

int	ft_exist_error_directory(char *infile)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, infile, ft_strlen(infile));
	write(2, ": Not a directory", 28);
	write(2, "\n", 1);
	return (false);
}

int	ft_perm_error(char *file)
{
	ft_putstr_fd("minimichel: ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": permission denied", 19);
	write(2, "\n", 1);
	return (false);
}

int	ft_read_infile(char *infile)
{
	// if (access(infile, O_RDONLY))
		return (open(infile, O_RDONLY));
	// else if (access(infile, O_DIRECTORY))
	//  	return (open(infile, O_DIRECTORY));
	// return (-1);
}

char	*ft_expand_heredoc(char *line, t_list **cpenv, int res, t_data *x)
{
	int		i;
	int		j;
	char	*final;

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
	res = ft_check_after_doll(final);
	final = ft_result(cpenv, res, final, x);
	return (final);
}

int	ft_read_infile_heredoc(char *lim, char *line, t_list **cpenv, t_data *x)
{
	int	fd;
	int	res;

	res = 0;
	fd = open(".HEREDOC", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("error heredoc\n", 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		write(1, ">", 1);
		line = readline(STDIN_FILENO);
		if (ft_strncmp(line, "$", 1) == 0)
			line = ft_expand_heredoc(line, cpenv, res, x);
		if (ft_strncmp(lim, line, ft_strlen(lim)) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (line[0] == '\0')
			write(1, "\n", 1);
		line = ft_strjoin(line, "\n");
	}
	free(line);
	return (fd);
}

int	ft_read_outfile_append(char *outfile)
{
	return (open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644));
}

int	ft_read_outfile(char *outfile)
{
	return (open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

void	ft_redirection_in(int infile)
{
	dup2(infile, STDIN_FILENO);
	close(infile);
}

void	ft_redirection_out(int outfile)
{
	dup2(outfile, STDOUT_FILENO);
	close (outfile);
}

void	ft_catch_file(t_list **redir, t_data *x, t_list **cpenv)
{
	t_list *tmp;
	int	file;

	file = 0;
	tmp = *redir;
	(void)x;
	if (((t_words *)tmp->content) == NULL)
	{
		//dprintf(2, "☆☆☆☆☆ PAS DE REDIR DANS CE MAILLON ☆☆☆☆☆\n");
		// dup2(0, STDIN_FILENO);
		// dup2(1, STDOUT_FILENO);
		// close (0);
		// close (1);
		return ;
	}
	while (tmp && tmp->content) // chaque maillon de mes redir
	{
		if ( ((t_words *)tmp->content)->token == TOK_FRFR) //heredoc
		{
			file = ft_read_infile_heredoc(((t_words *)tmp->next->content)->word, x->line, cpenv, x);
			if (file < 0)
				ft_exist_error(((t_words *)tmp->next->content)->word);
			else
				ft_redirection_in(file);
		}
		else if ( ((t_words *)tmp->content)->token == TOK_FROM) //in
		{
			file = ft_read_infile(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_exist_error(((t_words *)tmp->next->content)->word);
			else
				ft_redirection_in(file);
		}
		else if ( ((t_words *)tmp->content)->token == TOK_TOTO)//append
		{
			file = ft_read_outfile_append(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_perm_error(((t_words *)tmp->next->content)->word);
			else
				ft_redirection_out(file);
		}
		else if ( ((t_words *)tmp->content)->token == TOK_TO)//out
		{
			file = ft_read_outfile(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_perm_error(((t_words *)tmp->next->content)->word);
			else
				ft_redirection_out(file);
		}
		tmp = tmp->next;
	}
}

void	ft_redirection_in_tekf(int infile, t_data *x)
{
	dup2(infile, x->fd_pipe[0]);
	close(infile);
}

void	ft_redirection_out_tekf(int outfile, t_data *x)
{
	dup2(outfile, x->fd_pipe[1]);
	close (outfile);
}

void	ft_catch_file_tekflemme(t_list **after_doll, t_data *x)
{
	t_list *tmp;
	//t_list *tentativeredir;
	int	file;

	file = 0;
	tmp = *after_doll;
	(void)x;
	if (((t_words *)tmp->content) == NULL)
		return ;
	while (tmp && tmp->content) // chaque maillon de mes redir
	{
		if ( ((t_words *)tmp->content)->token == TOK_FRFR) //heredoc
		{
			//file = ft_read_infile_heredoc(((t_words *)tmp->next->content)->word, x->line);
			if (file < 0)
				ft_exist_error(((t_words *)tmp->next->content)->word);
			((t_cmdredir *) tmp->content)->fd_cmd[0] = file;
		}
		else if ( ((t_words *)tmp->content)->token == TOK_FROM) //in
		{
			file = ft_read_infile(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_exist_error(((t_words *)tmp->next->content)->word);
			((t_cmdredir *) tmp->content)->fd_cmd[0] = file;
		}
		else if ( ((t_words *)tmp->content)->token == TOK_TOTO)//append
		{
			file = ft_read_outfile_append(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_perm_error(((t_words *)tmp->next->content)->word);
			((t_cmdredir *) tmp->content)->fd_cmd[1] = file;
		}
		else if ( ((t_words *)tmp->content)->token == TOK_TO)//out
		{
			file = ft_read_outfile(((t_words *)tmp->next->content)->word);
			if (file < 0)
				ft_perm_error(((t_words *)tmp->next->content)->word);
			((t_cmdredir *) tmp->content)->fd_cmd[1] = file;
		}
		tmp = tmp->next;
	}
}
