/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:22:45 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/27 00:41:17 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_equal(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '=')
		return (-42);
	while (cmd[i])
	{
		if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
			return ((i + 1) * (-1));
		if (cmd[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_first_alpha(char *cmd)
{
	if ((cmd[0] >= 'A' && cmd[0] <= 'Z')
		|| (cmd[0] >= 'a' && cmd[0] <= 'z'))
		return (0);
	return (1);
}

int	check_alnum(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '=' || cmd[i] == '+')
		return (1);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
			return (0);
		else if ((cmd[i] < 'A' || cmd[i] > 'Z') && (cmd[i] < 'a'
				|| cmd[i] > 'z') && (cmd[i] < '0' || cmd[i] > '9')
			&& cmd[i] != '_' && (cmd[i] == '+' && cmd[i + 1] == '='))
			return (1);
		i++;
	}
	return (0);
}

void	ft_insert(t_list *new, t_list *tmp)
{
	t_list	*swp;

	if (new == NULL || tmp == NULL)
		return ;
	swp = tmp->next;
	tmp->next = new;
	new->next = swp;
}
