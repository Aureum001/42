/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:52:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/16 17:35:05 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "./libft/libft.h"

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

#endif
