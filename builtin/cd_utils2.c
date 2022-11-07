/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:40:04 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 02:24:43 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_oldpwd(char *word, t_list *cpenv, t_data *x)
{
	char	*tmp;
	char	*tmp1;

	ft_cd_unset("unset", "OLDPWD", cpenv, x);
	ft_cd_export("export", word, cpenv, x);
	ft_cd_unset("unset", "PWD", cpenv, x);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return ;
	tmp1 = ft_strjoin("PWD=", tmp);
	free(tmp);
	ft_cd_export("export", tmp1, cpenv, x);
	return (free(tmp1));
}

void	ft_cd_is_back(char *word, char *tmp1, t_list *cpenv, t_data *x)
{
	char	*tmp;

	tmp = ft_cd_back(tmp1);
	if (chdir(tmp) == 0)
		ft_change_oldpwd(word, cpenv, x);
	free(tmp);
	return (free(word));
}

void	ft_cd_is_til(char *tmp1, char *word, t_list *cpenv, t_data *x)
{
	char	*tmp;

	tmp = ft_cd_home(tmp1, &cpenv);
	if (chdir(tmp) == 0)
		ft_change_oldpwd(word, cpenv, x);
	free(tmp);
	return ;
}
