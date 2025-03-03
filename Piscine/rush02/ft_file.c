#include "rush02.h"

#define BUFF_SIZE 1024

static char *ft_strcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *read_file_no_lseek(const char *filepath)
{
	int		fd;
	char	buffer[BUFF_SIZE + 1];
	char	*result = NULL;
	char	*temp;
	int		bytes_read;
	int		total_len = 0;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = malloc(total_len + bytes_read + 1);
		if (!temp)
		{
			free(result);
			close(fd);
			return (NULL);
		}
		if (result)
		{
			ft_strcpy(temp, result);
			free(result);
		}
		else
			temp[0] = '\0';
		ft_strcpy(temp + total_len, buffer);
		total_len += bytes_read;
		temp[total_len] = '\0';
		result = temp;
	}
	close(fd);
	return (result);
}
