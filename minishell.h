/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:03 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/01 19:14:12 by jecolmou         ###   ########.fr       */
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
# include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

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
	pid_t		process_id;
	int			fd_cmd[2];
}	t_cmdredir;

enum	e_builtin
{
	ECHO,
	PWD,
};

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

typedef struct s_dollar{
	int		j4;
	char	*save;
	char	*tmp;
	int		len_env;
	int		len_word;
	int		comp;
	t_list	*envcp;
}	t_dollar;

typedef struct s_data{
	////////////ENV
	int		len_after_doll;
	int		len_word;
	int		i_doll;
	int		d1;
	int		d2;
	char	**env;
	//////////////////
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
	int		outfile;
	int		infile;
	int		here_infile;
	int		append_outfile;
	int		flag_redir;
	char	*hered;
	bool	interupt;
	int		flag_heredoc;
	int		flag_executable;
	t_dollar	*d;
	int		flag_ambi;
	char	*word_ambi;
	int		redir_key;
	int		flag_stop;
	int		flag_no_pipe_no_cmd_ok_redir;
	int		nb_cmd;
	////////////////////////
	t_list	*letters;
	t_list	*words;
	t_list	*btw_pipes;
	t_list	*segment;
	t_list	*cpenv;

}	t_data;

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

enum	e_quote
{
	DEF = 120,
	AF_SPAC = 121,
};

//main.c
int			sizeof_string_tab(char **str);
void		handle_sig_child(int sig);
void		handle_sig_parent(int sig);

//lexeur.c
int			pre_lexeur(t_data *x, char *line, t_list **letters);

//lexeur_lexical.c
void		group_letters(t_list	**lst_letters, t_list **lst_words);
t_words 	*words_init(char *word, int token);

//lexeur_lexical_utils.c
int			len_group_letters(t_list **tmp);
char		*build_word(int len, t_list **tmp);

//lexeur_grammatical.c
void		syntax_error(t_list *tmp, int i);
int			token_validity(t_list **lst_words);
int			token_order(t_list **lst_words);
int			check_redir(t_list *lst);

//del.c
char		*ft_expand_one_btw_del(t_list **tmp, t_list **env, t_data *x);
char		*until_next_del(t_list *tmp, t_list *end, t_list **env, t_data *x);
t_list		*find_end_del(t_list *af_quot);

//new_expand.c
void		new_expand(t_list **lst_words, t_list **env, t_data *x);
int			check_del(t_list *tmp);


//lim_spac.c
void		ft_delete_space(t_list **lst_words);
void		ft_lim_protection(t_list **lst_words);

//////////DOLLAR//////////
void		final_doll(t_list **segment, t_list **envcp, t_list **after_doll, t_data *x);
t_cmdredir	*init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x);
t_list		**ft_expand_cmd(t_list **segment, t_list **envcp, t_data *x);
t_list		**ft_expand_redir(t_list **segment, t_list **envcp, t_data *x);
int			ft_check_after_doll(char *word);

//////////EXPAND//////////
char		*ft_result(t_list **envcp, int res, char *word, t_data *x);

//////////LINKED LISTS//////////
void		ft_lstadd_back(t_list **alst, t_list *new);
void		**ft_lstadd_back2(t_list **alst, t_list *new);
t_list		*ft_lstnew(void * content);
t_btw_pipes	*ft_add_back(t_btw_pipes *a_list, t_words **words);
void    	ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list **tmp);

//////////PARSER//////////
void		sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
t_list		*ft_sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
int			ft_nb_pipes(t_list **lst_words);
t_words		*ft_add_redir(t_words *a_list, t_words *value);
void		ft_sep_cmd_redir(t_list **btw_pipes, t_list **future);
t_cmdredir	*cmdredir_init(t_list *portion);
t_list		**ft_dupredir(t_list *portion);
t_list		**ft_dupcmd(t_list *portion);
int			ft_error_ambigous_redirect(char *word, int len);
int			ft_error_nsfod(char *infile);
void		ft_check_ambi(t_list **tmp, t_data *x);

//////////COMMAND & PATH ABSOLUTE//////////
//cmd_constructor.c
int			ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv);
int			ft_cmd_and_env(t_data *x, t_list **cmd, t_list **cpenv);
char		*ft_no_env_access_return(t_list **cmd, t_data *x);

//get_path.c
char		**ft_get_ultime_cmd(t_list **cmd, t_data *x, char *pc);
char		*ft_path_construction(t_list **cmd, t_data *x, t_list **cpenv);//ft_path_command
char		*ft_construction_absolute_path_pc(char **path_env, char **option);
char		**ft_get_path_in_env(t_data *x, t_list **cpenv);


int			ft_is_null(char *cmd);
int			ft_is_space(char *cmd);
void		ft_error_command_not_found(char *cmd);
char		*ft_join_options(t_list **cmd, t_data *x);

//////////ENVIRONNEMENT//////////
void		final_doll(t_list **segment, t_list **envcp, t_list **after_doll, t_data *x);
t_cmdredir 	*init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x);
t_list		**ft_expand(t_list **words, t_list **envcp, t_data *x);
void		ft_dup_env(char **env, t_list **cpenv, t_data *x);
int			ft_check_after_doll(char *word);
void		ft_dup_env(char **env, t_list **cpenv, t_data *x);
t_words 	*ft_init_words(char *word, int token);
t_words 	*ft_init_words_kezako(char *word);

