#include "../includes/push_swap.h"

#define MOVE_BUF_SIZE 20000

static char *move_buffer[MOVE_BUF_SIZE];
static int move_count = 0;

void add_move(const char *move)
{
	if (move_count < MOVE_BUF_SIZE)
		move_buffer[move_count++] = ft_strdup(move);
}

void print_optimized_moves(void)
{
	int i = 0;
	while (i < move_count)
	{
		if (i + 1 < move_count)
		{
			if ((!ft_strncmp(move_buffer[i], "ra", 2) && !ft_strncmp(move_buffer[i+1], "rb", 2)) ||
				(!ft_strncmp(move_buffer[i], "rb", 2) && !ft_strncmp(move_buffer[i+1], "ra", 2)))
			{
				ft_putstr_fd("rr\n", 1);
				i += 2;
				continue;
			}
			if ((!ft_strncmp(move_buffer[i], "rra", 3) && !ft_strncmp(move_buffer[i+1], "rrb", 3)) ||
				(!ft_strncmp(move_buffer[i], "rrb", 3) && !ft_strncmp(move_buffer[i+1], "rra", 3)))
			{
				ft_putstr_fd("rrr\n", 1);
				i += 2;
				continue;
			}
			if ((!ft_strncmp(move_buffer[i], "sa", 2) && !ft_strncmp(move_buffer[i+1], "sb", 2)) ||
				(!ft_strncmp(move_buffer[i], "sb", 2) && !ft_strncmp(move_buffer[i+1], "sa", 2)))
			{
				ft_putstr_fd("ss\n", 1);
				i += 2;
				continue;
			}
		}
		ft_putstr_fd(move_buffer[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	// Free the buffer
	for (i = 0; i < move_count; i++)
		free(move_buffer[i]);
	move_count = 0;
}