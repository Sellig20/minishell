/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:03 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/16 16:27:06 by jecolmou         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# define FALSE 0
# define TRUE 1

typedef struct s_letters{
	char		letter;
	int			token;
}	t_letters;

typedef struct s_words{
	char			*word;
	int				token;
}	t_words;

typedef struct s_list{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_btw_pipes{
	t_list	*portion_words;
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
	TOK_FILE,
	TOK_OTHER_SPAC,
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
	t_list	*letters;
	t_list	*words;
	t_list	*btw_pipes;
	t_list	**segment;
	t_list	*cpenv;
	t_list	**let;
	t_list	**wo;
	t_list	**bp;
	t_list	**seg;
	t_list	**cpv;
	char	**option;
	char	*pc;
	int		fd_pipe[2];
	int		key;
	char	*line;
	int		nb_pipe;
	int		outfile;
	int		infile;
	int		here_infile;
	int		append_outfile;
	int		flag_redir_builtin;
	char	*hered;
	int		doc;
	int		flag_exua;
	int		redir_key;
	int		flag_stop;
	int		flag_no_pipe_no_cmd_ok_redir;
	int		nb_cmd;
	int		i_ex;
	int		finish;
	int		res_echo;
	int		only_n;
	int		bad_friend;
	int		has_writ;
	int		echo_opt;
	int		count_files;
	int		builtin;
	int		bretzel;
	int		cdi;
	int		cdj;
	int		cdk;
	int		flag_ambi;
	int		is_retrieve;
	int		file;
	int		check;
	int		check_to;
	int		checkbis;
	int		checkter;
	int		echo;
	int		flag_uxu;
	int		dot_n_zero;
	int		first_is_dot;
	int		isalpha;
	int		dot_space;
	int		flag_file_down;
	int		is_pi;
}	t_data;

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

/////////////////////////LEXER////////////////////////////
//lexeur.c
int			pre_lexeur(t_data *x, char *line, t_list **letters);

//lexeur_lexical.c
void		group_letters(t_list	**lst_letters, t_list **lst_words);
t_words		*words_init(char *word, int token);

//lexeur_lexical_utils.c
int			len_group_letters(t_list **tmp);
char		*build_word(int len, t_list **tmp);
char		*build_quot(t_list **tmp);

//lexeur_grammatical.c
void		syntax_error(t_list *tmp, int i);
int			token_validity(t_list **lst_words);
int			token_order(t_list **lst_words);
int			check_redir(t_list *lst);

//del.c
char		*ft_expand_one_btw_del(t_list **tmp, t_list **env, t_data *x);
char		**until_next_del(t_list *tmp, t_list *end, t_list **env, t_data *x);
t_list		*find_end_del(t_list *af_quot);

//del_bis.c
void		protect_space(char *word, int sign);
void		unprotect_space(char **words);
int			get_last_index(char **btw);
char		**append_last_word(t_list *tmp, char **btw_del);
void		quotes(t_data *x, t_list *tmp);

//dollar.c
char		*ft_expand_one_btw_quot(t_list **tmp, t_list **envcp, t_data *x);
void		append_doll(char *word, char **btw, int ok);
void		add_doll(char *word, char **btw);

//new_expand.c
void		new_expand(t_list **lst_words, t_list **env, t_data *x);

//new_expand_utils.c
t_list		*other_word_annexe(char *word, t_data *x);
t_list		*put_new(t_data *x, char *word);
void		insert_words(char **words, t_list **tmp, t_data *x);
char		*put_null(char *word, t_data *x);

//new_expand_utils.c
int			get_len_words(t_list *tmp, t_list *end);
void		ft_free_w(char **words);
void		put_words(char **words, t_list **tmp);

//lim_spac.c
int			ft_delete_space(t_list **lst_words);
void		ft_lim_protection(t_list **lst_words);

//checks.c
int			check_redir(t_list *tmp);
int			check_after_redir(t_list **tmp);
int			check_pipes(t_list *tmp);
int			check_del(t_list *tmp);

////////////////////////PARSER////////////////////////////////////
//expand.c
char		*ft_result(t_list **envcp, int res, char *word, t_data *x);
char		*ft_methode_1(char *new_word, char *word, t_dollar *d, t_data *x);
char		*ft_methode_2(char *new_word, char *word, t_dollar *d);
char		*ft_methode_3(char *new_word, char *word, t_dollar *d, t_data *x);
char		*ft_methode_4(char *new_word, char *word, t_dollar *d);

//expand_annexe.c
int			ft_check_after_d(char *word);
char		*ft_expand_found_3(t_dollar *d, char *new_word, int len);
char		*ft_expand_not_found_4(t_dollar *d, char *new_word);
char		*ft_expand_found_4(t_dollar *d, char *new_word);
char		*ft_expand_4(char *new_word, t_dollar *d);

//expand_utils.c
char		*ft_new_word_4(char *new_word, t_dollar *d);

//sep_cmd.c
int			ft_check_not_cmd(t_list *portion);
int			ft_check_dollar_followed(t_list *portion);
int			ft_check_dollar(t_list *portion);
int			ft_check_cmd_followed(t_list *portion);
int			ft_sort_cmd(t_list *portion);

//parser_cmd_redir.c
t_list		**ft_dupcmd(t_list *portion);
t_list		**ft_dupredir(t_list *portion);
t_cmdredir	*cmdredir_init(t_list *portion);
void		ft_sep_cmd_redir(t_list **btw_pipes, t_list **future);
t_list		*ft_return_duped(t_list *portion, t_list *dup);
int			check_words(t_list *portion);

//cmd_constructor.c
int			ft_cmd_constructor(t_list **cmd, t_data *x, t_list **cpenv);
int			ft_cmd_and_env(t_data *x, t_list **cmd, t_list **cpenv);
char		*ft_no_env_access_return(t_list **cmd, t_data *x);

//cmd_constructor.c
char		*ft_no_env_access_return(t_list **cmd, t_data *x);
int			ft_is_slash(t_list **cmd);
void		ft_slash(t_list **cmd, t_data *x, t_list **cpenv);

//get_path.c
char		**ft_get_ultime_cmd(t_list **cmd, t_data *x, char *pc);
char		*ft_path_construction(t_list **cmd, t_data *x, t_list **cpenv);
char		*ft_construction_absolute_path_pc(char **path_env, char **option);
char		**ft_get_path_in_env(t_data *x, t_list **cpenv);

void		sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
t_list		*ft_sep_btw_pipes(t_list **lst_words, t_list **lst_btw_pipes);
int			ft_nb_pipes(t_list **lst_words);
t_words		*ft_add_redir(t_words *a_list, t_words *value);
void		ft_check_ambi(t_list **tmp, t_data *x);
int			ft_is_null(char *cmd);
int			ft_is_space(char *cmd);
char		*ft_join_options(t_list **cmd, t_data *x);
char		*ft_check_exec(char *str, t_data *x, t_list **cpenv, char *final);
char		*ft_get_executable(char	*final);

//heredoc_utils.c
int			init_list_heredoc(t_list ***letter, t_list ***words);
void		write_heredoc(t_list **words, int fd);
char		*heredoc_get_lim(t_list *letters, t_data *x);

/////////////////////////ERROR FUNCTIONS/////////////////////////
//open_error_files.c
int			ft_exist_error_directory(char *infile, t_data *x);
int			ft_error_nsfod(char *infile, t_data *x);
int			ft_perm_error(char *file, t_data *x, int nb, t_list **cpenv);
void		ft_isad_error(char *file, t_data *x, t_list **cpenv);

//error_functions.c
int			ft_error_ambigous_redir(char *word, int len);
void		ft_error_command_not_f(char *cmd);
int			check_if_not(char *executable);

/////////////////////CHECK FILES AN REDIRECTION//////////////////
void		ft_catch_file(t_list **after_doll, t_data *x, t_list **envcp);
void		ft_heredoc(t_list **tmp, t_data *x, t_list **cpenv);
int			ft_read_heredoc(char *lim, t_list **cpenv, t_data *x);
char		*ft_expand_heredoc(char *line, t_list **cpenv, int res, t_data *x);
int			ft_read_infile(char *infile, t_data *x);
int			ft_read_outfile_append(char *outfile, t_data *x);
int			ft_read_outfile(char *outfile, t_data *x);
void		ft_close(int fd);
int			ft_is_exe(t_list **tmp);
char		*ft_is_executable(t_list **tmp, t_data *x, t_list **cpenv);
char		*ft_transform_executable(char *executable);

///////////////////////////////ENVIRONNEMENT///////////////////////
void		final_doll(t_list **segment, t_list **envcp,
				t_list **after_doll, t_data *x);
t_cmdredir	*init_with_new_dollar(t_list **segment, t_list **envcp, t_data *x);
t_list		**ft_expand(t_list **words, t_list **envcp, t_data *x);
void		ft_dup_env(char **env, t_list **cpenv);
t_words		*ft_init_words(char *word, int token);
t_words		*ft_init_words_kezako(char *word);
char		**get_env(t_list *cpenv);

////////////////////////////////EXECUTION///////////////////////////
void		ft_exec_organisor(t_list **after_doll, t_list **cpenv, t_data *x);
int			ft_exec_no_pipe_bis(t_list **cmdredir, t_data *x, t_list **cpenv);

//execution_utils.c
int			ft_nb_cmd(t_list **lst);
void		ft_set_fdcmd(t_list **after_doll, t_data *x);
void		ft_loop_redirections_prot(t_list **redir, t_data *x);
void		ft_close_files(t_data *x);
void		ftclosep(t_data *x);

//execution_no_pipe.c
void		ft_exec_no_pipes(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_exec_no_pipe_annexe(t_list **cmdredir,
				t_data *x, t_list **cpenv);
void		ft_proc_no_pipe(t_list **cmd, t_list **redir,
				t_data *x, t_list **cpenv);
void		ft_no_pipe_no_cmd_redir(t_list **redir, t_data *x);
int			ft_no_pipe_is_executable(t_list **cmdredir,
				t_list **cpenv, t_data *x);

//execution_pipe.c
void		ft_execution_pipe(t_list **after_doll, t_list **cpenv, t_data *x);
void		ft_proc_pipe(t_list **tmpafterd, t_data *x, t_list **cpenv);
void		ft_create_pipe(t_list **cmdredir, t_data *x);

//execution_pipe_utils.c
int			ft_waitpid(t_list **after_doll, t_data *x);
void		ft_connector_redirections(t_list **cmdredir, t_data *x);
void		ft_connector_std_fdcmd(t_list **cmdredir);
int			ft_is_redirection_in(t_list **list);
int			ft_is_redirection_out(t_list **list);

//redirection_no_pipe.c
void		ft_no_pipe_redirection_in(t_list **redir, t_data *x);
void		ft_no_pipe_redirection_out(t_list **redir, t_data *x);
void		ft_annexe_out_no_pipe(t_list **list, t_data *x);

//redirection_pipe.c
void		ft_pipe_redirection_out(t_list **after_doll,
				t_list *redir, t_data *x);
void		ft_pipe_redirection_in(t_list **after_doll,
				t_list *redir, t_data *x);
void		ft_annexe_in_out_pipe(t_list **cmdredir, t_list **list, t_data *x);

//////////////////////////////LINKED LISTS//////////////////////////////
void		ft_lstadd_back(t_list **alst, t_list *neww);
void		**ft_lstadd_back2(t_list **alst, t_list *neww);
t_list		*ft_lstnew(void *content);
t_btw_pipes	*ft_add_back(t_btw_pipes *a_list, t_words **words);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list **tmp);

//////////////////////////////////LIBFT///////////////////////////////////
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
void		ft_lstadd_front(t_list **alst, t_list *neww);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);
void		*ft_calloc(size_t count, size_t size);
//////////////////////////////////FREE AND CLEAR///////////////////////////
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

