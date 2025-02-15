#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define DEFAULT_DICT "numbers.dict"

typedef struct s_dict_entry
{
	unsigned long long	key;
	char				*value;
}	t_dict_entry;

typedef struct s_dictionary
{
	t_dict_entry	*entries;
	int				size;
}	t_dictionary;

t_dictionary	*parse_dictionary(const char *filepath);
void			free_dictionary(t_dictionary *dict);
char			*convert_number_to_words(const char *number_str, t_dictionary *dict);
int				is_valid_number(const char *str);
void			ft_putstr(char *str);
char			*ft_strdup(const char *src);
unsigned long long	ft_atoi(const char *str);
char			*ft_strtrim(char *str);
int				ft_strlen(char *str);
char			*read_file_no_lseek(const char *filepath);

#endif
