/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:00:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/13 17:19:31 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	initialize_data(t_data *data)
{
    data->stack_a = NULL;
    data->stack_b = NULL;
    data->size_a = 0;
    data->size_b = 0;
}

static int	validate_argument_format(const char *arg)
{
    int	i;

    i = 0;
    if (arg[i] == '-' || arg[i] == '+')
        i++;
    if (arg[i] == '\0')
        return (0);
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (0);
        i++;
    }
    return (1);
}

int	is_valid_input_precheck(int argc, char **argv)
{
    int	i;

    i = 1;
    while (i < argc)
    {
        if (!validate_argument_format(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

static int	check_for_duplicates_in_stack(t_stack *stack)
{
    t_stack	*current;
    t_stack	*runner;

    current = stack;
    while (current)
    {
        runner = current->next;
        while (runner)
        {
            if (current->value == runner->value)
                return (1);
            runner = runner->next;
        }
        current = current->next;
    }
    return (0);
}

void	populate_initial_stack(t_data *data, int argc, char **argv)
{
    int		i;
    long	num;
    int		error_flag;
    t_stack	*new_node; // Declare a pointer for the new node

    i = 1;
    error_flag = 0;
    while (i < argc)
    {
        num = ft_atol_ps(argv[i], &error_flag);
        if (error_flag || num > 2147483647 || num < -2147483648)
        {
            error_exit(data);
        }
        new_node = stack_new((int)num); // Create the new node
        if (!new_node) // Check if stack_new failed (e.g., malloc error)
        {
            error_exit(data); // Or handle error appropriately
        }
        stack_add_back(&(data->stack_a), new_node); // Use stack_add_back
        data->size_a++;
        i++;
    }
    if (check_for_duplicates_in_stack(data->stack_a))
    {
        error_exit(data);
    }
}