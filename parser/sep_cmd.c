/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:36:45 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 15:59:35 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_not_cmd(t_list *portion)
{
	if ((((t_words *)portion->content)->token != TOK_DOLL
			&& ((t_words *)portion->content)->token != TOK_WORD)
		&& (!(portion->next->next)))
	{
		dprintf(2, "je passe par ici 1\n");
		return (1);
	}
	return (0);
}

int	ft_check_dollar_followed(t_list *portion)
{
	if (((t_words *)portion->content)->token != TOK_WORD
		&& ((t_words *)portion->next->content)->token == TOK_DOLL
		&& ((t_words *)portion->next->next->content)->token == TOK_WORD
		&& portion->next->next->next)
	{
		dprintf(2, "je passe par ici 2\n");
		return (1);
	}
	return (0);
}

int	ft_check_dollar(t_list *portion)
{
	if (((t_words *)portion->content)->token != TOK_WORD
		&& ((t_words *)portion->next->content)->token == TOK_DOLL
		&& ((t_words *)portion->next->next->content)->token == TOK_WORD)
	{
		dprintf(2, "je passe par ici 3\n");
		return (1);
	}
	return (0);
}

int	ft_check_cmd_followed(t_list *portion)
{
	if (((t_words *)portion->content)->token != TOK_DOLL
		&& ((t_words *)portion->content)->token != TOK_WORD
		&& portion->next->next)
	{
		dprintf(2, "je passe par ici 4\n");
		return (1);
	}
	return (0);
}

int	ft_sort_cmd(t_list *portion)
{
	if (ft_check_not_cmd(portion) == 1)
		return (1);
	if (ft_check_dollar(portion) == 1)
		return (1);
	return (0);
}
