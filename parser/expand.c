/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:40:31 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 00:09:19 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

char	*ft_methode_1(char *w, char *word, t_dollar *d, t_data *x)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	(void)x;
	w = malloc(sizeof(char) * (d->len_word + 1));
	if (!w)
		return (NULL);
	ft_bzero(w, d->len_word + 1);
	while (word[i])
	{
		w[j] = word[i];
		i++;
		j++;
	}
	if (x->key == 2 && d->len_word == 1 && x->doc == 0)
	{
		x->flag_stop = 2;
		return (free(w), ft_error_ambigous_redir(word, d->len_word), NULL);
	}
	return (w);
}

char	*ft_methode_2(char *new_word, char *word, t_dollar *d)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	new_word = malloc(sizeof(char) * (d->len_word + 2));
	if (!new_word)
		return (NULL);
	ft_bzero(new_word, d->len_word + 2);
	new_word[j] = '$';
	while (word[i])
	{
		new_word[j + 1] = word[i];
		i++;
		j++;
	}
	return (new_word);
}

char	*ft_methode_3(char *nw, char *word, t_dollar *d, t_data *x)
{
	char	*tmp;

	tmp = NULL;
	while (d->envcp)
	{
		tmp = ft_strjoin(word, "=");
		if (ft_strncmp(((t_words *)d->envcp->content)->word,
				tmp, d->len_word + 1) == 0)
			nw = ft_expand_found_3(d, nw, d->len_word);
		free(tmp);
		d->envcp = d->envcp->next;
	}
	if (d->comp == 0)
	{
		nw = malloc(sizeof(char) * 1 + 1);
		if (!nw)
			return (NULL);
		nw[0] = '\0';
		if (x->key == 2 && x->doc == 0)
		{
			x->flag_stop = 2;
			return (free(nw), ft_error_ambigous_redir(word, d->len_word), NULL);
		}
	}
	return (nw);
}

char	*ft_methode_4(char *new_word, char *word, t_dollar *d)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while ((word[i] >= 'a' && word[i] <= 'z')
		|| (word[i] >= '0' && word[i] <= '9')
		|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] == '_'))
		i++;
	d->tmp = malloc(sizeof(char) * (i + 1));
	if (!d->tmp)
		return (NULL);
	d->save = malloc(sizeof(char) * (d->len_word - i) + 1);
	if (!d->save)
		return (NULL);
	while (++k < i)
		d->tmp[k] = word[k];
	d->tmp[k] = '\0';
	while (i < d->len_word && word[i])
		d->save[j++] = word[i++];
	d->save[j] = '\0';
	new_word = ft_expand_4(new_word, d);
	return (new_word);
}

char	*ft_result(t_list **cpenv, int res, char *word, t_data *x)
{
	t_dollar	d;
	char		*new_word;

	ft_bzero(&d, sizeof(d));
	d.len_word = ft_strlen(word);
	d.envcp = *cpenv;
	new_word = NULL;
	if (res == 1)
		new_word = ft_methode_1(new_word, word, &d, x);
	else if (res == 2)
		new_word = ft_methode_2(new_word, word, &d);
	else if (res == 3)
		new_word = ft_methode_3(new_word, word, &d, x);
	else if (res == 4)
		new_word = ft_methode_4(new_word, word, &d);
	else if (res == 5)
		new_word = ft_itoa(g_status);
	else
		return (NULL);
	return (new_word);
}
