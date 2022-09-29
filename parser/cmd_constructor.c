/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:44:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/29 18:48:33 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_options(t_list **cmd, t_data *x)
{
	t_list *cmd_line;
	t_list *tmp;
	char	*tt;
	char	*res;
	int		i;
	int		j;

	cmd_line = *cmd;
	tmp = *cmd;
	i = 0;
	j = 1;
	while (cmd_line)
	{
		tt = ((t_words *)cmd_line->content)->word;
		if(tt[0] == '-')
		{
			while (tt[i] != '\0')
				i++;
			i--;
			x->i_len = x->i_len + i;
		}
		cmd_line = cmd_line->next;
	}
	res = malloc(sizeof(char) * x->i_len + 2);
	ft_bzero(res, x->i_len + 2);
	if (!res)
		return (NULL);
	while (tmp)
	{
		tt = ((t_words *)tmp->content)->word;
		i = 0;
		if (tt[0] == '-')
		{
			i = 1;
			res[0] = '-';
			while(tt[i])
			{
				res[j] = tt[i];
				j++;
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (res);
}

void	ft_cmd_and_env(t_data *x, char *co, char *opt, t_list **cpenv)//if env else pas env
{
	t_list *tmp_cpenv;
	//int i = 0;
	tmp_cpenv = *cpenv;
	if (!tmp_cpenv)
	{
		x->option = ft_split(co, ' ');
		if (access((x->option[0]), X_OK) == 0)
			*x->pc = *(x->option[0]);
		else
			write(2, "ERROR : PAS DE ENV ET PAS DE ABSOLUTE PATH = TU DEGAGES JE SUIS PAS DEVIN BIATCH\n", 15);
	}
	else
	{
		x->option = ft_split(co, ' ');
		if (access((x->option[0]), X_OK) == 0) ////si env et que c le chemin absolu, rien beosin de cnostruire on envoie direct bb
			*x->pc = *(x->option[0]);
		else
		{
			x->pc = ft_path_construction(co, x, cpenv); //join slash etc
			ft_free_array(x->option);
			x->option = ft_get_ultime_cmd(co, opt, x->pc); //absolute path + option = ultime collage
		}
	}
}

int ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;
	t_list	*tmp_cpenv;
	char	*opt;

	(void)tmp_cpenv;
	cmd_line = *cmd;
	tmp_cpenv = *cpenv;
	x->option = NULL;
	x->pc = NULL;
	opt = malloc(sizeof(char) * x->i_len + 1);
	opt = ft_join_options(&cmd_line, x);
	if (cmd_line->content == NULL)
		write(2, "☆☆☆☆☆ PAS DE COMMANDE DANS CE MAILLON ☆☆☆☆☆\n", 25);
	else
	{
		if (cmd_line->next)///si ya une option a la commande
		{
			ft_cmd_and_env(x, ((t_words *)cmd_line->content)->word, opt, cpenv);
			free(opt);
			if (!x->option)
			{
				// dprintf(2, "x->option[0] = null\n");
				// dprintf(2, "x->option[1] = null\n");
				// dprintf(2, "x->pc = null\n");
				return (false);
			}
		}
		else//si ya pas doption genre ls ou wc seuls
		{
			// dprintf(2, "oui pas doption\n");
			// dprintf(2, "cmdline content = \n");
			// dprintf(2, "=>>>> %s\n", ((t_words *)cmd_line->content)->word);
			ft_cmd_and_env(x, ((t_words *)cmd_line->content)->word, ((t_words *)cmd_line->content)->word, cpenv);
			x->option[1] = NULL;
		}
	}
	return (true);
}
