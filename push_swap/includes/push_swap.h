/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/19 11:38:41 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <limits.h> // For INT_MAX, INT_MIN

typedef struct s_stack
{
	int				value;
	int				index; // 0-based index after sorting conceptually
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size_a;
	int		size_b;
}	t_data;

// Helper struct for finding cheapest moves in chunk sort
typedef struct s_move_details
{
	int	pos;        // 0-indexed position from top of stack
	int	rotations;  // Number of rotations needed
	int	direction;  // 1 for RA/RB, -1 for RRA/RRB
}	t_move_details;

/* Main program flow */
int		main(int argc, char **argv);
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
// void	radix_sort(t_data *data); // Keep if you plan to implement/use
void	chunk_sort(t_data *data);

/* Chunk sort helper functions (called by chunk_sort from sorting_utils.c) */
/* Definitions are in sorting_chunk.c */
void	process_all_chunks_to_b(t_data *data, int num_chunks,
			int chunk_size_base, int original_size);
void	push_all_from_b_to_a_sorted(t_data *data);

/* Stack utilities */
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new_node); // Renamed for clarity
void	stack_add_front(t_stack **stack, t_stack *new_node); // Renamed for clarity
t_stack	*stack_last(t_stack *stack);
int		stack_size(t_stack *stack);
void	free_stack(t_stack **stack); // Consider making static if only used in free_data
int		is_sorted(t_stack *stack);
// int	get_max_bits(t_stack *stack); // Keep if radix_sort is used
void	assign_index(t_data *data);

/* Input validation and parsing (original for push_swap.c main) */
int		is_valid_input(int argc, char **argv); // Used by push_swap's main
int		has_duplicates(t_stack *stack);    // Used by push_swap's main
int		is_number(char *str);              // Used by push_swap's main
long	ft_atol(const char *str);          // Used by push_swap's main

/* Error and memory management */
void	error_exit(t_data *data);
void	free_data(t_data *data);

/* Checker specific */
int		apply_command(char *command, t_data *data); // For checker

/* Parsing functions (new structure, used by checker and potentially push_swap) */
void	initialize_data(t_data *data);
int		is_valid_input_precheck(int argc, char **argv);
void	populate_initial_stack(t_data *data, int argc, char **argv);

/* Parsing utils functions (new structure) */
long	ft_atol_ps(const char *str, int *error_flag); // Differentiate from libft's atol
// void	add_node_to_stack_end(t_stack **stack, int value); // Replaced by stack_add_back

void add_move(const char *move);
void print_optimized_moves(void);

void	greedy_sort(t_data *data);

#endif