////////////////////////////////////VISUAlIZE FUNCTIONS//////////////////////
void		visualize_t_letters(t_list **lst_letters);
void		visualize_t_words(t_list **lst_words);
void		ft_visualize_btw_pipes(t_list **lst_btw_pipes);
void		ft_visualize_cmd_redir(t_list **list);
void		visualize_string_tab(char **str);

//////////////////////////////////////MAIN/////////////////////////////////
void		handle_sig_child(int sig);
void		handle_sig_parent(int sig);
void		handle_sig_heredoc(int sig);
void		ft_reset_2x(t_data *x);
void		ft_reset_x(t_data *x, t_list *lst_letters,
				t_list *lst_words, t_list *lst_btw_pipes);
int			ft_born(t_list ***cpenv, char **av, char **env, t_data *x);
void		ft_died(t_list **let, t_list **wor, t_list **btw, t_list **seg);
int			init_list(t_list ***letters, t_list ***words,
				t_list ***btw_pipes, t_list ***segment);
void		call_no_pipe(t_list *cmd, t_list *redir, t_list **cpenv, t_data *x);

///////////////////////////////////////BUILTIN///////////////////////////////
int			ft_is_builtin(t_list **tmp, t_data *x, t_list**cpenv);
int			ft_is_is_builtin(char *word);

