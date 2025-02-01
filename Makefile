CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibraries/Libft
NAME = so_long
SRCS = 	src/draw_player_directions.c \
		src/draw_monster_directions.c \
		src/load_player_exit_anim.c \
		src/game_init.c \
		src/input_handling.c \
		src/main.c \
		src/map_validation.c \
		src/memory_management.c \
		src/monster.c \
		src/path_validation.c \
		src/rendering.c \
		src/message_free.c \
		src/utils.c \
		
OBJS = $(SRCS:.c=.o)
LIBFT = libraries/Libft/libft.a
MLX = -lmlx -lXext -lX11

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libraries/Libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C libraries/Libft clean

fclean: clean
	rm -f $(NAME)
	make -C libraries/Libft fclean

re: fclean all

.PHONY: all clean fclean re