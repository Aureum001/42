#include "rush02.h"

static int count_lines(const char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static int parse_line(char *line, t_dictionary *dict)
{
	char	*colon;

	if (line[0] == '\0')
		return (0);
	colon = line;
	while (*colon && *colon != ':')
		colon++;
	if (*colon != ':')
		return (-1);
	*colon = '\0';
	dict->entries[dict->size].key = ft_atoi(line);
	dict->entries[dict->size].value = ft_strdup(ft_strtrim(colon + 1));
	if (!dict->entries[dict->size].value)
		return (-1);
	dict->size++;
	return (1);
}

static int process_buffer_into_dict(char *buffer, t_dictionary *dict)
{
	char	*line_start;
	int		i;
	int		ret;
	int		is_end;

	line_start = buffer;
	i = 0;
	while (1)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			is_end = (buffer[i] == '\0'); 
			buffer[i] = '\0';
			ret = parse_line(line_start, dict);
			if (ret == -1)
				return (-1);
			if (is_end)
				break ;
			line_start = buffer + i + 1;
		}
		i++;
	}
	return (0);
}

t_dictionary *parse_dictionary(const char *filepath)
{
	char			*buffer;
	int				line_count;
	t_dictionary	*dict;
	int				ret;

	buffer = read_file_no_lseek(filepath);
	if (!buffer)
		return (NULL);
	line_count = count_lines(buffer);
	dict = malloc(sizeof(t_dictionary));
	if (!dict)
	{
		free(buffer);
		return (NULL);
	}
	dict->entries = malloc(sizeof(t_dict_entry) * (line_count + 1));
	if (!dict->entries)
	{
		free(dict);
		free(buffer);
		return (NULL);
	}
	dict->size = 0;
	ret = process_buffer_into_dict(buffer, dict);
	free(buffer);
	if (ret == -1)
	{
		free_dictionary(dict);
		return (NULL);
	}
	return (dict);
}

void free_dictionary(t_dictionary *dict)
{
	int	i;

	if (!dict)
		return;
	i = 0;
	while (i < dict->size)
	{
		if (dict->entries[i].value)
			free(dict->entries[i].value);
		i++;
	}
	free(dict->entries);
	free(dict);
}
