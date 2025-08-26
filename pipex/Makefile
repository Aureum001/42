NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft

SRCS = pipex.c find_cmd_path.c pipex_utils.c
BONUS_SRCS = pipex_bonus.c find_cmd_path.c pipex_utils.c here_doc_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJS) $(LIBFT)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

# Test the mandatory pipex (2 commands)
test:
	@echo "Testing mandatory pipex (grep 'foo' | tr a-z A-Z > outfile):"
	@echo "foo\nbar\nFooBar\nbaz\nFOO" > infile
	@./pipex infile "grep -i foo" "tr a-z A-Z" outfile
	@echo "Expected output:"
	@echo "FOO\nFOOBAR\nFOO"
	@echo "Actual output:"
	@cat outfile
	@rm -f infile outfile

# Test the bonus pipex_bonus (here_doc and multiple commands)
test_bonus:
	@echo "Testing bonus pipex_bonus (here_doc):"
	@printf "line1\nline2\nLIMITER\n" > input.txt
	@./pipex_bonus here_doc LIMITER "cat" "wc -c" outfile < input.txt
	@cat outfile
	@rm -f outfile input.txt
	@echo "Testing bonus pipex_bonus (multiple commands):"
	@echo "foo\nbar\nbaz" > infile
	@./pipex_bonus infile "grep a" "tr a x" "wc -l" outfile
	@cat outfile
	@rm -f infile outfile

leaks:
	@echo "Leak test for mandatory pipex:"
	@echo "foo\nbar\nbaz" > infile
	@valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "cat" "cat" outfile
	@rm -f infile outfile

leaks_bonus:
	@echo "Leak test for bonus pipex_bonus (here_doc):"
	@printf "line1\nline2\nLIMITER\n" > input.txt
	@valgrind --leak-check=full --show-leak-kinds=all ./pipex_bonus here_doc LIMITER "cat" "cat" outfile < input.txt
	@rm -f outfile input.txt
