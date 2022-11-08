/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:43:55 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/08 23:48:46 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cd_dash(char *str, t_list **cpenv, t_data *x)
{
	t_list	*envcp;
	char	*tmp;
	int		len;
	char	*str_dash;

	(void)str;
	x->cdj = 7;
	x->cdk = 0;
	envcp = *cpenv;
	while (envcp)
	{
		if (ft_strncmp(((t_words *)envcp->content)->word, "OLDPWD=", 7) == 0)
			tmp = ((t_words *)envcp->content)->word;
		envcp = envcp->next;
	}
	len = ft_strlen(tmp) - 7;
	str_dash = malloc(sizeof(char) * (len + 1));
	if (!str_dash)
		return (NULL);
	while (tmp[x->cdj])
		str_dash[x->cdk++] = tmp[x->cdj++];
	str_dash[x->cdk] = '\0';
	return (str_dash);
}

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
	if (!str_home)
		return (NULL);
	while (tmp[i])
		str_home[j++] = tmp[i++];
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
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp) - 1;
	final_pwd = malloc(sizeof(char) * (len + 1));
	if (!final_pwd)
		return (free(tmp), NULL);
	while (tmp[len] && tmp[len] != '/')
		len--;
	while (i < len)
	{
		final_pwd[j] = tmp[i];
		i++;
		j++;
	}
	final_pwd[j] = '\0';
	return (free(tmp), final_pwd);
}

int	ft_cd_organisation(char *tmp, t_list **cpenv, char *str, t_data *x)
{
	char	*word;
	char	*word1;

	word1 = getcwd(NULL, 0);
	if (!word1)
		return (EXIT_SUCCESS);
	word = ft_strjoin("OLDPWD=", word1);
	free(word1);
	if (str && str[x->cdi] == '~')
		ft_cd_is_til(tmp, word, *cpenv, x);
	else if (str && ft_strcmp(str, "..") == 0)
		ft_cd_is_back(tmp, word, *cpenv, x);
	else if (str && str[0] == '-')
		ft_cd_is_dash(tmp, word, *cpenv, x);
	else if (str && (str[0] == 34 || str[0] == 39))
		ft_cd_is_quotes(str);
	else
	{
		str = ft_check_str(str, cpenv, x);
		if (str && chdir(str) == 0)
			return (ft_change_oldpwd(word, *cpenv, x), free(word), 0);
		else
			return (free(word), free(tmp), EXIT_FAILURE);
	}
	return (free(tmp), EXIT_SUCCESS);
}

int	ft_cd(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*cmd;
	char	*str;
	char	*tmp;

	if (!cpenv)
		return (EXIT_FAILURE);
	cmd = ((t_cmdredir *)cmdredir->content)->cmd;
	tmp = NULL;
	if (ft_lstsize(&cmd) > 2)
		return (ft_putstr_fd("Minimichel: cd: too many arguments\n", 2), 1);
	if (cmd->next)
		str = ((t_words *)cmd->next->content)->word;
	else
		str = "~";
	if (ft_cd_organisation(tmp, cpenv, str, x) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
