/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:44:25 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/11 18:41:54 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_option(t_list **cmd_line)
{
	t_list	*cmd;
	int		i;
	int		len;
	char	*tmp;
	int		len_finale;

	i = 0;
	len = 0;
	len_finale = 0;
	cmd = *cmd_line;
	while (cmd)
	{
		if (cmd->content)
			tmp = ((t_words *)cmd->content)->word;
		else
			return (0);
		if (tmp[0] == '-')
		{
			while (tmp[i] != '\0')
				i++;
			len = i - 1;
		}
		len_finale += len;
		cmd = cmd->next;
	}
	return (len_finale);
}

void	ft_error_cannot_access(char *str, char *first)
{
	ft_putstr_fd(first, 2);
	ft_putstr_fd(": cannot access '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': NOOOOOOOOOOOOOOO such file or directory\n", 2);
}

int	ft_join_option_error(char *str, char *first, t_list **cmd)
{
	t_list	*cmd_line;

	cmd_line = *cmd;
	str = ((t_words *)cmd_line->content)->word;
	return (ft_error_cannot_access(str, first) , 1);
}

char	*ft_cp_options(t_list *cmd_line, int len, char *tt, char *first, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (cmd_line)
	{
		tt = ((t_words *)cmd_line->content)->word;
		len = ft_strlen(tt);
		if (len == 1)
			return (ft_join_option_error(tt, first, &cmd_line), NULL);
		else if (len > 1 && tt[0] == '-')
		{
			i = 1;
			res[0] = '-';
			while(i < len && tt[i])
			{
				res[j] = tt[i];
				i++;
				j++;
			}
		}
		cmd_line = cmd_line->next;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_join_options(t_list **cmd, t_data *x)
{
	t_list	*cmd_line;
	char	*tt;
	char	*res;
	char	*first;
	int		len;

	len = 0;
	cmd_line = *cmd;

	first = ((t_words *)cmd_line->content)->word;
	dprintf(2, "first = %s\n", first);
	tt = NULL;
	if (!cmd)
		return (NULL);
	//if (((t_words *)cmd_line->next->content)->word[0] == '-')
	x->i_len = ft_strlen_option(&cmd_line);
	// else
	// 	x->i_len = ft_strlen_option_cat(&cmd_line);
	dprintf(2, "i_len = %d\n", x->i_len);
	res = malloc(sizeof(char) * (x->i_len + 2));
	ft_bzero(res, x->i_len + 1);
	if (!res)
		return (NULL);
	cmd_line = cmd_line->next;
	res = ft_cp_options(cmd_line, len, tt, first, res);
	return (res);
}

void	ft_cmd_and_env(t_data *x, char *co, char *opt, t_list **cpenv)//if env else pas env
{
	t_list *tmp_cpenv;
	tmp_cpenv = *cpenv;
	if (!tmp_cpenv)
	{
		x->option = ft_split(co, ' ');
		if (access((x->option[0]), X_OK) == 0)
			*x->pc = *(x->option[0]);
		else
			write(2, "ERROR : PAS DE ENV ET PAS DE ABSOLUTE PATH = TU DEGAGES JE SUIS PAS DEVIN BIATCH\n", 35);
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
			x->option = ft_get_ultime_cmd(co, opt, x->pc); //absolute path + option = ultime collage
		}
	}
}

int ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv)
{
	t_list	*cmd_line;
	t_list	*tmp_cpenv;
	char	*opt;

	cmd_line = *cmd;
	tmp_cpenv = *cpenv;
	(void)tmp_cpenv;
	x->option = NULL;
	x->pc = NULL;
	opt = NULL;
	if (cmd_line->content == NULL)
		write(2, "☆☆☆☆☆ PAS DE COMMANDE DANS CE MAILLON ☆☆☆☆☆\n", 25);
	else
	{
		dprintf(2, "=> %s\n", ((t_words *)cmd_line->content)->word);
		if (cmd_line->next)///si ya une option a la commande
		{
			if (((t_words *)cmd_line->next->content)->word[0] == '-')
				opt = ft_join_options(&cmd_line, x);
			else
				opt = ((t_words *)cmd_line->next->content)->word;
			if (!opt)
				return (EXIT_FAILURE);
			ft_cmd_and_env(x, ((t_words *)cmd_line->content)->word, opt, cpenv);
			free(opt);
		}
		else//si ya pas doption genre ls ou wc seuls
		{
			ft_cmd_and_env(x, ((t_words *)cmd_line->content)->word, ((t_words *)cmd_line->content)->word, cpenv);
			x->option[1] = NULL;
		}
	}
	return (EXIT_SUCCESS);
}
