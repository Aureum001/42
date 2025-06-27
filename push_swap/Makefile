# Executable names
NAME		= push_swap
BONUS_NAME	= checker

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I includes -I libft
LIBFT		= libft/libft.a

# Mandatory source files
SRC_MANDATORY = src/push_swap.c \
				src/sorting.c \
				src/greedy_sort.c \
				src/greedy_helpers.c

# Bonus source files
SRC_BONUS = src/checker_bonus.c \
			src/checker_utils_bonus.c

# Common source files (used by both)
SRC_COMMON = src/operations.c \
			 src/operations2.c \
			 src/operations3.c \
			 src/operations4.c \
			 src/utils.c \
			 src/utils2.c \
			 src/utils3.c \
			 src/parsing.c \
			 src/parsing_utils.c \
			 src/move_buffer.c

# Object files
OBJ_MANDATORY	= $(SRC_MANDATORY:.c=.o)
OBJ_BONUS		= $(SRC_BONUS:.c=.o)
OBJ_COMMON		= $(SRC_COMMON:.c=.o)

# Default rule
all: $(NAME)

# Mandatory build rule
$(NAME): $(OBJ_MANDATORY) $(OBJ_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) -no-pie $^ -o $(NAME)

# Bonus build rule
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJ_BONUS) $(OBJ_COMMON) $(LIBFT)
	$(CC) $(CFLAGS) -no-pie $^ -o $(BONUS_NAME)

# Libft rule
$(LIBFT):
	make -C libft

# Generic rule for .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rules
clean:
	rm -f $(OBJ_MANDATORY) $(OBJ_BONUS) $(OBJ_COMMON)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make fclean -C libft

re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re test100 test500 ctest100 ctest500 leakcheck test5

# === Testing Rules (depend on 'bonus' to ensure checker is built) ===

ctest100: bonus
	@NUMBERS="$$(seq 1 100 | shuf | tr '\n' ' ' | sed 's/ *$$//')"; \
	echo "Testing 100 numbers..."; \
	OPS=$$(./$(NAME) $$NUMBERS); \
	COUNT=$$(echo "$$OPS" | wc -l | xargs); \
	RESULT=$$(echo "$$OPS" | ./$(BONUS_NAME) $$NUMBERS); \
	echo "Moves: $$COUNT, Result: $$RESULT";

ctest500: bonus
	@NUMBERS="$$(seq 1 500 | shuf | tr '\n' ' ' | sed 's/ *$$//')"; \
	echo "Testing 500 numbers:"; \
	OPS=$$(./$(NAME) $$NUMBERS); \
	COUNT=$$(echo "$$OPS" | wc -l | xargs); \
	RESULT=$$(echo "$$OPS" | ./$(BONUS_NAME) $$NUMBERS); \
	echo "Moves: $$COUNT, Result: $$RESULT";

# === Valgrind Leak Checks (depend on 'bonus') ===

leakcheck: bonus
	@echo "--- Running all Valgrind leak checks ---"
	@make vtest_ps_ok
	@make vtest_ps_err
	@make vtest_ch_ok
	@make vtest_ch_err
	@make vtest_ch_ctrl_d
	@echo "\n--- All leak checks complete ---"

vtest_ps_ok:
	@echo "\n[VALGRIND] Testing push_swap: normal case"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 8 5 9 1 4 > /dev/null

vtest_ps_err:
	@echo "\n[VALGRIND] Testing push_swap: error case (duplicates)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 8 5 9 1 8 > /dev/null || true

vtest_ch_ok:
	@echo "\n[VALGRIND] Testing checker: OK case"
	@./$(NAME) 8 5 9 1 4 | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BONUS_NAME) 8 5 9 1 4 > /dev/null

vtest_ch_err:
	@echo "\n[VALGRIND] Testing checker: error case (invalid move)"
	@echo "invalid_move" | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BONUS_NAME) 8 5 9 1 4 > /dev/null || true

vtest_ch_ctrl_d:
	@echo "\n[VALGRIND] Testing checker: Ctrl+D (EOF) case"
	@cat /dev/null | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BONUS_NAME) 8 5 9 1 4 > /dev/null


test5:
	@echo "Testing all permutations of 5 numbers (should all be < 12 moves)..."
	@fails=0; \
	for a in 1 2 3 4 5; do \
	for b in 1 2 3 4 5; do \
	for c in 1 2 3 4 5; do \
	for d in 1 2 3 4 5; do \
	for e in 1 2 3 4 5; do \
	if [ "$$a" -ne "$$b" ] && [ "$$a" -ne "$$c" ] && [ "$$a" -ne "$$d" ] && [ "$$a" -ne "$$e" ] && \
	   [ "$$b" -ne "$$c" ] && [ "$$b" -ne "$$d" ] && [ "$$b" -ne "$$e" ] && \
	   [ "$$c" -ne "$$d" ] && [ "$$c" -ne "$$e" ] && \
	   [ "$$d" -ne "$$e" ]; then \
	    args="$$a $$b $$c $$d $$e"; \
	    count=`./push_swap $$args | wc -l`; \
	    if [ "$$count" -ge 12 ]; then \
	        echo "FAIL ($$count moves): $$args"; \
	        fails=$$((fails+1)); \
	    fi; \
	fi; \
	done; done; done; done; done; \
	if [ "$$fails" -eq 0 ]; then \
	    echo "All permutations OK (<12 moves)"; \
	else \
	    echo "$$fails permutations failed"; \
	fi