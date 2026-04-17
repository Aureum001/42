#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;

void	free_json(json j);
int	argo(json *dst, FILE *stream);
int	peek(FILE *stream);
void	unexpected(FILE *stream);
int	accept(FILE *stream, char c);
int	expect(FILE *stream, char c);
void	free_json(json j);
void	serialize(json j);

int parse_map(json *dst, FILE *stream);
int parse_int(json *dst, FILE *stream);
int parser(json *dst, FILE *stream);
int argo(json *dst, FILE *stream);
char *get_str(FILE *stream);

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

void	free_json(json j)
{
	switch (j.type)
	{
		case MAP:
			for (size_t i = 0; i < j.map.size; i++)
			{
				free(j.map.data[i].key);
				free_json(j.map.data[i].value);
			}
			free(j.map.data);
			break ;
		case STRING:
			free(j.string);
			break ;
		default:
			break ;
	}
}

void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}

int parse_int(json *dst, FILE *stream)
{
	int n = 0;
	fscanf(stream, "%d", &n);
	dst->type = INTEGER;
	dst->integer = n;
	return (1);
}

char *get_str(FILE *stream)
{
	char *res = calloc(4096, sizeof(char));
	if (!res)
		return (NULL);
	int		i = 0;
	char c = getc(stream);

	while (1)
	{
		c = getc(stream);
		if (c == EOF)
		{
			unexpected(stream);
			return (NULL);
		}
		if (c == '"')
			break ;
		if (c == '\\')
			c = getc(stream);
		res[i++] = c;
	}
	return (res);
}

int parse_map(json *dst, FILE *stream)
{
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	char c = getc(stream);
	if (peek(stream) == '}')
		return (1);

	while (1)
	{
		c = peek(stream);
		if (c != '"')
		{
			unexpected(stream);
			return (-1);
		}
		dst->map.data = realloc(dst->map.data, (dst->map.size + 1) * sizeof(pair));
		pair *current = &dst->map.data[dst->map.size];
		current->key = get_str(stream);
		if (!current->key)
			return (-1);
		dst->map.size++;
		if (expect(stream, ':') == 0)
			return (1);
		if (argo(&current->value, stream) == -1)
			return (-1);
		c = peek(stream);
		if (c == '}')
		{
			accept(stream, c);
			break ;
		}
		if (c == ',')
			accept(stream, c);
		else
		{
			unexpected(stream);
			return (-1);
		}
	}
	return (1);
}

int argo(json *dst, FILE *stream)
{
	char c = peek(stream);
	
	if (c == EOF)
	{
		unexpected(stream);
		return (-1);
	}
	if (isdigi(c))
	{
		return (parse_int(dst, stream));
	}
	if (c == '"')
	{
		dst->type = STRING;
		dst->string = get_str(stream);
		if (!dst->string)
			return (-1);
	}
}
