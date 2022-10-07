# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 14:34:45 by evsuits           #+#    #+#              #
#    Updated: 2022/10/04 11:06:23 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		= main.c \
			./lexeur/lexeur.c \
			./lexeur/lexeur_lexical.c \
			./lexeur/lexeur_grammatical.c \
			./utils/utils.c \
			./utils/utils2.c \
			./utils/ft_lstsize.c \
			./utils/lst_clear.c \
			./utils/lst_utils.c \
			./utils/ft_lstadd_front.c \
			./utils/ft_substr.c \
			./utils/ft_strcmp.c \
			./utils/putstr_fd.c \
			./utils/ft_bzero.c \
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
			./builtin/builtins.c \
			./builtin/export.c \
			./builtin/export_case.c \
			./builtin/export_utils.c \
			./builtin/unset.c \
			./builtin/pwd.c \
			./builtin/echo.c \
			./builtin/cd.c \
			./visualize/visualize_cmd_redir.c \
			./visualize/visualize_t_words.c \
			./visualize/visualize_btw_pipes.c \

OBJS					=	${SRCS:.c=.o}

CC						=	clang

CFLAGS					=	-Wall -Wextra -Werror -g3

RM						=	rm -rf

all		:	${NAME}

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o		:	%.c
		$(CC) $(CFLAGS)	-c	$<	-o	$@

clean	:
		${RM}	${OBJS}

fclean	:	clean
		${RM}	${NAME}

re:	fclean	all

.PHONY:	all	clean	fclean	re
