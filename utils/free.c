/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
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
	t_letters	*letters;

	letters = content;
	if (letters)
		free(letters);
}

void	ft_free_words(void *content)
{
	t_words	*words;

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
	t_btw_pipes	*btw_pipes;

	btw_pipes = content;
	if (btw_pipes)
	{
		if (btw_pipes->portion_words)
			ft_lstclear(&(btw_pipes->portion_words), ft_free_words);
	}
}

void	ft_free_cpenv(void *content)
{
	t_words	*cpenv;

	cpenv = content;
	if (cpenv)
	{
		if (cpenv->word)
			free(cpenv->word);
	}
	free(cpenv);
}

void	ft_free_cmd_redir(void *content)
{
	t_cmdredir	*cmdredir;

	cmdredir = content;
	if (cmdredir)
	{
		if (cmdredir->cmd)
		{
			ft_lstclear_cmd_dir(&(cmdredir->cmd), ft_free_words);
		}
		if (cmdredir->redirection)
		{
			ft_lstclear_cmd_dir(&(cmdredir->redirection), ft_free_words);
		}
		free(cmdredir);
	}
}
