NAME = cub3d

SRCS = src/main.c src/map.c \
       parsing/start_parsing.c parsing/map_utils.c parsing/read_process_line.c \
	   parsing/parsing_map.c parsing/parsing_player.c \
	   parsing/parsing_textures.c parsing/parse_single_line.c parsing/parsing_handler.c \
	   parsing/parsing_color.c utils/clean_utils.c

OBJS = $(SRCS:%.c=obj/%.o)
LIBFT = includes/libft
MLX = includes/mlx_linux
EXT_LIB = $(MLX)/libmlx.a
CC = cc
RM = rm -fr
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT) -I$(MLX)
LDFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -L/usr/include/X11/extensions -lX11 -lXext

all: libft.a $(EXT_LIB) $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -g $(OBJS) $(EXT_LIB) $(CFLAGS) $(LDFLAGS) -o $(NAME)

$(EXT_LIB):
	@make -C $(MLX)

libft.a:
	@make -C $(LIBFT)

clean:
	$(RM) obj a.out

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(MLX) clean

re: fclean all
.PHONY: all clean fclean re libft.a

v:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --suppressions=mlx.supp ./$(NAME)