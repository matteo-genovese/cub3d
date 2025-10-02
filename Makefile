NAME = cub3D
CC	= cc -std=gnu11
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I ./mlx
LIBS = -L ./mlx ./mlx/libmlx.a -lXext -lX11 -lm

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/

SRC_FILES = main.c initialize.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

MLX_LIB = ./mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(MLX_LIB):
	make -C ./mlx

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(INCLUDES) -c $< -o $@

clean:
	make -C ./mlx clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	make fclean
	git add .
	git commit -m "update"
	git push

.PHONY: all clean re fclean git
