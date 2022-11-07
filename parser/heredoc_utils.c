/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou   <jecolmou@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:50 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/05 00:43:09 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_get_lim(t_list *letters, t_data *x)
{
	char	*word;
	int		len;
	t_list	*tmp_len;
	t_list	*tmp;
	int		i;

	len = 1;
	i = 0;
	tmp_len = letters;
	tmp = letters;
	while (tmp_len && len++ > 0)
		tmp_len = tmp_len->next;
	word = malloc(sizeof(char) * len);
	while (tmp)
	{
		if (((t_letters *)tmp->content)->token != TOK_QUOT)
			word[i++] = ((t_letters *) tmp->content)->letter;
		if (((t_letters *)tmp->content)->token == TOK_DOLL)
			x->flag_heredoc = 84;
		tmp = tmp->next;
	}
	word[i] = '\0';
	return (word);
}

void	write_heredoc(t_list **words, int fd)
{
	t_list	*tmp;

	tmp = *words;
	while (words && tmp && tmp->content)
	{
		write(fd, ((t_words *)tmp->content)->word,
			ft_strlen(((t_words *)tmp->content)->word));
		tmp = tmp->next;
	}
	write(fd, "\n", 1);
}

int	init_list_heredoc(t_list ***letter, t_list ***words)
{
	*letter = malloc(sizeof(t_list *));
	if (*letter == NULL)
		return (-1);
	**letter = NULL;
	*words = malloc(sizeof(t_list *));
	if (*words == NULL)
		return (ft_lstclear(*letter, ft_free_letters), -1);
	**words = NULL;
	return (0);
}