//////////EXECUTION//////////
//execution_no_pipe.c
void	ft_execution_no_pipe_annexe(t_list **cmdredir, t_data *x, t_list **cpenv);


void		ft_organize_execution(t_data *x, t_list **after_doll, t_list **cpenv);
void		ft_execution_no_pipe(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_processus_no_pipe(t_list **cmd, t_list **redir, t_data *x, t_list **cpenv);
void		ft_execution_organisation(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x, int nb_cmd);
void		ft_processus_pipe(t_list **tmpafterd, t_data *x, t_list **cpenv);
// void		ft_catch_file_tekflemme(t_list **after_doll, t_data *x);
void		ft_catch_file_tekinfile(t_list **after_doll, t_list *redir, t_data *x);
void		ft_catch_file_tekoutfile(t_list **after_doll, t_list *redir, t_data *x);
int			ft_is_builtin(t_list **tmp, t_data *x, t_list**cpenv);


//execution_utils.c
int			ft_nb_cmd(t_list **lst);
void		ft_set_fdcmd(t_list **after_doll, t_data *x);

//redirection_no_pipe.c
void		ft_no_pipe_redirection_in(t_list **redir, t_data *x);
void		ft_no_pipe_redirection_out(t_list **redir, t_data *x);
void		ft_annexe_in_out(t_list **list, t_data *x);
int			ft_is_redirection_in(t_list **list);
int			ft_is_redirection_out(t_list **list);

//redirection_pipe.c
void		ft_pipe_redirection_out(t_list **after_doll, t_list *redir, t_data *x);
void		ft_pipe_redirection_in(t_list **after_doll, t_list *redir, t_data *x, t_list **cpenv);


int			ft_waitpid(t_list **after_doll, t_data *x);
char		**get_env(t_list *cpenv);

//////////CHECK FILES AN REDIRECTION//////////
void		ft_catch_file(t_list **after_doll, t_data *x, t_list **envcp);
void		ft_heredoc(t_list **tmp, t_data *x, t_list **cpenv);
int			ft_read_infile_heredoc(t_list **tmp, char *lim, char *line, t_list **cpenv, t_data *x);
char		*ft_expand_heredoc(char *line, t_list **cpenv, int res, t_data *x);
int			ft_exist_error(char *infile, t_data *x);
int			ft_exist_error_directory(char *infile, t_data *x);
int			ft_perm_error(char *file, t_data *x);
int			ft_read_infile(char *infile, t_data *x);
int			ft_read_outfile_append(char *outfile, t_data *x);
int			ft_read_outfile(char *outfile, t_data *x);
void		ft_close(int fd);
int			ft_is_exe(t_list **tmp, t_data *x, t_list **cpenv);
char		*ft_is_executable(t_list **tmp, t_data *x, t_list **cpenv);
char		*ft_transform_executable(char *executable);

//////////LIBFT//////////XXXXXXXXXXXXXXXXXXXXXXXXXXX
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
char		*ft_itoa(int n);
//////////FREE AND CLEAR//////////
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_free_letters(void *content);
void		ft_free_words(void *content);
void		ft_free_btw_pipes(void *content);
void		ft_lstclear_cmd_dir(t_list **lst, void (*del)(void *));
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

//export.c
void		ft_export_solo(t_list **cpenv);
void		ft_write_exp(t_list **exp, t_list *cmdredir);
void		ft_export_error(char *cmdnext);

//export_utils.c
int			check_if_equal(char *cmd);
int			check_first_alpha(char *cmdnext);
int			check_alnum(char *cmdnext);
void		ft_insert(t_list *new, t_list *tmp);

//export_case.c
void		call_case(int index_eq, t_words *content, t_list **cpenv);
void		case_no_eq(char *cmd, t_list **cpenv);
void		case_eq(int index_eq, char *cmd, t_list **cpenv);
void		case_pl_eq(int index_eq, char *cmd, t_list **cpenv, int i);

//unset.c
int			ft_unset_others(t_list *tmp, char *before_eq);
int			ft_unset_first(t_list *tmp, char *before_eq);
int			ft_unset(t_list *cmd, t_list **cpenv, t_data *x);

//exit_utils.c
long long	ft_atoll(char *str);

typedef struct s_builtin_value	t_builtin_value;
typedef int						(*t_fct)(t_list *cmd, t_list **cpenv, t_data *x);

struct s_builtin_value
{
	char const			*builtin_name;
	t_fct const			fonction;
};

void	ft_exit_bis(char *str, t_data *x);

int			ft_exit(t_list *cmd, t_list **cpenv, t_data *x);
int			ft_export(t_list *cmdnext, t_list **cpenv, t_data *x);
int			ft_pwd(t_list *cmd, t_list **cpenv, t_data *x);
int			ft_echo(t_list *cmd, t_list **cpenv, t_data *x);
int			ft_cd(t_list *cmd, t_list **cpenv, t_data *x);
int			ft_fonction(t_list *cmd, t_list **cpenv, t_data *x);
int			ft_env(t_list *cmd, t_list **cpenv, t_data *x);

static t_builtin_value	const g_lookup[] = {
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"echo", ft_echo},
	{"unset", ft_unset},
	{"exit", ft_exit},
	{"env", ft_env},
	{0},
};
#endif
