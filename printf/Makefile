NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

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

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

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

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	$(MAKE) $(OBJ)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ_BONUS) | $(LIBFT)
	$(MAKE) $(OBJ_BONUS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ_BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus