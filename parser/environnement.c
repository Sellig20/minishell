/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:23 by jecolmou          #+#    #+#             */
/*   Updated: 2022/09/28 10:33:55 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cpenv *ft_init_cpenv_kezako(char *one_env)
{
	t_cpenv *new_cp_env;

	new_cp_env = malloc(sizeof(t_cpenv));
	if (!new_cp_env)
		return (NULL);
	new_cp_env->one_env = ft_strdup(one_env);
	return (new_cp_env);
}

t_words *ft_init_cpenv(char *one_env, int token)
{
	t_words *new_cp_env;
	(void)token;
	(void)one_env;

	new_cp_env = malloc(sizeof(t_words));
	// if (!new_cp_env)
	// 	return (NULL);
	// new_cp_env->one_env = ft_strdup(one_env);
	return (new_cp_env);
}

void	ft_dup_env(char **env, t_list **cpenv, t_data *x)
{
	int	e;
	t_list *new;

	e = 0;
	new = NULL;
	*cpenv = NULL;
	(void)x;
	while (env[e])
	{
		new = ft_lstnew((void *) ft_init_cpenv_kezako(env[e]));
		cpenv = (t_list **)ft_lstadd_back2(cpenv, new);
		e++;
	}
}


int	ft_check_after_doll(char *word)
{
	int	i;

	i = 0;
	if (word[i] >= '0' && word[i] <= '9')
		return (1);
	else if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9')
	|| (word[i] >= 'A' && word[i] <= 'Z')))
		return (2);
	while (word[i])
	{
		if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9')
		|| (word[i] >= 'A' && word[i] <= 'Z')))
			return (4);
		i++;
	}
	return (3);
}

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = s;
	while (n > 0)
	{
		str[i] = 0;
		i++;
		n--;
	}
}

char	*ft_if_1(char *new_word, int i, char *word, int h1)
{
	while (word[i])
	{
		new_word[h1] = word[i];
		h1++;
		i++;
	}
	return (new_word);
}

char	*ft_if_2(char *new_word, int i, char *word, int h2)
{
	new_word[h2] = '$';
	while (word[i])
	{
		new_word[h2 + 1] = word[i];
		i++;
		h2++;
	}
	return (new_word);
}

void	ft_error_ambigous_redirect(char *word, int len)
{
	ft_putstr_fd("Minimichel: $", 2);
	write(2, word, len);
	ft_putstr_fd(": ambigous redirect\n", 2);
}

char	*ft_if_3(char *new_word, int i, t_list **envcp, int len_one_env, int len, char *word, t_data *x)
{
	t_list *tmp_envcp;
	char	*tmp;
	int	j;

	//////key = 1 cmd$ | key = 2 redir$
	j = 0;
	tmp_envcp = *envcp;
	(void)x;
	tmp = NULL;
	while (tmp_envcp)
	{
		i = 0;
		tmp = ft_strjoin(word, "=");
		if (ft_strncmp(((t_cpenv *)tmp_envcp->content)->one_env, tmp, len + 1) == 0)
		{
			len_one_env = ft_strlen((((t_cpenv *)tmp_envcp->content)->one_env)) - (len + 1);
			new_word = malloc(sizeof(char) * len_one_env + 1);
			while (((t_cpenv *)tmp_envcp->content)->one_env[len + 1 + i])
			{
				new_word[i] = ((t_cpenv *)tmp_envcp->content)->one_env[len + 1 + i];
				i++;
				j = i;
			}
			new_word[i] = '\0';
		}
		free(tmp);
		tmp_envcp = tmp_envcp->next;
	}
	if (j == 0)
	{
		new_word = malloc(sizeof(char) * 1 + 1);
		new_word[i] = '\0';
		if (x->key == 2)
			ft_error_ambigous_redirect(word, len);
	}
	return (new_word);
}

char	*ft_if_if_4(int j4, char *reste_4, char *new_word, char *tmp_4, char *nul_4)
{
	nul_4 = malloc(sizeof(char) * 1 + 1);
	nul_4[j4] = '\0';
	new_word = ft_strjoin(nul_4, reste_4);
	free(reste_4);
	free(nul_4);
	free(tmp_4);
	return (new_word);
}

char	*ft_if_4(char *new_word, t_list **envcp, int len, int len_one_env, char *tmp_4, char *reste_4, char *nul_4, int j4)
{
	t_list *tmp_envcp;
	char	*tmp;
	int		comp;

	comp = 0;
	tmp_envcp = *envcp;
	while (tmp_envcp)
	{
		j4 = 0;
		len = ft_strlen(tmp_4);
		tmp = ft_strjoin(tmp_4, "=");
		if (ft_strncmp(((t_cpenv *)tmp_envcp->content)->one_env, tmp, len + 1) == 0)
		{
			len_one_env = ft_strlen((((t_cpenv *)tmp_envcp->content)->one_env)) - (len + 1);
			new_word = malloc(sizeof(char) * len_one_env + 1);
			while (((t_cpenv *)tmp_envcp->content)->one_env[len + 1 + j4])
			{
				new_word[j4] = ((t_cpenv *)tmp_envcp->content)->one_env[len + 1 + j4];
				j4++;
				comp = j4;
			}
			new_word[j4] = '\0';
		}
		free(tmp);
		tmp_envcp = tmp_envcp->next;
	}
	if (comp == 0)
	{
		new_word = ft_if_if_4(j4, reste_4, new_word, tmp_4, nul_4);
		return (new_word);
	}
	new_word = ft_strjoin(new_word, reste_4);
	free(reste_4);
	free(tmp_4);
	return (new_word);
}

char	*ft_res(t_list **envcp, int res, char *word, t_data *x)
{
	t_list *tmp_envcp;
	char *new_word;
	char *tmp_4;
	char *reste_4;
	char *nul_4;
	int	i;
	int j4;
	int	h;
	int	len;
	int	len_one_env;
	(void)x;

	len = ft_strlen(word);
	tmp_envcp = *envcp;
	len_one_env = 0;
	tmp_4 = 0;
	j4 = 0;
	reste_4 = 0;
	h = 0;
	int h1 = 0;
	int h2 = 0;
	nul_4 = 0;
	if (res == 1)
	{
		printf("METHODE 1 pour %s\n", word);
		i = 1;
		new_word = malloc(sizeof(char) * (len + 1));
		ft_bzero(new_word, len + 1);
		new_word = ft_if_1(new_word, i, word, h1);
		if (x->key == 2 && len == 1)
			ft_error_ambigous_redirect(word, len);
	}
	if (res == 2)
	{
		printf("METHODE 2 pour %s\n", word);
		i = 0;
		new_word = malloc(sizeof(char) * (len + 2));
		ft_bzero(new_word, len + 2);
		new_word = ft_if_2(new_word, i, word, h2);
	}
	if (res == 3)
	{
		printf("METHODE 3 pour %s\n", word);
		new_word = ft_if_3(new_word, i, &tmp_envcp, len_one_env, len, word, x);
	}
	if (res == 4)
	{
		printf("METHODE 4 pour %s\n", word);
		i = 0;
		j4 = 0;
		while ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9')
			|| (word[i] >= 'A' && word[i] <= 'Z') || (word[i] == '_'))
			i++;
		tmp_4 = malloc(sizeof(char) * (i + 1));
		reste_4 = malloc(sizeof(char) * (len - i) + 1);
		while (j4 < i)
		{
			tmp_4[j4] = word[j4];
			j4++;
		}
		tmp_4[j4]  = '\0';
		while (i < len && word[i])
		{
			reste_4[h] = word[i];
			i++;
			h++;
		}
		reste_4[h] = '\0';
		new_word = ft_if_4(new_word, &tmp_envcp, len, len_one_env, tmp_4, reste_4, nul_4, j4);
	}
	return (new_word);
}

t_list	**ft_expand_redir(t_list **segment, t_list **envcp, t_data *x)
{
	t_list *tmp_seg;
	t_list *maill_malloc_echo;
	int		res;
	char	*new_echo;
	t_list *new_maill = NULL;
	t_list *tentativeredir;
	t_list **remplirredir;

	x->key = 2;
	remplirredir = malloc(sizeof(t_list*));
	if (!remplirredir)
		return (NULL);
	*remplirredir = NULL;
	tmp_seg = *segment;
	res = 0;
	tentativeredir = (t_list *)((t_cmdredir*)tmp_seg->content)->redirection;
	if (tentativeredir->content == NULL)
	{
		(*remplirredir) = ft_lstnew(NULL);
		return (remplirredir);
	}
	while (tentativeredir)
	{
		if ( ((t_words *)tentativeredir->content)->token == TOK_DOLL && tentativeredir->next) //creer le rsultat si tok dollar
		{
			res = ft_check_after_doll(((t_words *)tentativeredir->next->content)->word);
			new_echo = ft_res(envcp, res, ((t_words *)tentativeredir->next->content)->word, x);
			new_maill = ft_lstnew((void *) words_init(new_echo, TOK_WORD));
			free(new_echo);
			remplirredir = (t_list **)ft_lstadd_back2(remplirredir, new_maill);
			return (remplirredir);
		}
		else
		{
			maill_malloc_echo = ft_lstnew((void *) words_init(((t_words *)tentativeredir->content)->word, ((t_words *)tentativeredir->content)->token)); // sinon renvoyer
			remplirredir = (t_list **)ft_lstadd_back2(remplirredir, maill_malloc_echo);
		}
		tentativeredir = tentativeredir->next;
	}
	if (!(*remplirredir))
		(*remplirredir) = ft_lstnew(NULL);
	return (remplirredir);
}

t_list	**ft_expand_cmd(t_list **segment, t_list **envcp, t_data *x)
{
	t_list *tmp_seg;
	t_list *maill_malloc_echo;
	int		res;
	char	*new_echo;
	t_list *new_maill = NULL;
	t_list *tentativecmd;
	t_list **remplircmd;

	x->key = 1;
	remplircmd = malloc(sizeof(t_list*));
	if (!remplircmd)
		return (NULL);
	*remplircmd = NULL;
	new_echo = NULL;
	tmp_seg = *segment;
	res = 0;
	tentativecmd = (t_list *)((t_cmdredir*)tmp_seg->content)->cmd;
	if (tentativecmd->content == NULL)
	{
		(*remplircmd) = ft_lstnew(NULL);
		return (remplircmd);
	}
	while (tentativecmd)
	{
		if ( ((t_words *)tentativecmd->content)->token == TOK_DOLL && tentativecmd->next) //creer le rsultat si tok dollar
		{
			res = ft_check_after_doll(((t_words *)tentativecmd->next->content)->word);
			new_echo = ft_res(envcp, res, ((t_words *)tentativecmd->next->content)->word, x);
			new_maill = ft_lstnew((void *) words_init(new_echo, TOK_WORD));
			free(new_echo);
			remplircmd = (t_list **)ft_lstadd_back2(remplircmd, new_maill);
			return (remplircmd);
		}
		else
		{
			maill_malloc_echo = ft_lstnew((void *) words_init(((t_words *)tentativecmd->content)->word, TOK_WORD)); // sinon renvoyer
			remplircmd = (t_list **)ft_lstadd_back2(remplircmd, maill_malloc_echo);
		}
		tentativecmd = tentativecmd->next;
	}
	if (!(*remplircmd))
		(*remplircmd) = ft_lstnew(NULL);
	return (remplircmd);
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
