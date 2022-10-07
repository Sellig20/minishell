/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize_t_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:55:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/30 19:56:02 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	visualize_t_words(t_list **lst_words)
{
	t_list	*tmp;
	int		i;

	tmp = *lst_words;
	i = 0;
	while (tmp->next)
	{
		printf("1.maillon num %i : word = %s, token = %i\n", i, ((t_words *)tmp->content)->word, ((t_words *) tmp->content)->token);
		tmp = tmp->next;
		i++;
	}
	printf("2.maillon num %i : word = %s, token = %i\n", i, ((t_words *) tmp->content)->word, ((t_words *) tmp->content)->token);
}
