/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:50:32 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 02:12:47 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_cd_error(void)
{
	ft_putstr_fd("pwd :error retrieving current directory: getcwd:", 2);
	ft_putstr_fd(" cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory", 2);
	ft_putstr_fd("\n", 2);
}

void	ft_cd_execption_supp_dir(char *join, char *word,
	t_list **cpenv, t_data *x)
{
	char	*tmp1;

	ft_cd_unset("unset", "OLDPWD", *cpenv, x);
	ft_cd_export("export", join, *cpenv, x);
	ft_cd_unset("unset", "PWD", *cpenv, x);
	tmp1 = getcwd(NULL, 0);
	word = ft_strjoin("PWD=", tmp1);
	free(tmp1);
	ft_cd_export("export", word, *cpenv, x);
	free(word);
}

int	ft_pwd(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	char	*word;
	char	*tmp;
	char	*join;

	(void)cmdredir;
	tmp = getcwd(NULL, 0);
	word = NULL;
	if (tmp)
	{
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_print_cd_error();
		word = ft_cd_home(word, cpenv);
		join = ft_strjoin("OLDPWD=", word);
		if (chdir(word) == 0)
			ft_cd_execption_supp_dir(join, word, cpenv, x);
		free(word);
		free(join);
		return (EXIT_SUCCESS);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
