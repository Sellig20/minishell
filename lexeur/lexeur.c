/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:41:59 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/10 01:06:06 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quote_management(t_letters *letters, int *i, t_data *x)
{
	if (letters->letter == '"' && *i == DEFAULT_STATE)
	{
		letters->token = TOK_QUOT;
		*i = D_QUOTE_STATE;
		return (1);
	}
	else if (letters->letter == '"' && *i == D_QUOTE_STATE)
	{
		letters->token = TOK_QUOT;
		*i = DEFAULT_STATE;
		return (1);
	}
	else if (letters->letter == '\'' && *i == DEFAULT_STATE && x->doc == 0)
	{
		letters->token = TOK_QUOT;
		*i = S_QUOTE_STATE;
		return (1);
	}
	else if (letters->letter == '\'' && *i == S_QUOTE_STATE && x->doc == 0)
	{
		letters->token = TOK_QUOT;
		*i = DEFAULT_STATE;
		return (1);
	}
	return (0);
}

static	t_letters	*letters_init(char letter, int *i, t_data *x)
{
	t_letters	*letters;

	letters = malloc(sizeof(t_letters));
	if (!letters)
		return (NULL);
	letters->letter = letter;
	if (quote_management(letters, i, x) == 1)
		return (letters);
	else if (letter == '$' && *i != S_QUOTE_STATE)
		letters->token = TOK_DOLL;
	else if (x->doc != 0)
		letters->token = TOK_WORD;
	else if ((letter == ' ' || letter == '\v' || letter == '\t'
			|| letter == '\f' || letter == '\r' || letter == '\n')
		&& *i == DEFAULT_STATE)
		letters->token = TOK_SPAC;
	else if (letter == '>' && *i == DEFAULT_STATE)
		letters->token = TOK_TO;
	else if (letter == '<' && *i == DEFAULT_STATE)
		letters->token = TOK_FROM;
	else if (letter == '|' && *i == DEFAULT_STATE)
		letters->token = TOK_PIPE;
	else
		letters->token = TOK_WORD;
	return (letters);
}

void	visualize_t_letters(t_list **lst_letters)
{
	t_list	*tmp;
	int		i;

	tmp = *lst_letters;
	i = 0;
	while (tmp->next)
	{
		printf("1.maillon num %i : letter = %c, token = %i\n", i,
			((t_letters *)tmp->content)->letter,
			((t_letters *)tmp->content)->token);
		tmp = tmp->next;
		i++;
	}
	printf("2.maillon num %i : letter = %c, token = %i\n", i,
		((t_letters *)tmp->content)->letter,
		((t_letters *)tmp->content)->token);
}

int	pre_lexeur(t_data *x, char *line, t_list **lst_letters)
{
	int		i;
	int		*j;
	t_list	*new;

	i = 1;
	j = malloc(sizeof(int));
	if (!j)
		return (-1);
	*j = DEFAULT_STATE;
	if (line == NULL || !(line[0]))
		return (free(j), 1);
	new = ft_lstnew((void *)letters_init(line[0], j, x));
	*lst_letters = new;
	while (line[i])
	{
		new = ft_lstnew((void *)letters_init(line[i], j, x));
		ft_lstadd_back(lst_letters, new);
		i++;
	}
	if (x->doc == 0 && *j != DEFAULT_STATE)
		return (free(j), syntax_error(*lst_letters, 8), 1);
	return (free(j), 0);
}
