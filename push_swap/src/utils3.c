/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:00 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/12 11:03:12 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_max_bits(t_stack *stack)
{
	int	max_num;
	int	max_bits;

	max_num = stack_size(stack) - 1;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	assign_index(t_data *data)
{
	t_stack	*current;
	t_stack	*compare;
	int		index;

	current = data->stack_a;
	while (current)
	{
		index = 0;
		compare = data->stack_a;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}
