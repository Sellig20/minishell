/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:21 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/31 21:08:10 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_read_infile(char *infile, t_data *x)
{
	int file;
	(void)x;
	file = open(infile, O_RDONLY);
	if (file < 0)
		ft_exist_error(infile, x);
	return (file);
}

int	ft_read_outfile_append(char *outfile, t_data *x)
{
	int	file;

	file = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file < 0)
		ft_perm_error(outfile, x);
	return (file);
}

int	ft_read_outfile(char *outfile, t_data *x)
{
	int	file;

	file = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		ft_perm_error(outfile, x);
	return (file);
}
