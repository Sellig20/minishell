/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:54 by jecolmou          #+#    #+#             */
/*   Updated: 2022/06/30 15:42:26 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_args(char **args)
{
	char	**tmp;

	tmp = args;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(args);
}

int	refresh(t_data *data)
{
	render(data);
	return (1);
}

void	ft_display_move(t_data *data)
{
	char	*str;

	str = ft_itoa(data->move_count);
	ft_putstr_fd("Move = ", 1);
	write(1, str, ft_int_len(data->move_count));
	write(1, "\n", 1);
	free(str);
}

int	ft_exit_game(t_data *data)
{
	if (ft_un_alloc(data))
		exit(0);
	return (1);
}
