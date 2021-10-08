NAME = fractol

SRC_DIR = ./src
OBJ_DIR = ./obj

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = ./minilibx-linux
MINILIBX = $(MINILIBX_DIR)/mlx.a
HEADERS = ./includes/fractol.h

SRC = main.c 				\
	  mlx_helpers.c			\
	  event_handlers.c 		\
	  mandelbrot.c			\
	  julia.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LFLAGS = -L./libft -L./minilibx-linux -lft -lmlx -lXext -lX11 -lm
IFLAGS = -I./includes
CFLAGS = -Wall -Werror -Wextra -O3
CC = gcc

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

run: all
	./$(NAME) mandelbrot

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
