/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/23 12:40:29 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <limits.h>

# define MOVE_BUF_SIZE 20000

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_buffer
{
	char	*moves[MOVE_BUF_SIZE];
	int		count;
}	t_buffer;

typedef struct s_data
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	int			size_a;
	int			size_b;
	t_buffer	buffer;
}	t_data;

typedef struct s_move_plan
{
	int	cost;
	int	a_rot;
	int	a_dir;
	int	b_rot;
	int	b_dir;
}	t_move_plan;

/* Main program flow */
void	push_swap(t_data *data);

/* Operations */
void	sa(t_data *data, int print);
void	sb(t_data *data, int print);
void	ss(t_data *data, int print);
void	pa(t_data *data, int print);
void	pb(t_data *data, int print);
void	ra(t_data *data, int print);
void	rb(t_data *data, int print);
void	rr(t_data *data, int print);
void	rra(t_data *data, int print);
void	rrb(t_data *data, int print);
void	rrr(t_data *data, int print);

/* Sorting algorithms */
void	sort_three(t_data *data);
void	sort_five(t_data *data);
void	greedy_sort(t_data *data);

/* Stack utilities */
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new_node);
void	stack_add_front(t_stack **stack, t_stack *new_node);
t_stack	*stack_last(t_stack *stack);
int		stack_size(t_stack *stack);
void	free_stack(t_stack **stack);
int		is_sorted(t_stack *stack);
void	assign_index(t_data *data);

/* Input validation and parsing */
int		is_valid_input(int argc, char **argv);
int		has_duplicates(t_stack *stack);
int		is_number(char *str);
long	ft_atol(const char *str);
long	ft_atol_ps(const char *str, int *error_flag);

/* Error and memory management */
void	error_exit(t_data *data);
void	free_data(t_data *data);

/* Move Buffer */
void	add_move(t_data *data, const char *move);
void	print_optimized_moves(t_data *data);
void	free_buffer(t_data *data);

/* Greedy sort helpers */
void	calc_rot(int pos, int size, int *rot, int *dir);
int		get_target_pos_in_b(t_stack *stack_b, int a_index);
int		find_max_index_pos(t_stack *stack);

#endif