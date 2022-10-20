/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:19:26 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/13 13:34:47 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_path_in_env(t_data *x, t_list **cpenv) //ft_get_path
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
		if (ft_strnstr(((t_cpenv *)tmp_cpenv->content)->one_env, "PATH=", 5))
		{
			tmp = ft_split(((t_cpenv *)tmp_cpenv->content)->one_env, '=');
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

char	*ft_construction_absolute_path_pc(char **path_env, char **option) // ft_return_pc
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

char	*ft_path_construction(char *co, t_data *x, t_list **cpenv)//ft_path_command
{
	char	**path_env;
	char	**option;
	char	*pc_final;

	if (!co)
		return (NULL);
	path_env = ft_get_path_in_env(x, cpenv); //on obtient notre tableau avec a chaque rangee, un bout de path de env
	if (!path_env)
		return (ft_error_command_not_found(co), NULL);
	option = ft_split(co, ' ');
	if (!option)
	{
		ft_free_array(path_env);
		return (NULL);
	}
	pc_final = ft_construction_absolute_path_pc(path_env, option);
	if (pc_final)
	{
		return (pc_final);
	}
	else
		ft_error_command_not_found(co);
	ft_free_array(path_env);
	ft_free_array(option);
	return (NULL);
}

char	**ft_get_ultime_cmd(char *co, char *pc) //ft_get_command pour join ma construction a mon option de commande
{
	char	**option;
	char	*tmp;

	if (!co || !pc)
		return (NULL);
	tmp = NULL;
	option = NULL;
	option = ft_split(co, ' ');
	if (!option)
	{
		free(pc);
		return (NULL);
	}
	tmp = option[0];
	option[0] = pc; //put l'absolut path dans option[0], option[1] ayant l'option de la commande.
	free(tmp);
	return (option);
}
