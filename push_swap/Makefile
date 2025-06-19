CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft
SRC = src/push_swap.c src/operations.c src/operations2.c src/operations3.c src/operations4.c src/sorting.c src/sorting_chunk.c src/sorting_utils.c src/utils.c src/utils2.c src/utils3.c src/parsing.c src/parsing_utils.c src/move_buffer.c src/greedy_sort.c
OBJ = $(SRC:.c=.o)
NAME = push_swap
LIBFT = libft/libft.a

CHECKER = checker
CHECKER_C_FILES = src/checker.c src/checker_utils.c
CHECKER_COMMON_OBJ = src/operations.o src/operations2.o src/operations3.o src/operations4.o src/utils.o src/utils2.o src/utils3.o src/parsing.o src/parsing_utils.o src/move_buffer.o src/greedy_sort.o
CHECKER_OBJ = $(CHECKER_C_FILES:.c=.o) $(CHECKER_COMMON_OBJ)

all: $(LIBFT) $(NAME) checker

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
# Add -no-pie if you want push_swap to also be non-PIE, otherwise it might face the same issue
# if libft is not compiled with -fPIC/-fPIE.
# For consistency, if libft is non-PIC, both executables should be non-PIE.
	$(CC) $(CFLAGS) -no-pie $(OBJ) $(LIBFT) -o $(NAME)

checker: $(CHECKER_OBJ) $(LIBFT)
# Add -no-pie to the linking command for checker
	$(CC) $(CFLAGS) -no-pie $(CHECKER_OBJ) $(LIBFT) -o checker

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(CHECKER_OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME) checker
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re

test100:
	@NUMBERS="$$(seq 1 100 | shuf | tr '\n' ' ' | sed 's/ *$$//')"; \
	echo "Testing 100 numbers:"; \
	echo "$$NUMBERS"; \
	OPS=$$(echo "$$NUMBERS" | xargs ./push_swap); \
	echo "$$OPS";

test500:
	@NUMBERS="$$(seq 1 500 | shuf | tr '\n' ' ' | sed 's/ *$$//')"; \
	echo "Testing 500 numbers:"; \
	echo "$$NUMBERS"; \
	OPS=$$(echo "$$NUMBERS" | xargs ./push_swap); \
	echo "$$OPS";