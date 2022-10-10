/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:45 by evsuits           #+#    #+#             */
/*   Updated: 2022/09/27 15:01:42 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_equal(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i] == '+' && cmd[i + 1] == '=')
			return ((i + 1) * (-1));
		if (cmd[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_if_first_alpha(char *cmdnext)
{
	if ((cmdnext[0] >= 'A' && cmdnext[0] <= 'Z')
		|| (cmdnext[0] >= 'a' && cmdnext[0] <= 'z'))
		return (0);
	return (1);
}

int	check_if_alphanum(char *cmdnext)
{
	int	i;

	i = 0;
	if (cmdnext[i] == '=' || cmdnext[i] == '+')
		return (1);
	while (cmdnext[i] && cmdnext[i] != '=')
	{
		if (cmdnext[i] == '+' && cmdnext[i + 1] && cmdnext[i + 1] == '=')
			return (0);
		else if ((cmdnext[i] < 'A' || cmdnext[i] > 'Z') && (cmdnext[i] < 'a'
				|| cmdnext[i] > 'z') && (cmdnext[i] < '0' || cmdnext[i] > '9')
			&& cmdnext[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_insert(t_list *new, t_list *tmp)
{
	t_list	*swp;

	swp = tmp->next;
	tmp->next = new;
	new->next = swp;
}
