/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/04 18:39:40 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_ambi(t_list **tmp, t_data *x)
{
	t_list	*list;

	list = *tmp;
	while (list)
	{
		if ((ft_strncmp(((t_words *)list->content)->word, "<", 1) == 0
				|| ft_strncmp(((t_words *)list->content)->word, ">", 1) == 0
				|| ft_strncmp(((t_words *)list->content)->word, ">>", 1) == 0)
			&& (((((t_words *)list->next->content)->token == TOK_SPAC)
					&& ft_strncmp(((t_words *)list->next->next->content)->word,
						"$", 1) == 0)
				|| (ft_strncmp(((t_words *)list->next->content)->word,
						"$", 1) == 0)))
			x->key = 2;
		list = list->next;
	}
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
		printf("Minimichel: Error \n");
		return (false);
	}
	else if (ft_is_space(cmd) == 0)
	{
		ft_putstr_fd("Minimichel: Error\n", 2);
		return (false);
	}
	return (1);
}
