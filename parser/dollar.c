/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:33:59 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/07 12:57:36 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_after_doll(char *word)
{
	int	i;

	i = 0;
	if (word[i] >= '0' && word[i] <= '9')
		return (1);
	else if (!((word[i] >= 'a' && word[i] <= 'z')
	|| (word[i] >= '0' && word[i] <= '9')
	|| (word[i] >= 'A' && word[i] <= 'Z')))
		return (2);
	while (word[i])
	{
		if (!((word[i] >= 'a' && word[i] <= 'z')
		|| (word[i] >= '0' && word[i] <= '9')
		|| (word[i] >= 'A' && word[i] <= 'Z')))
			return (4);
		i++;
	}
	return (3);
}

t_list	*ft_new_maillon_redir(t_list **tentative, t_list **envcp, t_data *x)
{
	t_list *new_maillon;
	t_list *redir;
	char	*new_echo;
	int		res;

	redir = *tentative;
	new_maillon = NULL;
	res = ft_check_after_doll(((t_words *)redir->next->content)->word);
	new_echo = ft_result(envcp, res, ((t_words *)redir->next->content)->word, x);
	new_maillon = ft_lstnew((void *) words_init(new_echo, TOK_WORD));
	free(new_echo);
	return (new_maillon);
}

t_list	**ft_expand_redir(t_list **list, t_list **envcp, t_data *x)
{
	t_list *new_maillon;
	t_list *redir;
	t_list **finale_list;

	x->key = 2;
	finale_list = malloc(sizeof(t_list*));
	if (!finale_list)
		return (NULL);
	*finale_list = NULL;
	redir = (t_list *)((t_cmdredir*)(*list)->content)->redirection;
	if (redir->content == NULL)
	{
		(*finale_list) = ft_lstnew(NULL);
		return (finale_list);
	}
	while (redir)
	{
		if (((t_words *)redir->content)->token == TOK_DOLL && redir->next) //creer le rsultat si tok dollar
			new_maillon = ft_new_maillon_redir(&redir, envcp, x);
		else
			new_maillon = ft_lstnew((void *) words_init(((t_words *)redir->content)->word, ((t_words *)redir->content)->token)); // sinon renvoyer
		finale_list = (t_list **)ft_lstadd_back2(finale_list, new_maillon);
		//il faut free new_maillon une fois quil est addback, parce que plus besoin du maillon seul.
		redir = redir->next;
	}
	if (!(*finale_list))
		(*finale_list) = ft_lstnew(NULL);
	return (finale_list);
}

t_list	*ft_new_maillon_cmd(t_list **tentative, t_list **envcp, t_data *x)
{
	t_list *new_maillon;
	t_list *tentativecmd;
	char	*new_echo;
	int		res;

	tentativecmd = *tentative;
	new_maillon = NULL;
	res = ft_check_after_doll(((t_words *)tentativecmd->next->content)->word);
	new_echo = ft_result(envcp, res, ((t_words *)tentativecmd->next->content)->word, x);
	new_maillon = ft_lstnew((void *) words_init(new_echo, TOK_WORD));
	free(new_echo);
	return (new_maillon);
}

t_list	**ft_expand_cmd(t_list **s_list, t_list **envcp, t_data *x)
{
	t_list *cmd;
	t_list *new_maillon;
	t_list **finale_list;

	x->key = 1;
	finale_list = malloc(sizeof(t_list*));
	if (!finale_list)
		return (NULL);
	*finale_list = NULL;
	new_maillon = NULL;
	cmd = ((t_cmdredir*)(*s_list)->content)->cmd;
	if (cmd->content == NULL)
	{
		(*finale_list) = ft_lstnew(NULL);
		return (finale_list);
	}
	while (cmd)
	{
		if (((t_words *)cmd->content)->token == TOK_DOLL && cmd->next) //creer le rsultat si tok dollar
		{
			new_maillon = ft_new_maillon_cmd(&cmd, envcp, x);
			cmd = cmd->next;
		}
		else
			new_maillon = ft_lstnew((void *) words_init(((t_words *)cmd->content)->word, TOK_WORD)); // sinon renvoyer
		finale_list = (t_list **)ft_lstadd_back2(finale_list, new_maillon);
		cmd = cmd->next;
	}
	if (!(*finale_list))
		(*finale_list) = ft_lstnew(NULL);
	return (finale_list);
}

t_cmdredir *init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x)
{
	t_cmdredir *new_cmd;
	t_list **remplircmd = NULL;
	t_list **remplirredir = NULL;
	if (!segment)
		return (NULL);
	new_cmd = malloc(sizeof(t_cmdredir));
	if (!new_cmd)
		return (NULL);
	remplircmd = ft_expand_cmd(segment, envcp, x);
	remplirredir = ft_expand_redir(segment, envcp, x);
	new_cmd->cmd = (*remplircmd);
	new_cmd->redirection = (*remplirredir);
	free(remplircmd);
	free(remplirredir);
	return (new_cmd);
}

void	final_doll(t_list **segment, t_list **envcp, t_list **after_doll, t_data *x)
{
	t_list *final;
	t_list *seg;

	*after_doll = NULL;
	seg = *segment;
	final = NULL;
	while (seg)
	{
		final = ft_lstnew((void *) init_with_new_dollar(&seg, envcp, x));
		after_doll = (t_list **)ft_lstadd_back2(after_doll, final);
		seg = seg->next;
	}
}
