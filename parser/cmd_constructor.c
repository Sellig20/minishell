/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:44:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/04 18:37:53 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (x->option[0][0] && x->option[0][0] == '/'
			&& access((x->option[0]), X_OK) == 0)
			x->pc = (x->option[0]);
		else
		{
			x->pc = ft_path_construction(cmd, x, cpenv);
			if (x->pc == NULL)
				return (EXIT_FAILURE);
			ft_free_array(x->option);
			x->option = ft_get_ultime_cmd(&tmp_cmd, x, x->pc);
			if (x->option == NULL)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;

	cmd_line = *cmd;
	(void)cpenv;
	x->option = NULL;
	x->pc = NULL;
	if (!cmd || !(*cmd) || (!cmd_line)
		|| !(((t_words *)cmd_line->content)->word))
		return (EXIT_FAILURE);
	else
	{
		if (ft_cmd_and_env(x, &cmd_line, cpenv) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
