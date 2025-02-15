#include "rush02.h"

static char	*lookup_in_dict(t_dictionary *dict, unsigned long long key)
{
	int	i;

	i = 0;
	while (i < dict->size)
	{
		if (dict->entries[i].key == key)
			return (dict->entries[i].value);
		i++;
	}
	return (NULL);
}

static char	*join_words(char *s1, char *s2)
{
	int	i;
	int	j;
	char *result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = ' ';
	j = 0;
	while (j < ft_strlen(s2))
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

char	*convert_number_to_words(const char *number_str, t_dictionary *dict)
{
	unsigned long long num;
	char *result = NULL;
	char *temp = NULL;
	char *lookup = NULL;

	num = ft_atoi(number_str);
	if (num == 0)
	{
		lookup = lookup_in_dict(dict, 0);
		if (!lookup)
			return (NULL);
		return (ft_strdup(lookup));
	}
	if (num >= 100)
	{
		unsigned long long hundreds = num / 100;
		lookup = lookup_in_dict(dict, hundreds);
		if (!lookup)
		    return (NULL);
		result = ft_strdup(lookup);
		temp = lookup_in_dict(dict, 100);
		if (!temp)
			return (NULL);
		result = join_words(result, temp);
		num %= 100;
		if (num == 0)
			return (result);
	}
	if (num < 20)
	{
		lookup = lookup_in_dict(dict, num);
		if (!lookup)
			return (NULL);
		if (result)
		{
			temp = join_words(result, lookup);
			free(result);
			result = temp;
		}
		else
			result = ft_strdup(lookup);
	}
	else
	{
		unsigned long long tens = (num / 10) * 10;
		unsigned long long ones = num % 10;
		lookup = lookup_in_dict(dict, tens);
		if (!lookup)
			return (NULL);
		if (result)
		{
			temp = join_words(result, lookup);
			free(result);
			result = temp;
		}
		else
			result = ft_strdup(lookup);
		if (ones)
		{
			lookup = lookup_in_dict(dict, ones);
			if (!lookup)
				return (NULL);
			temp = join_words(result, lookup);
			free(result);
			result = temp;
		}
	}
	return (result);
}
