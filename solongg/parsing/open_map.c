/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:05:16 by jecolmou          #+#    #+#             */
/*   Updated: 2022/07/11 10:00:03 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error :\nInvalid argument\n", 2);
		return (0);
	}
	if (ft_strlen(argv[1]) == 0)
	{
		ft_putstr_fd("Error :\nInvalid argument\n", 2);
		return (0);
	}
	return (1);
}

int	ft_open_file(char **argv, t_data *x)
{
	x->file = open(argv[1], O_DIRECTORY);
	if (x->file > 2)
	{
		close(x->file);
		ft_putstr_fd("Error :\nInvalid folder\n", 2);
		return (0);
	}
	if (ft_read_infile(argv[1]) == 0)
		return (0);
	x->file = open(argv[1], O_RDONLY);
	if (x->file == -1)
	{
		ft_putstr_fd("Error :\nInvalid file\n", 2);
		return (0);
	}
	return (1);
}

void	ft_is_tab_null(t_map *save, t_data *x)
{
	free(x->str);
	get_next_line(x->file, 1);
	ft_lstclear(&save);
	return ;
}

int	ft_return(t_data *x)
{
	close(x->file);
	ft_putstr_fd("Error :\nEmpty map\n", 2);
	return (get_next_line(x->file, 1), 0);
}

int	ft_open_map(char **argv, t_data *x)
{
	t_map	*tab;
	t_map	*save;

	tab = NULL;
	save = NULL;
	if (ft_open_file(argv, x) == 0)
		return (0);
	x->str = get_next_line(x->file, 0);
	if (!x->str)
		return (ft_return(x));
	while (x->str)
	{
		tab = ft_add_back(tab, x->str);
		if (tab == NULL)
			ft_is_tab_null(save, x);
		save = tab;
		x->str = get_next_line(x->file, 0);
	}
	get_next_line(x->file, 1);
	if (close(x->file) || ft_execution_parsing_items(&tab, x) == 0)
		return (ft_lstclear(&tab), 0);
	if (ft_convert_in_char(&tab, x) == 0)
		return (ft_lstclear(&tab), 0);
	x->map = tab;
	return (1);
}
