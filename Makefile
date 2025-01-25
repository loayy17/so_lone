CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g
NAME = so_long
RM = rm -f
LIBFTPATH = ./libraries/Libft
LIBFTAR = $(LIBFTPATH)/libft.a
SRCS = map.c
OBJS = $(SRCS:.c=.o)
MLXFLAGS = -lmlx -lXext -lX11

all: $(LIBFTAR) $(NAME)

$(LIBFTAR):
	$(MAKE) -C $(LIBFTPATH)

$(NAME): $(LIBFTAR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTAR) $(MLXFLAGS)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTPATH) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re libft