/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:43:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/14 13:17:50 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cd_home(char *tmp, t_list **cpenv)
{
	t_list	*envcp;
	int		i;
	int		j;
	char	*str_home;
	int		len;

	envcp = *cpenv;
	i = 5;
	j = 0;
	while (envcp)
	{
		if (ft_strncmp(((t_words *)envcp->content)->word, "HOME=", 5) == 0)
			tmp = ((t_words *)envcp->content)->word;
		envcp = envcp->next;
	}
	len = ft_strlen(tmp) - 5;
	str_home = malloc(sizeof(char) * (len + 1));
	while (tmp[i])
	{
		str_home[j] = tmp[i];
		i++;
		j++;
	}
	str_home[j] = '\0';
	return (str_home);
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
	free(tmp);
	return (final_pwd);
}

char	*ft_check_str(char *str)
{
	int	i;
	DIR	*d;

	i = 0;
	d = opendir(str);
	if (d == NULL)
	{
		ft_putstr_fd("Minimichel: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	free(d);
	return (str);
}

int	ft_cd_organisation(char *tmp, t_list **envcp, char *str, int i)
{
	t_list	*cpenv;

	cpenv = *envcp;
	if (str[i] == '~')
	{
		tmp = ft_cd_home(tmp, &cpenv);
		if (chdir(tmp) != 0)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(str, "..") == 0)
	{
		tmp = ft_cd_back(tmp);
		if (chdir(tmp) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		str = ft_check_str(str);
		if (str && chdir(str) != 0)
			return (EXIT_FAILURE);
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_list *cmd, t_list **cpenv, t_data *x)
{
	char	*str;
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = NULL;
	(void)x;
	if (ft_lstsize(&cmd) > 2)
		return (ft_putstr_fd("Minimichel: cd: too many arguments\n", 2), 1);
	if (cmd->next)
		str = ((t_words *)cmd->next->content)->word;
	else
		str = "~";
	len = ft_strlen(str);
	if (ft_cd_organisation(tmp, cpenv, str, i) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
