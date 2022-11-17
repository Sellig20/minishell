/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:33:46 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 01:43:52 by jecolmou         ###   ########.fr       */
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
	final = ft_calloc(sizeof(char), ft_strlen(executable));
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

int	ft_is_exe(t_list **tmp)
{
	t_list	*list;
	char	*executable;
	int		i;

	executable = NULL;
	list = *tmp;
	i = 0;
	if (!list || !((t_words *)list->content)
		|| !((t_words *)list->content)->word)
		return (EXIT_FAILURE);
	while (list)
	{
		executable = ((t_words *)list->content)->word;
		i = check_if_not(executable);
		if (i != 0)
			return (i);
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
	if (!final || !tmp)
		return (NULL);
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

char	*ft_is_exe2(t_list **tmp, char *isfull, char *final, t_data *x)
{
	t_list	*list;

	list = *tmp;
	final = ft_transform_executable(((t_words *)list->content)->word);
	isfull = ft_check_exec(((t_words *)list->content)->word, x, x->cpv, final);
	if (isfull == NULL)
		return (NULL);
	if (isfull && x->flag_uxu != 88)
	{
		x->flag_uxu = 5;
		free(final);
		return (ft_isad_error(((t_words *)list->content)->word,
				x, x->cpv), NULL);
	}
	isfull = ft_get_executable(final);
	free(final);
	x->flag_uxu = 5;
	if (!isfull)
	{
		x->flag_exua = 4;
		return ("MAGIKPONEY");
	}
	return (isfull);
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
	final = NULL;
	x->i_ex = -1;
	while (found_path[++x->i_ex])
	{
		pc_env = ft_strjoin(found_path[x->i_ex],
				((t_words *)list->content)->word);
		if (access(pc_env, X_OK) == 0)
		{
			isfull = ft_strjoin(isfull, pc_env);
			return (isfull);
		}
		free(pc_env);
	}
	ft_free_array(found_path);
	isfull = ft_is_exe2(&list, isfull, final, x);
	return (isfull);
}
