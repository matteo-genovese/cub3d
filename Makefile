NAME = cub3D
CC	= cc -std=gnu11
CFLAGS = -g -Wall -Wextra -Werror

INCLUDES = -I ./mlx -I ./include -I ./libft
LIBS = -L ./mlx -L ./libft ./mlx/libmlx.a ./libft/libft.a -lXext -lX11 -lm

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/
LIBFT_DIR = libft/

SRC_FILES = main.c initialize.c dda.c map.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

MLX_LIB = ./mlx/libmlx.a
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBS)
	@echo "Executable $(NAME) created"

$(MLX_LIB):
	make -C ./mlx

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(INCLUDES) -c $< -o $@

clean:
	make -C ./mlx clean
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "Executable $(NAME) removed"
	
re: fclean all

git:
	make fclean
	git add .
	git commit -m "update"
	git push

.PHONY: all clean re fclean git
