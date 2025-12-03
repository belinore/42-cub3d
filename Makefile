
NAME = cub3d

HDR = cub3d.h

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/draw_utils.c $(SRC_DIR)/init_mlx.c $(SRC_DIR)/init_game.c \
	  $(SRC_DIR)/raycasting.c $(SRC_DIR)/raycasting2.c $(SRC_DIR)/render.c $(SRC_DIR)/events.c \
	  $(SRC_DIR)/movement.c $(SRC_DIR)/minimap.c $(SRC_DIR)/utils.c
SRC_DIR = ./src

OBJS := $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O2

# Define OS-specific flags
ifeq ($(shell uname), Darwin)  # macOS
INCLUDES = -Iminilibx_macos -Iincludes
    LFLAGS = -L ./minilibx_macos \
              -l mlx -framework OpenGL -framework Appkit
else  # Assume Linux
INCLUDES = -Iminilibx-linux -Iincludes
    LFLAGS = -L./minilibx-linux \
              -l mlx_Linux -l X11 -l Xext -l Xrender -l GL -lm
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

debug:
	@echo "Sources: $(SRC)"
	@echo "Objects: $(OBJS)"
	@echo "CC Command: $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LFLAGS)"
