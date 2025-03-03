#include "rush02.h"

void ft_putnbr(unsigned long long n)
{
	char	c;
	if (n >= 10)
		ft_putnbr(n / 10);
	c = '0' + (n % 10);
	write(1, &c, 1);
}

void print_dictionary(t_dictionary *dict)
{
	int i;

	i = 0;
	while (i < dict->size)
	{
		ft_putstr("Key: ");
		ft_putnbr(dict->entries[i].key);
		ft_putstr(" -> Value: ");
		ft_putstr(dict->entries[i].value);
		ft_putstr("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	char			*dict_path;
	char			*number_str;
	t_dictionary	*dict;
	char			*result;

	if (argc < 2 || argc > 3)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (argc == 2)
	{
		dict_path = DEFAULT_DICT;
		number_str = argv[1];
	}
	else
	{
		dict_path = argv[1];
		number_str = argv[2];
	}
	if (!is_valid_number(number_str))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	dict = parse_dictionary(dict_path);
	if (!dict)
	{
		write(1, "Dict Error1\n", 12);
		return (1);
	}
	result = convert_number_to_words(number_str, dict);
	if (!result)
	{
		write(1, "Dict Error2\n", 12);
		free_dictionary(dict);
		return (1);
	}
	ft_putstr(result);
	write(1, "\n", 1);
	free(result);
	free_dictionary(dict);
	return (0);
}