//export.c
void		ft_export_solo(t_list **cpenv);
void		ft_write_exp(t_list **exp, t_list *cmdredir, t_data *x);

//export_utils.c
int			check_if_equal(char *cmd);
int			check_first_alpha(char *cmdnext);
int			check_alnum(char *cmdnext);
void		ft_insert(t_list *neww, t_list *tmp);

//export_utils2.c
void		ft_export_error(char *cmdnext);
void		write_exp_two(char *content, t_list *cmdredir, t_data *x);
void		write_exp_one(char *before_eq, char *after_eq,
				t_list *cmdredir, t_data *x);

//export_case.c
void		call_case(int index_eq, t_words *content, t_list **cpenv);
void		case_no_eq(char *cmd, t_list **cpenv);
void		case_eq(int index_eq, char *cmd, t_list **cpenv);
void		case_pl_eq(int index_eq, char *cmd, t_list **cpenv, int i);

//unset.c
int			ft_unset_others(t_list *tmp, char *before_eq);
int			ft_unset_first(t_list **tmp, char *before_eq);
int			ft_unset(t_list *cmd, t_list **cpenv, t_data *x);

//exit_utils.c
long long	ft_atoll(char *str);

//echo.c
int			ft_echo(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_orga_n(t_list *cmdredir, char *str, t_data *x);
int			ft_strn(char *str, t_data *x);

//echo_utils.c
int			ft_strlenlen(char *str);
int			ft_echo_n_option_no(t_list *cmdredir, char *str, t_data *x);
int			ft_echo_n_opt(t_list *cmdredir, char *str, t_data *x);
int			ft_echo_not_n_only(t_list *cmdredir, char *str, t_data *x);
void		ft_print_echo(char *str, t_list *cmdredir, t_data *x);

//echo_utils2.c
t_list		*ft_echo_quotes(t_list *cmdredir, t_list *cmd, t_data *x);
t_list		*ft_move_echo(t_list *cmd, t_data *x);
void		ft_echo_action(t_list *cmdredir, char *str, t_data *x);

//cd.c
int			ft_cd(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_cd_organisation(char *tmp, t_list **envcp, char *str, t_data *x);
char		*ft_cd_back(char *tmp);
char		*ft_cd_home(char *tmp, t_list **cpenv);
char		*ft_cd_dash(char *str, t_list **cpenv, t_data *x);

//cd_utils.c
int			ft_cdquotes(char *str);
void		ft_cd_is_quotes(char *str);
char		*ft_check_str(char *str, t_data *x);
void		ft_cd_export(char *str, char *word, t_list *cpenv, t_data *x);
void		ft_cd_unset(char *str, char *str1, t_list *cpenv, t_data *x);

//cd_utils2.c
void		ft_change_oldpwd(char *word, t_list *cpenv, t_data *x);
void		ft_cd_is_back(char *word, char *tmp, t_list *cpenv, t_data *x);
void		ft_cd_is_til(char *word, char *tmp, t_list *cpenv, t_data *x);
void		ft_cd_is_dash(char *tmp1, char *word, t_list *cpenv, t_data *x);

//env.c
void		env_error(char	*str, t_list *cmdredir, t_data *x, int i);

typedef struct s_builtin_value	t_builtin_value;
typedef int						(*t_fct)(t_list *cmd,
									t_list **cpenv, t_data *x);

struct s_builtin_value
{
	char const			*b;
	t_fct const			fonction;
};

int			ft_exit(t_list *cmdredir, t_list **cpenv, t_data *x);
void		ft_exit_bis(char *str, t_data *x);
int			ft_export(t_list *cmdredirnext, t_list **cpenv, t_data *x);
int			ft_pwd(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_echo(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_cd(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_fonction(t_list *cmdredir, t_list **cpenv, t_data *x);
int			ft_env(t_list *cmdredir, t_list **cpenv, t_data *x);

static t_builtin_value const	g_lookup[] = {
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
