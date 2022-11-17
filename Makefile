# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 14:34:45 by evsuits           #+#    #+#              #
#    Updated: 2022/11/16 02:22:07 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= main.c \
	  ./lexeur/lexeur.c \
	  ./lexeur/lexeur_lexical.c \
	  ./lexeur/lexeur_lexical_utils.c \
	  ./lexeur/lexeur_grammatical.c \
	  ./lexeur/checks.c \
	  ./lexeur/del.c \
	  ./lexeur/del_bis.c \
	  ./lexeur/lim_spac.c \
	  ./lexeur/new_expand.c \
	  ./lexeur/new_expand_utils.c \
	  ./lexeur/expand_utils.c \
	  ./lexeur/dollar.c \
	  ./parser/new_parser.c \
	  ./parser/parser_cmd_redir.c \
	  ./parser/parser_cmdredir_utils.c \
	  ./parser/environnement.c \
	  ./parser/heredoc.c \
	  ./parser/open_error_files.c \
	  ./parser/open_files.c \
	  ./parser/get_path.c \
	  ./parser/gestion.c \
	  ./parser/expand.c \
	  ./parser/expand_annexe.c \
	  ./parser/expand_utils.c \
	  ./parser/executable.c \
	  ./parser/cmd_constructor.c\
	  ./parser/cmd_constructor_annexe.c\
	  ./parser/error_functions.c \
	  ./parser/heredoc_utils.c \
	  ./parser/cmd_redir_utils.c \
	  ./parser/exe_utils.c \
	  ./execution/execution_utils.c \
	  ./execution/execution_pipe.c \
	  ./execution/execution_no_pipe.c \
	  ./execution/redirection_pipe.c \
	  ./execution/redirection_no_pipe.c \
	  ./execution/execution_pipe_utils.c \
	  ./execution/execution_organisation.c \
	  ./execution/execution_call_no_pipe.c \
	  ./utils/ft_calloc.c \
	  ./utils/utils.c \
	  ./utils/utils2.c \
	  ./utils/lst_clear.c \
	  ./utils/free.c \
	  ./utils/lst_utils.c \
	  ./utils/ft_lstadd_front.c \
	  ./utils/ft_substr.c \
	  ./utils/ft_strcmp.c \
	  ./utils/putstr_fd.c \
	  ./utils/ft_bzero.c \
	  ./utils/ft_lstsize.c \
	  ./utils/ft_itoa.c \
	  ./builtin/builtins.c \
	  ./builtin/export.c \
	  ./builtin/export_case.c \
	  ./builtin/export_utils.c \
	  ./builtin/unset.c \
	  ./builtin/pwd.c \
	  ./builtin/echo.c \
	  ./builtin/echo_utils.c \
	  ./builtin/echo_utils2.c \
	  ./builtin/cd.c \
	  ./builtin/cd_utils.c \
	  ./builtin/cd_utils2.c \
	  ./builtin/exit.c \
	  ./builtin/exit_utils.c \
	  ./builtin/env.c \
	  main_utils.c \
	  signaux.c \


CC= cc

CFLAGS= -g3 -Wall -Werror -Wextra

OBJ= ${SRCS:.c=.o}

NAME= minishell

%.o: %.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${OBJ} -lreadline -o ${NAME}

clean:
	rm -rf *.o
	rm -rf ./utils/*.o
	rm -rf ./builtin/*.o
	rm -rf ./lexeur/*.o
	rm -rf ./parser/*.o
	rm -rf ./execution/*.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean all re
