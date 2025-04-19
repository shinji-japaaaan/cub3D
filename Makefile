# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 12:07:24 by sishizaw          #+#    #+#              #
#    Updated: 2025/04/19 16:56:54 by karai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lXext -lX11 -lm

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

SRCS = ./srcs/main.c \
		./srcs/init.c \
		./srcs/parse_map1.c \
		./srcs/parse_map1_2.c \
		./srcs/parse_map2.c \
		./srcs/parse_map3.c \
		./srcs/parse_map4.c \
		./srcs/parse_map4_2.c \
		./srcs/parse_map4_3.c \
		./srcs/parse_map4_4.c \
		./srcs/parse_map4_5.c \
		./srcs/parse_map4_6.c \
		./srcs/parse_map4_7.c \
		./srcs/free.c \
		./srcs/check_map_content.c \
		./srcs/check_map_structure.c \
		./srcs/check_map_structure2.c \
		./srcs/hit_horz.c\
		./srcs/hit_utils.c\
		./srcs/hit_vert.c\
		./srcs/utility_mlx.c\
		./srcs/img_raycast.c\
		./srcs/init_mlx.c\
		./srcs/update.c\
		./srcs/update_utils.c\
		./srcs/key_hook.c\
		./srcs/put_hd.c\
		./srcs/put_vd.c\
		./srcs/destroy_all.c\


OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_LIB) $(LIBFT_FLAGS) $(MLX_FLAGS)

mlx:
	make -C $(MLX_DIR) all

mlx_clean:
	make -C $(MLX_DIR) clean

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

