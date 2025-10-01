NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I ./mlx
LIBS = -L ./mlx ./mlx/libmlx.a -lXext -lX11 -lm

SRC = main.c 

OBJ = $(SRC:.c=.o)
MLX_LIB = ./mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(MLX_LIB):
	make -C ./mlx

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C ./mlx clean
	rm -f */$(OBJ)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	make fclean
	git add .
	git commit -m "update"
	git push

.PHONY: all clean re fclean git
