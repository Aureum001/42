
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

int	parse_int(json *dst, FILE *stream)
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
	int i = 0;
	char c = getc(stream);  // Skip opening " (we already peeked and know it's there)

	while (1)
	{
		c = getc(stream);  // Read next character
		
		if (c == '"')  // Found closing quote - done!
			break ;
		if (c == EOF)  // Unterminated string
		{
			unexpected(stream);
			return NULL;
		}
		if (c == '\\')  // Escape sequence (\\ or \")
			c = getc(stream);  // Get the escaped character (skip backslash)
		res[i++] = c;  // Store character in result
	}
	return (res);
}

int parse_map(json *dst, FILE *stream)
{
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	char c = getc(stream);  // Skip opening { (we already peeked it)

	if (peek(stream) == '}')  // Empty map {} ?
		return 1;

	while (1)
	{
		c = peek(stream);
		if (c != '"')  // Key must be a string (starts with ")
		{
			unexpected(stream);
			return -1;
		}
		
		// Allocate space for one more key-value pair
		dst->map.data = realloc(dst->map.data, (dst->map.size + 1) * sizeof(pair));
		pair *current = &dst->map.data[dst->map.size];
		
		// Parse the key (must be a string)
		current->key = get_str(stream);
		if (current->key == NULL)
			return -1;
		dst->map.size++;
		
		// Expect : separator
		if (expect(stream, ':') == 0)
			return -1;
		
		// Parse the value (can be any type - recursively call argo)
		if (argo(&current->value, stream) == -1)
			return -1;
		
		c = peek(stream);
		if (c == '}')  // End of map
		{
			accept(stream ,c);  // Consume closing }
			break ;
		}
		if (c == ',')  // More pairs coming
			accept(stream, c);
		else
		{
			unexpected(stream);
			return -1;
		}
	}
	return 1;
}


int argo(json *dst, FILE *stream)
{
	int c = peek(stream);

	if (c == EOF)
	{
		unexpected(stream);
		return -1;
	}
	if (isdigit(c))
		return (parse_int(dst, stream));
	else if (c == '"')
	{
		dst->type = STRING;
		dst->string = get_str(stream);
		if (dst->string == NULL)
			return (-1);
		return (1);
	}
	else if (c == '{')
		return (parse_map(dst, stream));
	else
	{
		unexpected(stream);
		return -1;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	if (!stream)
		return (1);
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}
	serialize(file);
	printf("\n");
}

