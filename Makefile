NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx_linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT = libft.a
LIBFT_PATH = ./libft

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/$(LIBFT)
	$(CC) -o $(NAME) $@ $^ $(MLX_FLAGS)

%.o: %.C
	$(CC) -Imlx_linux -03 -c $< -o $@

$(LIBFT_PATH)/$(LIBFT):
	make -C $(LIBFT_PATH) all

mlx:
	make -C $(MLX_DIR) all

mlx_clean:
	make -C $(MLX_DIR) clean

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx mlx_clean
