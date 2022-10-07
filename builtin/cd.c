/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:43:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/07 18:04:15 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_old_pwd(t_list **cpenv, char *old_pwd)
{
	t_list	*envcp;
	char	*final_pwd;
	int		i;
	int		j;
	int		len;
	int		comp;

	i = 4;
	j = 0;
	comp = 0;
	envcp = *cpenv;
	while (envcp)
	{
		if (ft_strncmp(((t_words *)envcp->content)->word, "PWD=", 4) == 0)
			old_pwd = ((t_words *)envcp->content)->word;
		envcp = envcp->next;
	}
	len = ft_strlen(old_pwd) - 1;
	final_pwd = malloc(sizeof(char) * len + 1);
	while (old_pwd[len] && old_pwd[len] != '/')
		len--;
	while (i < len)
	{
		final_pwd[j] = old_pwd[i];
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
	char	*old_pwd;

	i = 0;
	len = 0;
	old_pwd = NULL;
	//dprintf(2, "-> %s\n", old_pwd);
	if (ft_lstsize(&cmd) > 2)
		return (ft_putstr_fd("Minimichel: cd: too many arguments\n", 2), EXIT_FAILURE);
	if (cmd->next)
		str = ((t_words *)cmd->next->content)->word;
	else
		str = "~";
	len = ft_strlen(str);
	if (str[i] == '~')
	{
		if (chdir("/mnt/nfs/homes/jecolmou") != 0)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(str, "..") == 0)
	{
		old_pwd = ft_get_old_pwd(cpenv, old_pwd);
		if (chdir(old_pwd) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (chdir(str) != 0)
			return (EXIT_FAILURE);
	}
	free(old_pwd);
	return (EXIT_SUCCESS);
}
