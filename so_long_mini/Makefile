NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = \
	src/main.c \
	src/map.c \
	src/render.c \
	src/input.c \
	src/utils.c \
	src/cleanup.c \
	src/map_load.c \
	src/idle_anim.c \
	src/assets.c \
	src/cleanup_and_exit.c \
	src/map_utils.c \
	src/map_validator.c
OBJ = $(SRC:.c=.o)
INCLUDES = -Iincludes -Iminilibx-linux
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

SRC_BONUS = \
	src/main_bonus.c \
	src/bonus_utils_bonus.c \
	src/enemies_bonus.c \
	src/render_bonus.c \
	src/parse_bonus.c \
	src/cleanup.c \
	src/map.c \
	src/map_load.c \
	src/input.c \
	src/utils.c \
	src/idle_anim.c \
	src/render.c \
	src/assets.c \
	src/time_bonus.c \
	src/input_bonus.c \
	src/hud_bonus.c \
	src/cleanup_and_exit_bonus.c \
	src/map_utils.c \
	src/map_validator.c \

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME) so_long_bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(MAKE) -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) $(LIBFT) -o $(NAME)

so_long_bonus: $(LIBFT) $(OBJ_BONUS)
	$(MAKE) -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(INCLUDES) $(LIBS) $(LIBFT) -o so_long_bonus

$(OBJ): includes/so_long.h

$(OBJ_BONUS): includes/so_long_bonus.h

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/test.ber

leaks_bonus:
	valgrind --leak-check=full --show-leak-kinds=all ./so_long_bonus maps/map_bonus.ber

clean:
	 rm -f $(OBJ) $(OBJ_BONUS) so_long_bonus
	 $(MAKE) -C $(LIBFT_DIR) clean
	 $(MAKE) -C minilibx-linux clean

fclean: clean
	 rm -f $(NAME) so_long_bonus
	 $(MAKE) -C $(LIBFT_DIR) fclean
	 $(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re bonus
