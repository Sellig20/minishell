/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor_annexe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:14:49 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 16:34:12 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_slash(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*tmp;

	tmp = *cmd;
	if (access(((t_words *)tmp->content)->word, X_OK) == 0)
		return ;
	else
	{
		perror(((t_words *)tmp->content)->word);
		ft_lstclear(cpenv, ft_free_words);
		return (ft_exit_bis("1", x));
	}
}

int	ft_is_slash(t_list **cmd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *cmd;
	while (tmp && ((t_words *)tmp->content)
		&& ((t_words *)tmp->content)->word
		&& ((t_words *)tmp->content)->word[i])
	{
		if (((t_words *)tmp->content)->word[i] == '/')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char	*ft_no_env_access_return(t_list **cmd, t_data *x)
{
	t_list	*tmp_cmd;

	tmp_cmd = *cmd;
	x->option = get_env(tmp_cmd);
	if (access((x->option[0]), X_OK) == 0)
		x->pc = (x->option[0]);
	else
		return (ft_error_command_not_f(x->option[0]), NULL);
	return (x->pc);
}
