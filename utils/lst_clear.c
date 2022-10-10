/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:03:15 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:03:28 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_letters(void *content)
{
	t_letters *letters;

	letters = content;
	if (letters)
		free(letters);
}

void	ft_free_words(void *content)
{
	t_words *words;

	words = content;
	if (words)
	{
		if (words->word)
			free(words->word);
		free(words);
	}
}

void	ft_free_btw_pipes(void *content)
{
	t_btw_pipes *btw_pipes;

	btw_pipes = content;
	if (btw_pipes)
	{
		if (btw_pipes->portion_words)
			ft_lst_clear(&(btw_pipes->portion_words), ft_free_words);
	}
}

void	ft_free_cpenv(void *content)
{
	t_cpenv *cpenv;

	cpenv = content;
	if (cpenv)
	{
		if (cpenv->one_env)
			free(cpenv->one_env);
	}
	free(cpenv);
}

void	ft_free_cmd_redir(void *content)
{
	t_cmdredir *cmdredir;

	cmdredir = content;
	if (cmdredir)
	{
		if (cmdredir->cmd)
		{
			ft_lst_clear_cmd_dir(&(cmdredir->cmd), ft_free_words);
		}
		if (cmdredir->redirection)
		{
			ft_lst_clear_cmd_dir(&(cmdredir->redirection), ft_free_words);
		}
		free(cmdredir);
	}
}

void	ft_lst_clear_cmd_dir(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((void *) (*lst)->content);
		free((*lst));
		(*lst) = tmp;
	}
}

void	ft_lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	tmp = *lst;
	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			del((void *) (*lst)->content);
			free((*lst));
			(*lst) = tmp;
		}
		free(lst);
	}
}

void	ft_free_array(char **array)
{
	char	**tmp;

	tmp = array;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(array);
}

/*
typedef struct	s_data
{
	int	param;
	bool	bonjour;
	minilibx *libx;
	minilibx_windows *win;
}

signal_handler()
t_data *myfunc(void)
{
	static t_data	data;

	return (&data);
}
*/
