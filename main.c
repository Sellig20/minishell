/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:40:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/15 23:28:24 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	ft_heart(t_data *x)
{
	x->nb_pipe = ft_nb_pipes(x->wo);
	ft_lim_protection(x->wo);
	new_expand(x->wo, x->cpv, x);
	if (ft_delete_space(x->wo) == 0)
	{
		sep_btw_pipes(x->wo, x->bp);
		ft_lstclear(x->wo, ft_free_words);
		ft_sep_cmd_redir(x->bp, x->seg);
		ft_lstclear(x->bp, ft_free_btw_pipes);
		ft_exec_organisor(x->seg, x->cpv, x);
	}
	else
	{
		ft_lstclear(x->wo, ft_free_words);
		free(x->bp);
	}
}

void	ft_bones(t_data *x)
{
	group_letters(x->let, x->wo);
	ft_lstclear(x->let, ft_free_letters);
	if (token_validity(x->wo) == 0 && token_order(x->wo) == 0)
		ft_heart(x);
	else
	{
		ft_lstclear(x->wo, ft_free_words);
		free(x->bp);
	}
}

void	ft_blood(t_data *x)
{
	ft_lstclear(x->let, ft_free_letters);
	free(x->wo);
	free(x->bp);
}

int	main(int ac, char **av, char **env)
{
	t_data		x;

	(void) ac;
	if (ft_born(&x.cpv, av, env, &x) < 0)
		return (1);
	while (1)
	{
		if (init_list(&x.let, &x.wo, &x.bp, &x.seg) < 0)
			return (ft_lstclear(x.cpv, ft_free_cpenv), 1);
		ft_reset_x(&x, *x.let, *x.wo, *x.bp);
		x.segment = x.seg;
		if (!(x.line))
			return (write(2, " exit\n", 6), ft_lstclear(x.cpv, ft_free_cpenv),
				ft_died(x.let, x.wo, x.bp, x.seg), 0);
		else
			add_history(x.line);
		if (pre_lexeur(&x, x.line, x.let) == 0)
			ft_bones(&x);
		else
			ft_blood(&x);
		ft_lstclear(x.seg, ft_free_cmd_redir);
		free(x.line);
	}
	return (rl_clear_history(), 0);
}
