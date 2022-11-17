/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:44:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 16:36:36 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_and_env_annexe(t_data *x, t_list **cmd, t_list **cpenv)
{
	t_list	*tmp_cmd;

	tmp_cmd = *cmd;
	x->pc = ft_path_construction(cmd, x, cpenv);
	if (x->pc == NULL)
		return (EXIT_FAILURE);
	ft_free_array(x->option);
	x->option = ft_get_ultime_cmd(&tmp_cmd, x, x->pc);
	if (x->option == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cmd_and_env(t_data *x, t_list **cmd, t_list **cpenv)
{
	t_list	*tmp_cpenv;
	t_list	*tmp_cmd;

	tmp_cpenv = *cpenv;
	tmp_cmd = *cmd;
	if (!tmp_cpenv)
		x->pc = ft_no_env_access_return(&tmp_cmd, x);
	else
	{
		x->option = get_env(tmp_cmd);
		if (!x->option)
			return (EXIT_FAILURE);
		if (x->option[0][0] && x->option[0][0] == '/'
			&& access((x->option[0]), X_OK) == 0)
				x->pc = (x->option[0]);
		else
		{
			if (ft_cmd_and_env_annexe(x, cmd, cpenv) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_constructor_cmdandenv(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;

	cmd_line = *cmd;
	if (ft_is_slash(&cmd_line) == EXIT_SUCCESS)
		ft_slash(&cmd_line, x, cpenv);
	if (ft_cmd_and_env(x, &cmd_line, cpenv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;

	cmd_line = *cmd;
	if (*cmd && !((t_words *)(*cmd)->content)->word)
	{
		ft_lstclear(cpenv, ft_free_words);
		ft_exit_bis("127", x);
	}
	if (cmd_line && ((((t_words *)cmd_line->content)->word
				&& (((t_words *)cmd_line->content)->word[0]) == '/'
				&& access(&(((t_words *)cmd_line->content)->word[0]),
					X_OK) != 0)))
	{
		ft_putstr_fd("Minimichel :", 2);
		perror(&((t_words *)cmd_line->content)->word[0]);
		ft_lstclear(cpenv, ft_free_words);
		ft_exit_bis("127", x);
	}
	(void)cpenv;
	x->option = NULL;
	x->pc = NULL;
	ft_constructor_cmdandenv(&cmd_line, x, cpenv);
	return (EXIT_SUCCESS);
}
