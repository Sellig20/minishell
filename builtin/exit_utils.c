/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evsuits <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:28:21 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/26 16:23:35 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char c)
{
	if (!c)
		return (-1);
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_islonglong(long long nb, int signe)
{
	if ((nb * signe) > 922337203685477807
		|| (nb * signe) < -922337203685477808)
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	long long	nb;
	int			i;
	int			signe;

	i = 0;
	nb = 0;
	signe = 1;
	if (!str || !(str[i]))
		return (-42);
	while (str[i] == ' ')
		i++;
	if ((str[i] == '+') && ft_isdigit(str[i + 1]) == 1)
		i++;
	else if (str[i] == '-' && ft_isdigit(str[i + 1]) == 1 && i++ != -42)
		signe = (-1) * signe;
	while (str[i] && ft_isdigit(str[i]) == 1)
		nb = nb * 10 + (str[i++] - 48);
	if (ft_isdigit(str[i]) != -1 || ft_islonglong(nb, signe) == 1)
		return (922337203685477808);
	return (nb * signe);
}
