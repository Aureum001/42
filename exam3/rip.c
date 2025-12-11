#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	calculate_min_removals(char *str)
{
	int	open;
	int	close;
	int	i;

	open = 0;
	close = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void	generate_solutions(char *str, int min_removals, int index, int removals)
{
	char	saved;
	int		i;

	if (removals > min_removals)
		return ;
	if (removals == min_removals && calculate_min_removals(str) == 0)
	{
		puts(str);
		return ;
	}
	i = index;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			saved = str[i];
			str[i] = ' ';
			generate_solutions(str, min_removals, i + 1, removals + 1);
			str[i] = saved;
		}
		i++;
	}
}

int	validate_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		min_removals;

	if (argc != 2 || !argv[1][0])
		return (1);
	if (!validate_input(argv[1]))
		return (1);
	min_removals = calculate_min_removals(argv[1]);
	generate_solutions(argv[1], min_removals, 0, 0);
	return (0);
}