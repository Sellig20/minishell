
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:50:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/21 17:25:03 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **env)
{
	int		i;
	char	**paths;
	char	**tmp;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			tmp = ft_split(env[i], '=');
			if (!tmp)
				return (NULL);
			paths = ft_split(tmp[1], ':');
			ft_free_array(tmp);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	**ft_get_command(char *cmd, char *pc)
{
	char	**command;
	char	*tmp;

	if (!cmd || !pc)
		return (NULL);
	command = ft_split(cmd, ' ');
	if (!command)
	{
		free(pc);
		return (0);
	}
	tmp = command[0];
	command[0] = pc;
	free(tmp);
	return (command);
}

char	*ft_return_pc(char **command, char **path)
{
	char	*pc;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		pc = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (access(pc, X_OK) == 0)
		{
			ft_free_array(command);
			ft_free_array(path);
			return (pc);
		}
		free(pc);
		i++;
	}
	return (NULL);
}

char	*ft_path_command(char *cmd, char **env)
{
	char	**path;
	char	**command;
	char	*pc;

	command = NULL;
	if (!cmd)
		return (NULL);
	path = ft_get_path(env);
	if (path == NULL)
		return (ft_argv_error(cmd), NULL);
	command = ft_split(cmd, ' ');
	if (command == NULL)
	{
		ft_free_array(path);
		return (0);
	}
	pc = ft_return_pc(command, path);
	if (pc != NULL)
		return (pc);
	ft_argv_error(cmd);
	ft_free_array(command);
	ft_free_array(path);
	return (NULL);
}
