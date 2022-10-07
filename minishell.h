/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:03 by evsuits           #+#    #+#             */
/*   Updated: 2022/10/07 15:18:04 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

#define false 0
#define true 1

typedef struct s_letters{
	char		letter;
	int			token;
}	t_letters;

typedef struct s_words{
	char			*word;
	int				token;
}	t_words;

typedef struct s_list{
	void	*content;
	struct s_list *next;
}	t_list;

typedef struct s_btw_pipes{
	t_list *portion_words;
}	t_btw_pipes;


typedef struct s_cmdredir{
	t_list		*cmd;
	t_list		*redirection;
	int			fd_cmd[2];
}	t_cmdredir;

typedef struct s_cpenv{
	char	*one_env;
}	t_cpenv;

enum	e_env
{
	TOK_ENV = 28,
	TOK_EXP = 29,
};

enum	e_token
{
	TOK_PIPE,
	TOK_TO,
	TOK_FROM,
	TOK_WORD,
	TOK_TOTO,
	TOK_FRFR,
	TOK_DOLL,
	TOK_QUOT,
	TOK_SPAC = 10,
};

typedef struct s_data{
	////////////ENV
	int		len_after_doll;
	int		len_one_env;
	int		i_doll;
	int		d1;
	int		d2;
	char	**env;
	//////////////////
	t_list **cpenv;
	int		is_env;
	char	*path_constructor;
	char	**tab_option;
	char	**co;
	/////////////////////
	char	**option;
	char	*pc;
	int		file;
	int		fd_pipe[2];
	int		nb_pipe;
	/////////////////////
	int		key;
	char	*line;
	int		i_gl;
	int		len_opt;
	char	*banana;
	int		i_len;
	int		n_option;
	int		i_e;
}	t_data;

typedef struct s_dollar{
	int		j4;
	char	*save;
	char	*tmp;
	int		len_env;
	int		len_word;
	int		comp;
	t_list	*envcp;
}	t_dollar;

typedef struct s_echo{
	char	*str;
	int		n_option;
	int		i;
	int		shot;
	int		has_written;
}	t_echo;

enum	e_quote_state
{
	DEFAULT_STATE = 25,
	S_QUOTE_STATE = 26,
	D_QUOTE_STATE = 27,
};

//main.c
int			sizeof_string_tab(char **str);

////////////////////////////////////////////////////////////////////////////////////////////////////LEXER
int			pre_lexeur(char *line, t_list **letters);
void		group_letters(t_list	**lst_letters, t_list **lst_words);
t_words		*words_init(char *word, int token);
void		syntax_error(t_list *tmp, int i);
int			token_validity(t_list **lst_words);
int			token_order(t_list **lst_words);


////////////////////////////////////////////////////////////////////////////////////////////////////PARSER

//////////DOLLAR//////////
void	final_doll(t_list **segment, t_list **envcp, t_list **after_doll, t_data *x);
t_cmdredir *init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x);
t_list	**ft_expand_cmd(t_list **segment, t_list **envcp, t_data *x);
t_list	**ft_expand_redir(t_list **segment, t_list **envcp, t_data *x);
int	ft_check_after_doll(char *word);

//////////EXPAND//////////
 char	*ft_result(t_list **envcp, int res, char *word, t_data *x);
// char	*ft_if_4(char *new_word, t_list **envcp, int len, int len_one_env, char *tmp_4, char *reste_4, int j4);
// char	*ft_if_if_4(int j4, char *reste_4, char *new_word, char *tmp_4, char *nul_4);
// char	*ft_if_3(char *new_word, int i, t_list **envcp, int len_one_env, int len, char *word, t_data *x);
// char	*ft_if_2(char *new_word, int i, char *word, int h2);
// char	*ft_if_1(char *new_word, int i, char *word, int h1);

//////////PARSER//////////
void		sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
t_list		*ft_sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
int			ft_nb_pipes(t_list **lst_words);
t_words		*ft_add_redir(t_words *a_list, t_words *value);
void		ft_sep_cmd_redir(t_list **btw_pipes, t_list **future);
t_cmdredir	*cmdredir_init(t_list *portion);
t_list		**ft_dupredir(t_list *portion);
t_list		**ft_dupcmd(t_list *portion);
void		ft_error_ambigous_redirect(char *word, int len);

//////////COMMAND & PATH ABSOLUTE//////////
int			ft_is_null(char *cmd);
int			ft_is_space(char *cmd);
void		ft_error_command_not_found(char *cmd);
char		*ft_join_options(t_list **cmd, t_data *x);
void		ft_cmd_and_env(t_data *x, char *co, char *opt, t_list **cpenv);
int			ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv);
char		**ft_get_ultime_cmd(char *co, char *opt, char *pc);
char		*ft_path_construction(char *co, t_data *x, t_list **cpenv);
char		*ft_construction_absolute_path_pc(char **path_env, char **option);
char		**ft_get_path_in_env(t_data *x, t_list **cpenv);

//////////ENVIRONNEMENT//////////
void		final_doll(t_list **segment, t_list **envcp, t_list **after_doll, t_data *x);
t_cmdredir 	*init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x);
t_list		**ft_expand(t_list **words, t_list **envcp, t_data *x);
void		ft_dup_env(char **env, t_list **cpenv, t_data *x);
int			ft_check_after_doll(char *word);
void		ft_dup_env(char **env, t_list **cpenv, t_data *x);
t_words 	*ft_init_cpenv(char *one_env, int token);
t_cpenv 	*ft_init_cpenv_kezako(char *one_env);

//////////CHECK FILES AN REDIRECTION//////////
void		ft_catch_file(t_list **after_doll, t_data *x, t_list **envcp);
int			ft_read_outfile(char *outfile);
int			ft_read_infile(char *infile);

//////////////////////////////////////////////////////////////////////////////////////////////////////////UTILS

//////////LIBFT & UTILS//////////
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_strcmp(const char *s1, const char *s2);

//////////LINKED LISTS//////////
void		ft_lstadd_back(t_list **alst, t_list *new);
void		**ft_lstadd_back2(t_list **alst, t_list *new);
t_list		*ft_lstnew(void * content);
t_btw_pipes	*ft_add_back(t_btw_pipes *a_list, t_words **words);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list **lst);

//////////FREE AND CLEAR//////////
void		ft_lst_clear(t_list **lst, void (*del)(void *));
void		ft_free_letters(void *content);
void		ft_free_words(void *content);
void		ft_free_btw_pipes(void *content);
void		ft_lst_clear_cmd_dir(t_list **lst, void (*del)(void *));
void		ft_lstclear_cpenv(t_list **liste);
void		ft_free_cmd_redir(void *content);
void		ft_free_cpenv(void *content);
void		ft_free_array(char **array);
char		*ft_strndup(char const *s, int word_size);

//////////VISUAlIZE FUNCTIONS//////////
void		ft_visualize_btw_pipes(t_list **lst_btw_pipes);
void		ft_visualize_cmd_redir(t_list **list);
void		visualize_string_tab(char **str);
void		visualize_t_words(t_list **lst_words);

//////////ERROR FUNCTIONS//////////
void		ft_error_command_not_found(char *cmd);
int			ft_exist_error(char *infile);
int			ft_exist_error_directory(char *infile);
int			ft_perm_error(char *file);
int			ft_is_null(char *cmd);
int			ft_is_space(char *cmd);

/////////////////////////////////////////////////////////////////////////////////////////////////////EXECUTION

//////////EXECUTION//////////
void		ft_organize_execution(t_data *x, t_list **after_doll, t_list **cpenv);
void		ft_execution_nopipe(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_processus_nopipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv);
void		ft_execution_organisation(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x, int nb_cmd);
void		ft_processus_pipe_1(t_list *tmp, t_data *x, t_list **cpenv);
void		ft_processus_pipe_2(t_list *tmp, t_data *x, t_list **cpenv);
void		ft_processus_pipe_3(t_list *tmp, t_data *x, t_list **cpenv);
void		ft_catch_file_tekflemme(t_list **after_doll, t_data *x);

//////////////////////////////////////////////////////////////////////////////////////////////////////BUILTINS

int			ft_is_builtin(t_list **cmd, t_data *x, t_list **cpenv);
//void			ft_echo_n_option(t_list *cmd, char *str, int i, int n_option);

//export.c
void		ft_export_solo(t_list **cpenv);
void		ft_write_exp(t_list **exp);
void		ft_export_error(char *cmdnext);

//export_utils.c
int			check_if_equal(char *cmd);
int			check_if_first_alpha(char *cmdnext);
int			check_if_alphanum(char *cmdnext);
void		ft_insert(t_list *new, t_list *tmp);

//export_case.c
void		call_case(int index_eq, t_words *content, t_list **cpenv);
void		case_no_eq(char *cmd, t_list **cpenv);
void		case_eq(int index_eq, char *cmd, t_list **cpenv);
void		case_pl_eq(int index_eq, char *cmd, t_list **cpenv);

//unset.c
int			ft_unset_others(t_list *tmp, char *before_eq);
int			ft_unset_first(t_list *tmp, char *before_eq);

typedef struct s_builtin_value	t_builtin_value;
typedef int						(*t_fct)(t_list *cmd, t_list **cpenv);

struct s_builtin_value
{
	char const			*builtin_name;
	t_fct const			fonction;
};

int		ft_fonction(t_list *cmd, t_list **cpenv);//, t_data *x);
int		ft_pwd(t_list *cmd, t_list **cpenv);//, t_data *x);
//int		ft_export(t_list *cmdnext, t_list **cpenv);
int		ft_echo(t_list *cmd, t_list **cpenv);//, t_data *x);
int		ft_cd(t_list *cmd, t_list **cpenv);

static t_builtin_value	const g_lookup[] = {
	{"cd", ft_cd},
	{"echo",ft_echo},
	{"pwd", ft_pwd},
	{"export", ft_fonction},
	{"unset", ft_fonction},
	{"exit", ft_fonction},
	{"env", ft_fonction},
	{0},
};

#endif
