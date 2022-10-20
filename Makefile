# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 14:34:45 by evsuits           #+#    #+#              #
#    Updated: 2022/10/13 22:33:36 by evsuits          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= main.c \
	  visu.c \
	  ./lexeur/lexeur.c \
	  ./lexeur/lexeur_lexical.c \
	  ./lexeur/lexeur_lexical_utils.c \
	  ./lexeur/lexeur_grammatical.c \
	  ./lexeur/quotes.c \
	  ./lexeur/lim_spac.c \
	  ./lexeur/expand_btw_quot.c \
	  ./parser/new_parser.c \
	  ./parser/parser_cmd_redir.c \
	  ./parser/environnement.c \
	  ./parser/parser_redir_files.c \
	  ./parser/get_path.c \
	  ./parser/gestion.c \
	  ./parser/expand.c \
	  ./parser/dollar.c \
	  ./parser/cmd_constructor.c\
	  ./execution/execution.c \
	  ./execution/execution_no_pipe.c \
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
	  ./builtin/cd.c \

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
