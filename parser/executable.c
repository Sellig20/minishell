/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:33:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/28 14:34:32 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_transform_executable(char *executable)
{
	char	*final;
	int		i;
	int		j;

	i = 2;
	j = 0;
	final = calloc(sizeof(char) , ft_strlen(executable) - 1);
	if (!final)
		return (NULL);
	while (executable[i])
	{
		final[j] = executable[i];
		i++;
		j++;
	}
	final[j] = '\0';
	return (final);
}

int	ft_is_exe(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list *list;
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

char	*ft_is_executable(t_list **tmp, t_data *x, t_list **cpenv)
{
	t_list *list;
	char	*executable;
	char	*final;
	char	*tmp1;
	char	*tmp2;
	char	**found_path;
	char	*pc_env;
	char	*tmp_env;

	found_path = ft_get_path_in_env(x, cpenv);
	list = *tmp;
	(void)x;
	int i = 0;
	(void)cpenv;
	tmp1 = NULL;
	tmp2 = NULL;
	final = NULL;
	executable = NULL;
	executable = ((t_words *)list->content)->word;
	final = ft_transform_executable(executable);
	while (found_path[i])
	{
		tmp_env = ft_strjoin(found_path[i], "/");
		pc_env = ft_strjoin(tmp_env, final);
		if (access(pc_env, X_OK) == 0)
			return (pc_env);
		i++;
		free(pc_env);
		free(tmp_env);
	}
	ft_free_array(found_path);
	tmp1 = getcwd(NULL, 0);
	tmp2 = ft_strjoin(tmp1, "/");
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, final);
	free(tmp2);
	free(final);
	if (access(tmp1, X_OK) == 0)
		return (tmp1);
	return (NULL);
}
