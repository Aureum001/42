/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:52:06 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/23 12:37:14 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/push_swap_bonus.h"

static void	init_data(t_data *data)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	data->size_a = 0;
	data->size_b = 0;
	data->buffer.count = 0;
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

static void	print_result(t_data *data)
{
	if (is_sorted(data->stack_a) && data->size_b == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
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
	process_commands(&data);
	print_result(&data);
	free_data(&data);
	return (0);
}
