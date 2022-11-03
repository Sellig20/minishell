# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 14:34:45 by evsuits           #+#    #+#              #
#    Updated: 2022/11/03 20:57:36 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= main.c \
	  visu.c \
	  ./lexeur/lexeur.c \
	  ./lexeur/lexeur_lexical.c \
	  ./lexeur/lexeur_lexical_utils.c \
	  ./lexeur/lexeur_grammatical.c \
	  ./lexeur/del.c \
	  ./lexeur/lim_spac.c \
	  ./lexeur/new_expand.c \
	  ./parser/new_parser.c \
	  ./parser/parser_cmd_redir.c \
	  ./parser/environnement.c \
	  ./parser/heredoc.c \
	  ./parser/open_error_files.c \
	  ./parser/open_files.c \
	  ./parser/get_path.c \
	  ./parser/gestion.c \
	  ./parser/expand.c \
	  ./parser/expand_annexe.c \
	  ./parser/executable.c \
	  ./parser/sep_cmd.c \
	  ./parser/cmd_constructor.c\
	  ./parser/error_functions.c \
	  ./execution/execution_pipe.c \
	  ./execution/execution_no_pipe.c \
	  ./execution/redirection_pipe.c \
	  ./execution/redirection_no_pipe.c \
	  ./execution/execution_pipe_utils.c \
	  ./execution/execution_organisation.c \
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
	  ./builtin/cd.c \
	  ./builtin/exit.c \
	  ./builtin/exit_utils.c \
	  ./builtin/env.c \

CC= gcc

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
