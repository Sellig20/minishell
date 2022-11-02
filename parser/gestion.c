/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/02 19:52:39 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_ambi(t_list **tmp, t_data *x)
{
	t_list *list;

	list = *tmp;
	while (list)
	{
		if ((ft_strncmp(((t_words *)list->content)->word, "<", 1) == 0
			|| ft_strncmp(((t_words *)list->content)->word, ">", 1) == 0
			|| ft_strncmp(((t_words *)list->content)->word, ">>", 1) == 0)
					&&
			((  ( ((t_words *)list->next->content)->token == TOK_SPAC) && ft_strncmp(((t_words *)list->next->next->content)->word, "$", 1) == 0)
			|| (ft_strncmp(((t_words *)list->next->content)->word, "$", 1) == 0)))
			x->key = 2;
		list = list->next;
	}
}

void	ft_error_command_not_found(char *cmd)
{
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	tmp = ft_strjoin(cmd, ": command not found");
	tmp1 = ft_strjoin("MMMinimichel: ", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
}

int	ft_is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && cmd[i + 1] == '\0')
			return (false);
		i++;
	}
	return (true);
}

int	ft_is_null(char *cmd)
{
	if (ft_strlen(cmd) == 0)
	{
		printf("Error \n");
		return (false);
	}
	else if (ft_is_space(cmd) == 0)
	{
		ft_putstr_fd("JE SUIS FT_IS_NULL DANS GESTION\n", 2);
		return (false);
	}
	return (1);
}

int	ft_error_nsfod(char *infile)
{
	// int		i;
	// int		j;
	// char	*print;

	// i = 0;
	// j = 0;
	// print = malloc(sizeof(char) * (ft_strlen(infile)));
	// //print = NULL;
	// while (infile[i])
	// {
	// 	print[j] = infile[i];
	// 	i++;
	// 	j++;
	// }
	// print[j] = '\0';
	// ft_putstr_fd("Minimichel: ", 2);
	// write(2, print, ft_strlen(print));
	// ft_putstr_fd(": No such file or directory", 2);
	// write(2, "\n", 1);
	char	*tmp;
	char	*tmp1;
	char	*to_return;

	tmp = ft_strjoin(infile, ": No such file or directory");
	tmp1 = ft_strjoin("MMMMMMMinimichel: ", tmp);
	to_return = ft_strjoin(tmp1, "\n");
	write(2, to_return, ft_strlen(to_return));
	free(to_return);
	free(tmp);
	free(tmp1);
	return (false);
}

int	ft_error_ambigous_redirect(char *word, int len)
{
	ft_putstr_fd("Minimichel: $", 2);
	write(2, word, len);
	ft_putstr_fd(": ambigous redirect\n", 2);
	return (false);
}
