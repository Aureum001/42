CFLAGS = -Wall -Wextra -Werror
CC		= cc
RM		= rm -f
NAME = get_next_line.a

SRCS = get_next_line.c \
	get_next_line_utils.c \

SRCS_B = get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}
OBJS_B  = ${SRCS_B:.c=.o}

$(NAME): $(OBJS)
	$(MAKE) $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_B)
	$(MAKE) $(OBJS_B)
	ar rcs $(NAME) $(OBJS_B)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
					${RM} ${NAME}

re:			fclean all

.PHONY: re clean fclean all