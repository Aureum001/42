/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:20:13 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/11 17:19:27 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_safe(int row, int board[])
{
	int	i;
	int	tmp;

	i = 0;
	while (i < row)
	{
		tmp = board[row] - board[i];
		if (tmp < 0)
			tmp *= -1;
		if (board[row] == board[i] || row - i == tmp)
			return (0);
		i++;
	}
	return (1);
}

void	board_print(int board[])
{
	int		i;
	char	tmp;

	i = 0;
	while (i < 10)
	{
		tmp = board[i] + '0';
		write(1, &tmp, 1);
		i++;
	}
	write(1, "\n", 1);
}

void	place_queen(int row, int *solutions, int board[])
{
	int	i;

	i = 0;
	if (row == 10)
	{
		*solutions += 1;
		board_print(board);
		return ;
	}
	while (i < 10)
	{
		board[row] = i;
		if (is_safe(row, board))
			place_queen(row + 1, solutions, board);
		i++;
	}
}

int	ft_ten_queens_puzzle(void)
{
	int	solutions;
	int	i;
	int	board[10];

	solutions = 0;
	i = 0;
	while (i < 10)
		board[i++] = 0;
	place_queen(0, &solutions, board);
	return (solutions);
}
