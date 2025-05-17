# Project name and output
NAME = libftprintf.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = ft_printf.c \
	ft_printf_utils.c \
	ft_print_utils2.c \
	ft_print_utils3.c \
	ft_print_s.c \
	ft_print_d.c \
	ft_print_i.c \
	ft_print_u.c \
	ft_print_hex.c \
	ft_print_c.c \
	ft_print_p.c \
	ft_print_utils4.c

# Object files
OBJ = $(SRC:.c=.o)

# Include libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Bonus source files
SRC_BONUS = ft_printf_bonus.c \
	ft_printf_utils.c \
	ft_print_utils2.c \
	ft_print_utils3.c \
	ft_print_s.c \
	ft_print_d.c \
	ft_print_i.c \
	ft_print_u.c \
	ft_print_hex.c \
	ft_print_c.c \
	ft_print_p.c \
	ft_print_utils4.c

# Bonus object files
OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Clean bonus objects before regular build
.PHONY: clean_bonus
clean_bonus:
	rm -f ft_printf_bonus.o

# Clean regular objects before bonus build
.PHONY: clean_regular
clean_regular:
	rm -f ft_printf.o

# Default target - first clean bonus objects
all:	$(NAME)

# Link with libft
$(NAME): clean_bonus | $(LIBFT)
	$(MAKE) $(OBJ)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)

# Bonus target - first clean regular objects
bonus: clean_regular | $(LIBFT)
	$(MAKE) $(OBJ_BONUS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ_BONUS)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re:	fclean all

# Phony targets
.PHONY: all clean fclean re clean_bonus clean_regular