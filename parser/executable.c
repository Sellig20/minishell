/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:33:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/02 19:54:26 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_transform_executable(char *executable)
{
	char	*final;
	int		i;
	int		j;

	i = 1;
	j = 0;
	final = calloc(sizeof(char), ft_strlen(executable));
	if (!final)
		return (NULL);
	while (executable[i])
	{
		final[j] = executable[i];
		i++;
		j++;
	}
	return (final);
}

int	ft_is_exe(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list	*list;
	char	*executable;

	executable = NULL;
	list = *tmp;
	(void)x;
	(void)cpenv;
	while (list)
	{
		executable = ((t_words *)list->content)->word;
		if (executable[0] == '.' && executable[1] == '/')
			return (EXIT_SUCCESS);
		list = list->next;
	}
	return (EXIT_FAILURE);
}

char	*ft_get_executable(char	*final)
{
	char	*tmp;
	char	*tmp1;

	tmp = getcwd(NULL, 0);
	tmp1 = ft_strjoin(tmp, final);
	free(tmp);
	if (access(tmp1, X_OK) == 0)
		return (tmp1);
	else
	{
		free(tmp1);
		return (NULL);
	}
}

char	*ft_is_executable(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list	*list;
	char	**found_path;
	char	*final;
	char	*isfull;
	char	*pc_env;

	list = *tmp;
	found_path = ft_get_path_in_env(x, cpenv);
	isfull = NULL;
	final = ft_transform_executable(((t_words *)list->content)->word);
	x->i_ex = -1;
	while (found_path[++x->i_ex])
	{
		pc_env = ft_strjoin(found_path[x->i_ex], final);
		if (access(pc_env, X_OK) == 0)
			isfull = ft_strjoin(isfull, pc_env);
		free(pc_env);
	}
	if (isfull)
		return (isfull);
	isfull = ft_get_executable(final);
	ft_free_array(found_path);
	free(final);
	return (isfull);
}
