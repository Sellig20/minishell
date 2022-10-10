/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:40:31 by jecolmou          #+#    #+#             */
/*   Updated: 2022/10/07 14:55:50 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_methode_1(char *new_word, char *word, t_dollar *d, t_data *x)
{
	dprintf(2, "METHODE 1 pour %s\n", word);
	int		i;
	int		j;

	j = 0;
	i = 1;
	new_word = malloc(sizeof(char) * (d->len_word + 1));
	ft_bzero(new_word, d->len_word + 1);
	while (word[i])
	{
		new_word[j] = word[i];
		j++;
		i++;
	}
	if (x->key == 2 && d->len_word == 1)
		ft_error_ambigous_redirect(word, d->len_word);
	return (new_word);
}

char	*ft_methode_2(char *new_word, char *word, t_dollar *d)
{
	dprintf(2, "METHODE 2 pour %s\n", word);
	int	i;
	int	j;

	j = 0;
	i = 0;
	new_word = malloc(sizeof(char) * (d->len_word + 2));
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

char	*ft_expand_found_3(t_dollar *d, char *new_word, int len)
{
	int		i;

	i = 0;
	d->len_env = ft_strlen((((t_cpenv *)d->envcp->content)->one_env)) - (len + 1);
	new_word = malloc(sizeof(char) * d->len_env + 1);
	while (((t_cpenv *)d->envcp->content)->one_env[len + 1 + i])
	{
		new_word[i] = ((t_cpenv *)d->envcp->content)->one_env[len + 1 + i];
		i++;
		d->comp = i;
	}
	new_word[i] = '\0';
	return (new_word);
}

char	*ft_methode_3(char *new_word, char *word, t_dollar *d, t_data *x)
{
	dprintf(2, "METHODE 3 pour %s\n", word);
	char	*tmp;
	int		j;
	int		i;

	tmp = NULL;
	j = 0;
	i = 0;
	while (d->envcp)
	{
		i = 0;
		tmp = ft_strjoin(word, "=");
		if (ft_strncmp(((t_cpenv *)d->envcp->content)->one_env, tmp, d->len_word + 1) == 0)
			new_word = ft_expand_found_3(d, new_word, d->len_word);
		free(tmp);
		d->envcp = d->envcp->next;
	}
	if (d->comp == 0)
	{
		new_word = malloc(sizeof(char) * 1 + 1);
		new_word[i] = '\0';
		if (x->key == 2)
			ft_error_ambigous_redirect(word, d->len_word);
	}
	return (new_word);
}

char	*ft_expand_not_found_4(t_dollar *d, char *new_word)
{
	int		j;
	char	*null;

	null = NULL;
	j = 0;
	null = malloc(sizeof(char) * 1 + 1);
	null[j] = '\0';
	new_word = ft_strjoin(null, d->save);
	free(d->save);
	free(null);
	free(d->tmp);
	return (new_word);
}

char	*ft_expand_found_4(t_dollar *d, char *new_word)
{
	int		j;

	j = 0;
	d->len_env = ft_strlen((((t_cpenv *)d->envcp->content)->one_env)) - (d->len_word + 1);
	new_word = malloc(sizeof(char) * d->len_env + 1);
	while (((t_cpenv *)d->envcp->content)->one_env[d->len_word + 1 + j])
	{
		new_word[j] = ((t_cpenv *)d->envcp->content)->one_env[d->len_word + 1 + j];
		j++;
		d->comp = j;
	}
	new_word[j] = '\0';
	return (new_word);
}

char	*ft_expand_4(char *new_word, t_dollar *d)
{
	char	*tmp;
	d->comp = 0;

	while (d->envcp)
	{
		d->len_word = ft_strlen(d->tmp);
		tmp = ft_strjoin(d->tmp, "=");
		if (ft_strncmp(((t_cpenv *)d->envcp->content)->one_env, tmp, d->len_word + 1) == 0)
			new_word = ft_expand_found_4(d, new_word);
		free(tmp);
		d->envcp = d->envcp->next;
	}
	if (d->comp == 0)
	{
		new_word = ft_expand_not_found_4(d, new_word);
		return (new_word);
	}
	new_word = ft_strjoin(new_word, d->save);
	free(d->save);
	free(d->tmp);
	return (new_word);
}

char	*ft_methode_4(char *new_word, char *word, t_dollar *d)
{
	dprintf(2, "METHODE 4 pour %s\n", word);
	int		i;
	int		j;
	int		k;
	i = 0;
	j = 0;
	k = -1;
	while ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9')
		|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] == '_'))
		i++;
	d->tmp = malloc(sizeof(char) * (i + 1));
	d->save = malloc(sizeof(char) * (d->len_word - i) + 1);
	while (++k < i)
		d->tmp[k] = word[k];
	d->tmp[k]  = '\0';
	while (i < d->len_word && word[i])
	{
		d->save[j] = word[i];
		i++;
		j++;
	}
	d->save[j] = '\0';
	new_word = ft_expand_4(new_word, d);
	return (new_word);
}

char	*ft_result(t_list **cpenv, int res, char *word, t_data *x)
{
	t_dollar	d;
	char		*new_word;
	int			i;

	ft_bzero(&d, sizeof(d));
	d.len_word = ft_strlen(word);
	d.envcp = *cpenv;
	new_word = NULL;
	i = 0;
	if (res == 1)
		new_word = ft_methode_1(new_word, word, &d, x);
	if (res == 2)
		new_word = ft_methode_2(new_word, word, &d);
	if (res == 3)
		new_word = ft_methode_3(new_word, word, &d, x);
	if (res == 4)
		new_word = ft_methode_4(new_word, word, &d);
	return (new_word);
}

