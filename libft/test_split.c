#include <stdlib.h>
#include <stdio.h>

int	c_in(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	count_words(char *str, char *sep)
{
	int	i;
	int	n_words;

	i = 0;
	n_words = 0;
	while (str[i])
	{
		while (str[i] && c_in(str[i], sep))
			i++;
		if (str[i])
			n_words++;
		while (str[i] && !c_in(str[i], sep))
			i++;
	}
	return (n_words);
}

int	ft_word_len(char *str, char *sep)
{
	int	len;

	len = 0;
	while (str[len] && !c_in(str[len], sep))
		len++;
	return (len);
}

char	*allocate_word(char *str, char *sep)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = ft_word_len(str, sep);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *sep)
{
	int		i;
	int		n_words;
	char	**strings;

	i = 0;
	n_words = count_words(str, sep);
	strings = (char **)malloc(sizeof(char *) * (n_words + 1));
	while (*str)
	{
		while (*str && c_in(*str, sep))
			str++;
		if (*str)
		{
			strings[i] = allocate_word(str, sep);
			if (!strings[i])
				return (NULL);
			i++;
		}
		while (*str && !c_in(*str, sep))
			str++;
	}
	strings[i] = NULL;
	return (strings);
}


int main(void) {
    char *s = "h ello";
    char c = ' ';
    char *expected[] = {"h","ello", NULL};
	char **result = ft_split(s, &c);
	for (int i = 0; expected[i] != NULL; i++) {
		printf("%s vs %s \n", expected[i], result[i]);
		free(result[i]);
	}
	free(result);

    printf("Test with leading delimiter passed (if no segfault)!\n");
    return 0;
}