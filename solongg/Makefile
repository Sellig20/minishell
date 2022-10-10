# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:35:34 by jecolmou          #+#    #+#              #
#    Updated: 2022/06/30 20:48:32 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME					=	so_long

SRC					=	so_long.c \
							parsing/parsing.c \
							parsing/open_map.c \
							parsing/parse_p.c \
							parsing/parse_e.c \
							parsing/parse_c.c \
							parsing/wall.c \
							get_next_line/get_next_line.c \
							get_next_line/get_next_line_utils.c \
							linked_lists/ft_add_back.c \
							linked_lists/ft_lstsize.c \
							linked_lists/ft_lstclear.c \
							tools.c \
							mlx.c \
							get_images.c \
							keyboard.c \
							keyboard_annex.c \
							x_y.c \

NAME = so_long

LIBFT = ./libft/libft.a

MLX = ./mlx/libmlx.a

CC = clang

LINK = clang

CFLAGS = -Wall -Wextra -Werror -Imlx -Ilibft -I. -c

OBJ = $(SRC:.c=.o)

LFLAGS	=	-ldl -lmlx -Lmlx -lm -lXext -lX11 -Llibft -lft -Lmlx -lmlx

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(LINK) $(OBJ) $(LFLAGS) $(OUTPUT_OPTION)

$(LIBFT) :
	$(MAKE) -C ./libft

$(MLX) :
	$(MAKE) -C ./mlx

%.o: %.c
	${CC} ${CFLAGS} $< $(OUTPUT_OPTION)

clean:
	$(MAKE) $@ -C ./libft
	$(MAKE) $@ -C ./mlx
	rm -f $(OBJ)

fclean: clean
	${MAKE} $@ -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
