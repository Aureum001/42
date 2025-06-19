/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:04:57 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/17 10:39:32 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	calculate_num_chunks(int original_size)
{
    if (original_size <= 100)
        return (5);
    else if (original_size <= 500)
        return (11);
    else
        return (15); // Or a different calculation for very large numbers
}

static void	sort_remaining_in_a(t_data *data)
{
    if (data->size_a == 3)
        sort_three(data);
    else if (data->size_a == 2
        && data->stack_a->value > data->stack_a->next->value)
        sa(data, 1);
}

void	chunk_sort(t_data *data)
{
    int	chunk_size_base;
    int	num_chunks;
    int	original_size;

    if (is_sorted(data->stack_a))
        return ;
    original_size = data->size_a;
    assign_index(data);
    num_chunks = calculate_num_chunks(original_size);
    if (num_chunks == 0 || original_size < 4) // Basic check
        return; // Should be handled by sort_three or already sorted
    chunk_size_base = original_size / num_chunks; // Integer division
    // If chunk_size_base is 0 (e.g. original_size < num_chunks), adjust
    if (chunk_size_base == 0)
        chunk_size_base = 1;

    process_all_chunks_to_b(data, num_chunks, chunk_size_base, original_size);
    sort_remaining_in_a(data);
    push_all_from_b_to_a_sorted(data);
}
