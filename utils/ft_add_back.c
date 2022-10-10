/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:02:46 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:03:02 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_btw_pipes	*ft_add_back(t_btw_pipes *btw_pipes, t_words **portion_words)
{
	t_btw_pipes	*tmp_btw_pipes;
	t_btw_pipes	*tmp;

	tmp_btw_pipes = malloc(sizeof(t_btw_pipes));
	if (tmp_btw_pipes == NULL)
		return (NULL);
	tmp_btw_pipes->portion_words = *portion_words;
	tmp_btw_pipes->next = NULL;
	tmp = btw_pipes;
	if (!tmp)
		btw_pipes = tmp_btw_pipes;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tmp_btw_pipes;
	}
	return (btw_pipes);
}
