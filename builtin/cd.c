/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:43:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/10 10:59:48 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cd_home(char *tmp, t_list **cpenv)
{
	t_list	*envcp;
	char	*str_home;
	int		i;

	envcp = *cpenv;
	i = 0;
	while (envcp)
	{
		if (ft_strcmp(((t_words *)envcp->content)->word, ))
	}
}


char	*ft_cd_back(char *tmp)
{
	char	*final_pwd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	tmp = getcwd(NULL, 0);
	(void)tmp;
	len = ft_strlen(tmp) - 1;
	final_pwd = malloc(sizeof(char) * (len + 1));
	while (tmp[len] && tmp[len] != '/')
		len--;
	while (i < len)
	{
		final_pwd[j] = tmp[i];
		i++;
		j++;
	}
	final_pwd[j] = '\0';
	return (final_pwd);
}

int	ft_cd(t_list *cmd, t_list **cpenv)
{
	char	*str;
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = NULL;
	if (ft_lstsize(&cmd) > 2)
		return (ft_putstr_fd("Minimichel: cd: too many arguments\n", 2), EXIT_FAILURE);
	if (cmd->next)
		str = ((t_words *)cmd->next->content)->word;
	else
		str = "~";
	len = ft_strlen(str);
	if (str[i] == '~')
		return (chdir("/mnt/nfs/homes/jecolmou"), EXIT_SUCCESS);
	else if (ft_strcmp(str, "..") == 0)
	{
		tmp = ft_cd_back(tmp);
		if (chdir(tmp) != 0)
			return (EXIT_FAILURE);
	}
	else
		return (chdir(str), EXIT_SUCCESS);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
