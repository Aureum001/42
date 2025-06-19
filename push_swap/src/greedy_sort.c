#include "../includes/push_swap.h"

static void	calc_rot(int pos, int size, int *rot, int *dir)
{
    if (pos <= size / 2)
    {
        *rot = pos;
        *dir = 1;
    }
    else
    {
        *rot = size - pos;
        *dir = -1;
    }
}

/*
*   Finds the correct position in stack B for an element from stack A.
*   The goal is to keep B sorted in descending order.
*   It returns the position of the element in B that should be at the top
*   before we push the new element from A.
*/
static int	get_target_pos_in_b(t_stack *stack_b, int a_index)
{
    t_stack	*current_b;
    int		target_pos;
    long	closest_smaller;
    int		pos;

    current_b = stack_b;
    target_pos = -1;
    closest_smaller = LONG_MIN;
    pos = 0;
    // Find the largest element in B that is still smaller than a_index.
    // The element from A should be placed on top of this one.
    while (current_b)
    {
        if (current_b->index < a_index && current_b->index > closest_smaller)
        {
            closest_smaller = current_b->index;
            target_pos = pos;
        }
        current_b = current_b->next;
        pos++;
    }
    // If no smaller element was found, a_index is the new minimum.
    // It should be placed on top of the current maximum element in B.
    if (closest_smaller == LONG_MIN)
    {
        int	max_index = INT_MIN;
        pos = 0;
        current_b = stack_b;
        while (current_b)
        {
            if (current_b->index > max_index)
            {
                max_index = current_b->index;
                target_pos = pos;
            }
            current_b = current_b->next;
            pos++;
        }
    }
    return (target_pos);
}

void	greedy_sort(t_data *data)
{
    int		target_pos_b;

    assign_index(data);
    // Push first two elements to B to start the process
    if (data->size_a > 2)
        pb(data, 1);
    if (data->size_a > 2)
        pb(data, 1);
    while (data->size_a > 0)
    {
        t_stack	*curr_a = data->stack_a;
        int		best_cost = INT_MAX;
        int		best_a_rot = 0, best_a_dir = 1, best_b_rot = 0, best_b_dir = 1;
        int		pos = 0;
        while (curr_a)
        {
            int	a_rot, a_dir, b_rot, b_dir, cost;
            calc_rot(pos, data->size_a, &a_rot, &a_dir);
            target_pos_b = get_target_pos_in_b(data->stack_b, curr_a->index);
            calc_rot(target_pos_b, data->size_b, &b_rot, &b_dir);
            if (a_dir == b_dir)
                cost = (a_rot > b_rot) ? a_rot : b_rot;
            else
                cost = a_rot + b_rot;
            if (cost < best_cost)
            {
                best_cost = cost;
                best_a_rot = a_rot;
                best_a_dir = a_dir;
                best_b_rot = b_rot;
                best_b_dir = b_dir;
            }
            curr_a = curr_a->next;
            pos++;
        }
        int a_rot = best_a_rot, a_dir = best_a_dir;
        int b_rot = best_b_rot, b_dir = best_b_dir;
        while (a_rot > 0 && b_rot > 0 && a_dir == b_dir)
        {
            if (a_dir == 1)
                rr(data, 1);
            else
                rrr(data, 1);
            a_rot--;
            b_rot--;
        }
        while (a_rot-- > 0)
            (a_dir == 1) ? ra(data, 1) : rra(data, 1);
        while (b_rot-- > 0)
            (b_dir == 1) ? rb(data, 1) : rrb(data, 1);
        pb(data, 1);
    }
    // Rotate B so the largest element (max index) is at the top
    int max_pos = 0, max_idx = INT_MIN, i = 0;
    t_stack *curr_b = data->stack_b;
    while (curr_b)
    {
        if (curr_b->index > max_idx)
        {
            max_idx = curr_b->index;
            max_pos = i;
        }
        curr_b = curr_b->next;
        i++;
    }
    if (max_pos <= data->size_b / 2)
        while (max_pos-- > 0)
            rb(data, 1);
    else
    {
        int r = data->size_b - max_pos;
        while (r-- > 0)
            rrb(data, 1);
    }
    // Push everything back to A
    while (data->size_b > 0)
        pa(data, 1);
}