/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/19 11:46:37 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	init_data(t_data *data)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	data->size_a = 0;
	data->size_b = 0;
}

static void	parse_arguments(t_data *data, int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			error_exit(data);
		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			error_exit(data);
		stack_add_back(&data->stack_a, stack_new((int)num));
		data->size_a++;
		i++;
	}
	if (has_duplicates(data->stack_a))
		error_exit(data);
}

void	push_swap(t_data *data)
{
	if (is_sorted(data->stack_a))
		return ;
	if (data->size_a == 2)
	{
		if (data->stack_a->value > data->stack_a->next->value)
			sa(data, 1);
	}
	else if (data->size_a == 3)
		sort_three(data);
	else if (data->size_a <= 5)
		sort_five(data);
	else
		greedy_sort(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	init_data(&data);
	if (!is_valid_input(argc, argv))
		error_exit(&data);
	parse_arguments(&data, argc, argv);
	push_swap(&data);
	print_optimized_moves();
	if (!is_sorted(data.stack_a))
		ft_printf("Not sorted");
	free_data(&data);
	return (0);
}
