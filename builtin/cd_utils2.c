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


void	ft_change_oldpwd(char *word, char *tmp, t_list *cpenv, t_data *x)
{
	ft_cd_unset("unset", "OLDPWD", cpenv, x);
	ft_cd_export("export", word, cpenv, x);
	ft_cd_unset("unset", "PWD", cpenv, x);
	tmp = getcwd(NULL, 0);
	word = ft_strjoin("PWD=", tmp);
	free(tmp);
	ft_cd_export("export", word, cpenv, x);
	free(word);
}

void	ft_cd_is_back(char *tmp, char *word, t_list *cpenv, t_data *x)
{
	tmp = ft_cd_back(tmp);
	if (chdir(tmp) == 0)
	{
		ft_change_oldpwd(word, tmp, cpenv, x);
		free(tmp);
		free(word);
	}
	else
	{
		free(word);
		free(tmp);
		return ;
	}
}

void	ft_cd_is_til(char *tmp, char *word, t_list *cpenv, t_data *x)
{
	tmp = ft_cd_home(tmp, &cpenv);
	if (chdir(tmp) == 0)
	{
		ft_change_oldpwd(word, tmp, cpenv, x);
		free(tmp);
		free(word);
	}
	else
	{
		free(word);
		free(tmp);
		return ;
	}
}
