#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int c;
	int found = 0;
	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			break;
		}
		found = 1;
	}
	return found;
}

int match_char(FILE *f, char c)
{
	int got = fgetc(f);
	if (got == c)
		return 1;
	if (got != EOF)
		ungetc(got, f);
	return 0;
}

int scan_char(FILE *f, va_list ap)
{
	int *out = va_arg(ap, int *);
	int c = fgetc(f);
	if (c == EOF)
		return 0;
	*out = c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
	int *out = va_arg(ap, int *);
	int c, sign = 1, val = 0, found = 0;

	match_space(f);
	c = fgetc(f);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (isdigit(c))
	{
		val = val * 10 + (c - '0');
		found = 1;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (found)
	{
		*out = val * sign;
		return 1;
	}
	return 0;
}

int scan_string(FILE *f, va_list ap)
{
	char *out = va_arg(ap, char *);
	int c, i = 0;

	match_space(f);
	while ((c = fgetc(f)) != EOF && !isspace(c))
		out[i++] = c;
	if (c != EOF)
		ungetc(c, f);
	if (i > 0)
	{
		out[i] = '\0';
		return 1;
	}
	return 0;
}

int match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void)
{
	int x, y;
	char c;
	char str[100];
	printf("Enter: <int> <char> <string> <int>\n");
	int n = ft_scanf("%d %c %s %d", &x, &c, str, &y);
	printf("Scanned %d items: x=%d, c='%c', str='%s', y=%d\n", n, x, c, str, y);
	return 0;
}