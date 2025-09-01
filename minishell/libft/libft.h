/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:21:43 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/04 11:10:00 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFFER_SIZE 42

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_print
{
	va_list	args;
	int		width;
	int		precision;
	int		z_padding;
	int		point;
	int		dash;
	int		total_length;
	int		sign;
	int		zero;
	int		percent;
	int		space;
	int		hash;
	int		plus;
}	t_print;

int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t nmemb, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int nb, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_printf(char const *format, ...);
t_print	*ft_initialise_tab(t_print *tab);
void	ft_reset_flags(t_print *tab);
int		ft_print_padding(int padding);
int		ft_get_numlen(unsigned long long n, int base);
int		ft_calculate_padding(t_print *tab, int numlen, int sign, int *zero_pad);
void	ft_putnbr_base(unsigned long long n, int base, int uppercase);
int		ft_format_integer(t_print *tab, long long n, int is_signed);
int		ft_format_hex(t_print *tab, unsigned long long n, int uppercase);
int		ft_is_flag(char c);
int		ft_print_i(t_print *tab);
int		ft_print_u(t_print *tab);
int		ft_print_d(t_print *tab);
int		ft_print_hex(t_print *tab, int kind);
int		ft_print_c(t_print *tab);
int		ft_print_s(t_print *tab);
int		ft_print_p(t_print *tab);
int		ft_eval_format(t_print *tab, char const *format, int i);
int		ft_parse_flag(t_print *tab, char const *format, int j);
int		ft_print_perc(t_print *tab);
int		ft_handle_sign(t_print *tab, long long n, int is_signed);
int		ft_handle_hex_prefix(t_print *tab, unsigned long long n, int uppercase);
int		ft_handle_zero_precision(t_print *tab, long long n);
void	ft_print_integer(t_print *tab, long long n, int sign, int zero_pad);
void	ft_print_hex_number(t_print *tab, unsigned long long n,
			int uppercase, int zero_pad);
void	ft_print_zeros(int count);
char	*get_next_line(int fd);

#endif