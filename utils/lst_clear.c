/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:03:15 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/17 18:21:47 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_clear_cmd_dir(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((void *)(*lst)->content);
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
			del((void *)(*lst)->content);
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
