# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 12:05:27 by ancanale          #+#    #+#              #
#    Updated: 2025/06/04 11:10:00 by ancanale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -fPIC
CC		= cc
RM		= rm -f
AR		= ar rc

NAME	= libft.a

INCDIR	= ./

SRCS	= ft_atoi.c ft_isalpha.c ft_isprint.c ft_memchr.c ft_memmove.c \
		ft_putendl_fd.c ft_strlcat.c ft_strncmp.c ft_strtrim.c \
		ft_bzero.c ft_isascii.c ft_itoa.c ft_memcmp.c ft_memset.c \
		ft_putnbr_fd.c ft_strnstr.c ft_tolower.c \
		ft_isalnum.c ft_isdigit.c ft_memccpy.c ft_memcpy.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_strmapi.c ft_strrchr.c ft_toupper.c \
		ft_substr.c ft_calloc.c ft_split.c ft_striteri.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_printf_bonus.c ft_printf_utils.c ft_print_c.c ft_print_d.c \
		ft_print_hex.c ft_print_i.c ft_print_p.c ft_print_s.c \
		ft_print_u.c ft_print_utils2.c ft_print_utils3.c ft_print_utils4.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c ft_strdup.c

OBJS	= ${SRCS:.c=.o}

${NAME}:	${OBJS}
				${AR} $@ $^

%.o:%.c		libft.h
					${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
					${RM} ${NAME}

re:			fclean all

.PHONY: re clean fclean all