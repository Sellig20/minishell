/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:50:32 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 02:48:04 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

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

void	ft_print_pwd(char *tmp, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
	{
		ft_putstr_fd(tmp, x->outfile);
		ft_putstr_fd("\n", x->outfile);
	}
	else
	{
		ft_putstr_fd(tmp, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	}
}

int	ft_pwd(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	char	*tmp;

	(void)cmdredir;
	tmp = getcwd(NULL, 0);
	(void)cpenv;
	if (tmp)
		ft_print_pwd(tmp, cmdredir, x);
	else
	{
		ft_print_cd_error();
		return (EXIT_SUCCESS);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
