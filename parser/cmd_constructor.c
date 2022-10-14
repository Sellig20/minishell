/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:44:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/14 16:31:24 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmd_and_env(t_data *x, char *co, t_list **cpenv)//if env else pas env
{
	t_list *tmp_cpenv;
	tmp_cpenv = *cpenv;
	if (!tmp_cpenv)
	{
		x->option = ft_split(co, ' ');
		if (access((x->option[0]), X_OK) == 0)
			*x->pc = *(x->option[0]);
		else
			ft_error_command_not_found(co);
	}
	else
	{
		x->option = ft_split(co, ' ');
		if (access((x->option[0]), X_OK) == 0) ////si env et que c le chemin absolu, rien besoin de construire on envoie direct
			*x->pc = *(x->option[0]);
		else
		{
			x->pc = ft_path_construction(co, x, cpenv); //join slash etc
			ft_free_array(x->option);
			x->option = ft_get_ultime_cmd(co, x->pc);
		}
	}
}

int	ft_strlen_cmd(t_list **cmd)
{
	int		len;
	t_list	*tmp;

	tmp = *cmd;
	len = 0;
	while (tmp)
	{
		len += ft_strlen(((t_words *)tmp->content)->word);
		tmp = tmp->next;
	}
	return (len);
}

char	*ft_conv_cmd_str(t_list **cmd, char *str)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = *cmd;
	str = NULL;
	while (tmp)
	{
		tmp_str = ((t_words *)tmp->content)->word;
		str = ft_strjoin(str, tmp_str);
		str = ft_strjoin(str, " ");
		tmp = tmp->next;
	}
	return (str);
}

int ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;
	t_list	*tmp;
	char	*str;

	tmp = *cmd;
	cmd_line = *cmd;
	(void)cpenv;
	x->option = NULL;
	x->pc = NULL;
	str = malloc(sizeof(char) * (ft_strlen_cmd(&tmp) + 1));
	str = ft_conv_cmd_str(&tmp,  str);
	if (cmd_line->content == NULL)
		write(2, "☆☆☆☆☆ PAS DE COMMANDE DANS CE MAILLON ☆☆☆☆☆\n", 25);
	else
	{
		if (cmd_line->next)///si ya une option a la commande
			ft_cmd_and_env(x, str,  cpenv);
		else//si ya pas doption genre ls ou wc seuls
		{
			ft_cmd_and_env(x, ((t_words *)cmd_line->content)->word, cpenv);
			x->option[1] = NULL;
		}
	}
	return (EXIT_SUCCESS);
}
