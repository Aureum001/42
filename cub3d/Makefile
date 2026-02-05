# **************************************************************************** #
#                                   cub3d                                   #
# **************************************************************************** #

NAME        := cub3d
BONUS_NAME  := cub3d_bonus

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -MMD -MP -I include

SRC_DIR     := src
OBJ_DIR     := build

CORE_DIR    := $(SRC_DIR)/core
PARSER_DIR  := $(SRC_DIR)/parser
RENDER_DIR  := $(SRC_DIR)/render
UTILS_DIR   := $(SRC_DIR)/utils

COMMON_SRCS := \
	$(CORE_DIR)/app_loop.c \
	$(PARSER_DIR)/parse_args.c \
	$(PARSER_DIR)/parse_config.c \
	$(RENDER_DIR)/render_frame.c \
	$(UTILS_DIR)/cleanup.c \
	$(UTILS_DIR)/error.c

MANDATORY_SRCS := \
	$(CORE_DIR)/main.c

BONUS_ONLY_SRCS := \
	$(CORE_DIR)/main_bonus.c \
	$(CORE_DIR)/app_loop_bonus.c

SRCS        := $(COMMON_SRCS) $(MANDATORY_SRCS)
BONUS_SRCS  := $(COMMON_SRCS) $(BONUS_ONLY_SRCS)

OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  := $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

LIB_DIR     := lib
MLX_DIR     := $(LIB_DIR)/minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
MLX_HEADERS := -I $(MLX_DIR)

LIBS        := $(MLX_FLAGS)

ifdef WITH_BONUS
TARGET      := $(BONUS_NAME)
OBJECTS     := $(BONUS_OBJS)
else
TARGET      := $(NAME)
OBJECTS     := $(OBJS)
endif

all: $(NAME)

bonus:
	$(MAKE) WITH_BONUS=1 $(BONUS_NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@echo "\033[1;32mLinking $(NAME)\033[0m"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

$(BONUS_NAME): $(MLX_LIB) $(BONUS_OBJS)
	@echo "\033[1;32mLinking $(BONUS_NAME)\033[0m"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "\033[1;34mCompiling $<\033[0m"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(MLX_HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "\033[1;33mCleaning objects\033[0m"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean >/dev/null || true

fclean: clean
	@echo "\033[1;31mRemoving binaries\033[0m"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)
