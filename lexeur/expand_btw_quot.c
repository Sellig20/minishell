/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_btw_quot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:44:28 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/18 18:32:21 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_btw_quot(t_list **tmp, t_list **end, t_list **start)
{
	t_list	*swp = NULL;

	if (tmp == NULL)
		return ;
	// (void)tm;
	if ((*tmp) && (*tmp)->next)
		swp = (*tmp)->next;
	else
		swp = NULL;
	while (*end && *start && *start != *end)
	{
		if ((*start)->next)
			swp = (*start)->next;
		else
			swp = NULL;
//		printf("on delone start=%s\n", ((t_words *) (*start)->content)->word);
		ft_lstdelone(*start, ft_free_words);
		(*start) = swp;
	}
	if (*start)
		(*start) = swp;
}

static void	first_quot(t_list **tmp, t_list **lst, t_list **envcp, t_data *x)
{
	char	*word;
	t_list	*new;
	t_list	*start;
	t_list	*end;

	start = *tmp;
	// printf("start = %s\n", ((t_words *) start->content)->word);
	end = ft_find_end_quot(*tmp);
	word = ft_until_next_quot(*tmp, end, envcp, x);
	delete_btw_quot(tmp, &end, &start);
//	*lst = end;
	if (start)
		*tmp = start;
	else
		*tmp = NULL;
	//printf("start=>next = %s\n", ((t_words *) start->next->content)->word);

	if (!end || !(end->next))
	{
	//	printf("on delone start=%s\n", ((t_words *) (start)->content)->word);
		ft_lstdelone(start, ft_free_words);
		new = ft_lstnew((void *) words_init(word, TOK_WORD));
	  	free(word);
	   	*lst = new;
	}
	else
	{
		*lst = end;
		// printf("enddddddddd = %s\n", ((t_words *) end->content)->word);

		new = ft_lstnew((void *) words_init(word, TOK_WORD));
		free(word);
//		printf("1. new = %s,\n", ((t_words *) new->content)->word);
//		printf("lst =%s\n", ((t_words *) (*lst)->content)->word);
//		printf("lst next =%s\n", ((t_words *) (*lst)->next->content)->word);
//		printf("on addfront new a lst avec new =%s\n", ((t_words *) new->content)->word);
		if (*lst && (*lst)->content && (*lst)->next)
		{
	//		*lst = end;
		//	*tmp = (*lst)->next;
		//	ft_lstadd_front(tmp, new);
			ft_lstadd_front(lst, new);
			*tmp = end->next;
		//	printf("on delone lst=%s\n", ((t_words *) (*lst)->next->content)->word);
			ft_lstdelone((*lst)->next, ft_free_words);
			(*lst)->next = *tmp;
			// printf("YOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n\n\n");
			visualize_t_words(lst);
		}
		else
		{
	//		printf("on delone lst\n");
//			printf("on delone lst=%s\n", ((t_words *) (*lst)->content)->word);
			ft_lstdelone(*lst, ft_free_words);
			*lst = new;
			(*lst)->next = NULL;
		}
		// free(end);
	/*	if (end && end->next)
			(*tmp)->next = end->next;
		else
			(*tmp)->next = NULL;*/
//		else
//			(*tmp) = NULL;
	//	(*tmp) = (*tmp)->next;
	}
//	visualize_t_words(lst);
}

static void	other_quot(t_list **tmp, t_list **envcp, t_data *x)
{
	t_list	*start;
	t_list	*end;
	t_list	*swp;
	char	*word;
	t_list	*new;

	start = (*tmp)->next;
	// printf("je suis le gros start =[%s]\n", ((t_words *)start->content)->word);

	end = ft_find_end_quot(start->next);
	word = ft_until_next_quot((*tmp)->next->next, end, envcp, x);
	new = ft_lstnew((void *) words_init(word, TOK_WORD));
	free(word);
	ft_insert(new, end);
	// printf("je suis le gros tmp apres le gros insert  =[%s]\n", ((t_words *)(*tmp)->content)->word);

	// printf("Notre vizu est le suivant :\n");
	// visualize_t_words(tmp);
//	*tmp
//	swp = (*tmp)->next;
	delete_btw_quot(&swp, &end, &start);
	(*tmp)->next = swp;
	// printf("je suis le gros tmp->next =[%s]\n", ((t_words *)(*tmp)->next->content)->word);
	// printf("Notre vizu est le suivant :\n");
	visualize_t_words(&end);
	//(*tmp)->next = start->next;
	if (!end || !end->next)
	{
		// printf(" GROS IF\n\n\n");
		ft_lstdelone((*tmp)->next, ft_free_words);
	//	printf("on delone end=%s\n", ((t_words *) end->content)->word);
		(*tmp)->next = NULL;
	}
	else
	{
				// printf(" GROS ELSE\n\n\n");
		swp = end->next;
	//	printf("on delone end=%s\n", ((t_words *) end->content)->word);
		ft_lstdelone(end, ft_free_words);
		(*tmp)->next = swp;
	}
	(*tmp) = (*tmp)->next;
}

void	ft_expand_btw_quot(t_list **lst_words, t_list **envcp, t_data *x)
{
	t_list	*tmp;
	t_list	*swp;

	tmp = *lst_words;
	swp = NULL;
/*	while (tmp)
	{
		if (((t_words *) tmp->content)->token == TOK_QUOT)
		{
			swp = tmp->next;
			ft_lstdelone(tmp, (void *)ft_free_words);
			tmp = swp;
			first_quot(&tmp, lst_words, envcp, x);
			tmp = *lst_words;
		}
		else if (tmp->next && ((t_words *) tmp->next->content)->token == TOK_QUOT)
			other_quot(&tmp, envcp, x);
		else
			tmp = tmp->next;
	}
*/	if (tmp && ((t_words *) tmp->content)->token == TOK_QUOT)
	{
		if (tmp->next && ((t_words *) tmp->next->content)->token != TOK_QUOT)
		{
			swp = tmp->next;
	//		printf("on delone tmp =%s\n", ((t_words *) tmp->content)->word);
			ft_lstdelone(tmp, (void *)ft_free_words);
			tmp = swp;
			*lst_words = tmp;
		}
		first_quot(&tmp, lst_words, envcp, x);
		if (*lst_words)
			tmp = *lst_words;
		else
			tmp = NULL;
	}
	while (tmp && tmp->next)
	{
		if (tmp->next && ((t_words *) tmp->next->content)->token == TOK_QUOT)
			other_quot(&tmp, envcp, x);
		else
			tmp = tmp->next;
	}
	if (tmp && ((t_words *) tmp->content)->token == TOK_QUOT)
	{
		free(tmp);
		tmp = NULL;
	}
}
