/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 16:49:06 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_check_ambi(t_list **tmp, t_data *x)
{
	t_list	*list;

	if (!tmp || x->doc != 0)
		return ;
	list = *tmp;
	while (list)
	{
		if ((((t_words *)list->content)->token == TOK_FROM
				|| ((t_words *)list->content)->token == TOK_TO
				|| ((t_words *)list->content)->token == TOK_TOTO)
			&& (((((t_words *)list->next->content)->token == TOK_SPAC
						&& ft_strncmp(
							((t_words *)list->next->next->content)->word,
							"$", 1) == 0)
					|| (ft_strncmp(((t_words *)list->next->content)->word,
							"$", 1) == 0))))
			x->key = 2;
		list = list->next;
	}
}

void	ft_set_error(char *str)
{
	ft_putstr_fd("Minimichel : ", 2);
	g_status = 1;
	perror(str);
}

char	*ft_check_exec(char *str, t_data *x, t_list **cpenv, char *final)
{
	DIR		*d;

	(void)x;
	if (!str)
		return (free(str), NULL);
	d = opendir(str);
	if (d == NULL && access(str, X_OK) == 0)
		x->flag_uxu = 88;
	else if (d == NULL && x->flag_uxu != 5)
	{
		ft_set_error(str);
		if (final)
			free(final);
		if (x->is_pi == 66)
		{
			ft_lstclear(cpenv, ft_free_words);
			ft_exit_bis("1", x);
		}
		else
			return (NULL);
	}
	else if (d == NULL && x->i_ex != -1)
		return (NULL);
	return (closedir(d), str);
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
		ft_putstr_fd("Minimichel: Error \n", 2);
		return (false);
	}
	else if (ft_is_space(cmd) == 0)
	{
		ft_putstr_fd("Minimichel: Error\n", 2);
		return (false);
	}
	return (1);
}
