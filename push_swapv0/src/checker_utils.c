/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:23:09 by ancanale          #+#    #+#             */
/*   Updated: 2025/06/13 18:53:08 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	remove_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

static void	process_commands(t_data *data)
{
	char	*line;
	int		apply_status_ok;

	line = get_next_line(0); // Initial read
	
	while (line != NULL)
	{
		ft_printf("%s", line);
		remove_newline(line);
		ft_printf("%s", line);
		apply_status_ok = apply_command(line, data);
		
		free(line); // Free the memory allocated by get_next_line

		if (!apply_status_ok)
		{
			// If apply_command indicated an invalid command, error_exit.
			// error_exit itself will handle freeing data and exiting.
			error_exit(data); 
		}
		line = get_next_line(0); // Read next line for the next iteration
	}
}

static void	print_result(t_data *data)
{
	if (is_sorted(data->stack_a) && data->size_b == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	initialize_data(&data);
	if (!is_valid_input_precheck(argc, argv))
		error_exit(&data);
	populate_initial_stack(&data, argc, argv);
	assign_index(&data);
	process_commands(&data);
	print_result(&data);
	free_data(&data);
	return (0);
}
