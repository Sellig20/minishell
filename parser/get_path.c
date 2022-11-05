/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:19:26 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/03 23:56:21 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_path_in_env(t_data *x, t_list **cpenv)
{
	t_list	*tmp_cpenv;
	int		i;
	char	**found_path;
	char	**tmp;

	tmp_cpenv = *cpenv;
	(void)x;
	(void)i;
	i = 0;
	if (!cpenv)
		return (NULL);
	while (tmp_cpenv)
	{
		if (ft_strnstr(((t_words *)tmp_cpenv->content)->word, "PATH=", 5))
		{
			tmp = ft_split(((t_words *)tmp_cpenv->content)->word, '=');
			if (!tmp)
				return (NULL);
			found_path = ft_split(tmp[1], ':');
			ft_free_array(tmp);
			return (found_path);
		}
		tmp_cpenv = tmp_cpenv->next;
	}
	return (NULL);
}

char	*ft_construction_absolute_path_pc(char **path_env, char **option)
{
	char	*pc;
	char	*tmp;
	int		i;

	i = 0;
	while (path_env[i])
	{
		tmp = ft_strjoin(path_env[i], "/");
		pc = ft_strjoin(tmp, option[0]);
		free(tmp);
		if (access(pc, X_OK) == 0)
		{
			ft_free_array(path_env);
			ft_free_array(option);
			return (pc);
		}
		free(pc);
		i++;
	}
	return (NULL);
}

char	*ft_path_construction(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*tmp_cmd;
	char	**path_env;
	char	**option;
	char	*pc_final;

	tmp_cmd = *cmd;
	path_env = ft_get_path_in_env(x, cpenv);
	if (!path_env)
		return (ft_error_command_not_f(x->option[0]),
			ft_exit_bis("127", x), NULL);
	option = get_env(tmp_cmd);
	if (!option)
		return (ft_free_array(path_env), NULL);
	pc_final = ft_construction_absolute_path_pc(path_env, option);
	if (pc_final)
		return (pc_final);
	else
	{
		ft_error_command_not_f(x->option[0]);
		ft_exit_bis("127", x);
	}
	ft_free_array(path_env);
	ft_free_array(option);
	return (NULL);
}

char	**ft_get_ultime_cmd(t_list **cmd, t_data *x, char *pc)
{
	t_list	*cmd_line;
	char	**option;
	char	*tmp;

	cmd_line = *cmd;
	(void)x;
	if (!pc)
		return (NULL);
	tmp = NULL;
	option = NULL;
	option = get_env(cmd_line);
	if (!option)
	{
		free(pc);
		return (NULL);
	}
	tmp = option[0];
	option[0] = pc;
	free(tmp);
	return (option);
}
