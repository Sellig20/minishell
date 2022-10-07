/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:49:26 by jecolmou          #+#    #+#             */
/*   Updated: 2022/05/21 16:19:57 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

# define IN 0
# define OUT 1

typedef struct s_data {
	int		pipe_fd[2];
	int		f1;
	int		f2;
	pid_t	child1;
	pid_t	child2;
}		t_data;

//////////UTILS//////////
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
int		ft_strcmp(const char *s1, const char *s2);

//////////PATH & COMMAND//////////
char	**ft_get_path(char **env);
char	**ft_get_command(char *cmd, char	*pc);
char	*ft_path_command(char	*cmd, char **env);
char	*ft_return_pc(char **command, char **path);

//////////TOOLS//////////
void	ft_argv_error(char *cmd);
int		ft_exist_error(char *infile);
int		ft_perm_error(char *file);
int		ft_read_infile(char *infile);
int		ft_read_outfile(char *outfile);
void	ft_free_array(char	**option);
int		ft_parse(char **argv);
int		ft_is_space(char *str);

//////////CHILDS FUNCTIONS//////////
void	ft_child_one(t_data *x, char *pc, char **option, char **env);
void	ft_child_two(t_data *x, char *pc, char **option, char **env);

//////////PARENTS FUNCTIONS//////////
void	ft_parent_one(t_data *x, char **argv, char **env);
void	ft_parent_two(t_data *x, char **argv, char **env);
void	ft_annexe_parent_one(t_data *x);
void	ft_annexe_parent_two(t_data *x);
void	ft_error_child(char **option, char *pc);
void	ft_if(char	*argv, char **pc, char ***option);
void	ft_else(char *argv, char ***opt, char **env, char **pc);

void	pipex(t_data *x, char **argv, char *env[]);

#endif
