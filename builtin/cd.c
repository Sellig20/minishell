/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:43:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 02:27:48 by jecolmou         ###   ########.fr       */
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

int	ft_cd_organisation(char *tmp, t_list **envcp, char *str, int i, t_data *x)
{
	t_list	*cpenv;
	char	*tmp1;
	char	*word;

	cpenv = (( tmp1 = getcwd(NULL, 0), *envcp));
	if (!tmp1)
		return (EXIT_FAILURE);
	word = ft_strjoin("OLDPWD=", tmp1);
	free(tmp1);
	if (str[i] == '~')
		ft_cd_is_til(tmp, word, cpenv, x);
	else if (ft_strcmp(str, "..") == 0)
		ft_cd_is_back(tmp, word, cpenv, x);
	else if (str[0] == 34 || str[0] == 39)
		ft_cd_is_quotes(str);
	else
	{
		str = ft_check_str(str);
		if (str && chdir(str) == 0)
			ft_change_oldpwd(word, tmp, cpenv, x);
		else
			return (free(word), EXIT_FAILURE);
		free(word);
	}
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_cd(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	char	*str;
	int		i;
	char	*tmp;

	if (!cpenv)
		return (EXIT_FAILURE);
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	i = 0;
	tmp = NULL;
	if (ft_lstsize(&cmd) > 2)
		return (ft_putstr_fd("Minimichel: cd: too many arguments\n", 2), 1);
	if (cmd->next)
		str = ((t_words *)cmd->next->content)->word;
	else
		str = "~";
	if (ft_cd_organisation(tmp, cpenv, str, i, x) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
