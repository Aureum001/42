/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_chunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:14:30 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/19 11:13:35 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	find_cheapest_in_chunk_a(t_data *d, int min_idx, int max_idx,
                                    t_move_details *move)
{
    t_stack	*curr;
    int		curr_p;
    int		cost;
    int		best_c;
    int		found;

    curr = d->stack_a;
    curr_p = 0;
    best_c = INT_MAX;
    found = 0;
    move->pos = -1; // Initialize to indicate not found
    while (curr)
    {
        if (curr->index >= min_idx && curr->index <= max_idx)
        {
            cost = curr_p;
            if (curr_p > d->size_a / 2)
                cost = d->size_a - curr_p;
            if (cost < best_c)
            {
                best_c = cost;
                move->pos = curr_p;
                move->rotations = (curr_p <= d->size_a / 2) ? curr_p : d->size_a - curr_p;
                move->direction = (curr_p <= d->size_a / 2) ? 1 : -1;
                found = 1;
            }
        }
        curr = curr->next;
        curr_p++;
    }
    return (found);
}

// Helper: Find the position in B where the value from A should be inserted
static int	find_insert_pos_b_desc(t_stack *b, int a_index)
{
    int		pos = 0;
    t_stack	*curr = b;

    if (!b)
        return (0);
    while (curr->next)
    {
        // Find the place where a_index fits between curr and curr->next
        if (curr->index > a_index && curr->next->index < a_index)
            return (pos + 1);
        curr = curr->next;
        pos++;
    }
    // If a_index is greater than all, or less than all, insert after the max
    // Find max index position
    int max_idx = b->index;
    int max_pos = 0;
    int i = 0;
    curr = b;
    while (curr)
    {
        if (curr->index > max_idx)
        {
            max_idx = curr->index;
            max_pos = i;
        }
        curr = curr->next;
        i++;
    }
    return (max_pos + 1) % (stack_size(b) + 1);
}

static void	rotate_b_to_insert(t_data *data, int insert_pos)
{
    if (insert_pos <= data->size_b / 2)
    {
        while (insert_pos-- > 0)
            rb(data, 1);
    }
    else
    {
        int r = data->size_b - insert_pos;
        while (r-- > 0)
            rrb(data, 1);
    }
}

static void	push_one_chunk_to_b(t_data *data, int min_idx, int max_idx,
                                int elements_to_push)
{
    t_move_details	move;
    int				pushed_count;

    pushed_count = 0;
    while (pushed_count < elements_to_push && data->size_a > 0)
    {
        if (!find_cheapest_in_chunk_a(data, min_idx, max_idx, &move))
            break; 
        while (move.rotations > 0)
        {
            if (move.direction == 1)
                ra(data, 1);
            else
                rra(data, 1);
            move.rotations--;
        }
        // --- New logic: rotate B to keep it sorted descending ---
        int insert_pos = find_insert_pos_b_desc(data->stack_b, data->stack_a->index);
        if (data->size_b > 1)
            rotate_b_to_insert(data, insert_pos);
        pb(data, 1);
        pushed_count++;
    }
}

void	process_all_chunks_to_b(t_data *data, int num_chunks,
                                int chunk_size_base, int original_size)
{
    int	i;
    int	min_idx_for_chunk;
    int	max_idx_for_chunk;
    int	actual_elements_to_push;

    i = 0;
    while (i < num_chunks && data->size_a > 3) // Leave a few for sort_three
    {
        min_idx_for_chunk = i * chunk_size_base;
        max_idx_for_chunk = (i + 1) * chunk_size_base - 1;
        if (i == num_chunks - 1) // Last chunk takes all remaining indices
            max_idx_for_chunk = original_size - 1;
        
        actual_elements_to_push = 0;
        // Count how many elements *actually* in A belong to this chunk range
        t_stack *scanner = data->stack_a;
        while(scanner) {
            if(scanner->index >= min_idx_for_chunk && scanner->index <= max_idx_for_chunk)
                actual_elements_to_push++;
            scanner = scanner->next;
        }
        
        if(actual_elements_to_push == 0) { // No elements for this chunk currently in A
            i++;
            continue;
        }
        push_one_chunk_to_b(data, min_idx_for_chunk, max_idx_for_chunk, actual_elements_to_push);
        i++;
    }
}

static int	find_pos_of_max_idx_b(t_data *data)
{
    t_stack	*current;
    int		max_idx_val;
    int		max_idx_pos;
    int		current_pos;

    if (!data->stack_b)
        return (-1); // Should not happen if size_b > 0
    current = data->stack_b;
    max_idx_val = INT_MIN; 
    max_idx_pos = 0;
    current_pos = 0;
    while (current)
    {
        if (current->index > max_idx_val)
        {
            max_idx_val = current->index;
            max_idx_pos = current_pos;
        }
        current = current->next;
        current_pos++;
    }
    return (max_idx_pos);
}

void	push_all_from_b_to_a_sorted(t_data *data)
{
    int	pos_of_max;
    int	rotations;

    while (data->size_b > 0)
    {
        pos_of_max = find_pos_of_max_idx_b(data);
        if (pos_of_max == -1) 
            break; 
        if (pos_of_max <= data->size_b / 2) 
        {
            rotations = pos_of_max;
            while (rotations-- > 0)
                rb(data, 1);
        }
        else 
        {
            rotations = data->size_b - pos_of_max;
            while (rotations-- > 0)
                rrb(data, 1);
        }
        pa(data, 1);
    }
}