# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 13:33:46 by jecolmou          #+#    #+#              #
#    Updated: 2022/05/21 16:18:27 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	pipex

SRCS					=	pipex.c \
							parent.c \
							parents_annexe.c \
							childs.c \
							path_command.c \
							tools.c \
							free.c \
							parsing.c \
							utils/ft_split.c \
							utils/ft_strnstr.c \
							utils/ft_strjoin.c \
							utils/ft_strlen.c \
							utils/ft_putstr_fd.c \
							utils/ft_strcmp.c \

OBJS					=	${SRCS:.c=.o}

CC						=	clang

CFLAGS					=	-Wall -Wextra -Werror

RM						=	rm -rf

all		:	${NAME}

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o		:	%.c
		$(CC) $(CFLAGS)	-c	$<	-o	$@

clean	:
		${RM}	${OBJS}

fclean	:	clean
		${RM}	${NAME}

re:	fclean	all

.PHONY:	all	clean	fclean	re
