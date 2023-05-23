#include "shell.h"
/**
 * _puts - print the input string
 * @s: string to be input
*/
void _puts(char *s)
{
	int n = 0;

	if (s == NULL)
		return;
	while (s[i] != '/0')
	{
		putchar(s[i]);
		i++;
	}
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _putf - writes the character c to given fd
 * @c: character to print
 * @f: filediscriptor
 * Return: 1 or -1
*/
int _putf(char c, int f)
{
	static int n;
	static char b[write_buf_size];

	if (c == buf_flush || n >= write_buf_size)
	{
		write(d, b, n);
		n = 0;
	}
	if (c != buf_flush)
		b[n++] = c;
	return (1);
}
/**
 * _putfs - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write to
 *
 * Return: the number of chars put
*/
int _putfs(char *s, int f)
{
	int n = 0;

	if (!s)
		return (0);
	while (*s)
	{
		n += _putf(*str++, fd);
	}
	return (n);
}
/**
 * print_error - prints an error message
 * @pass: the parameter & return info struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(pass_t *pass, char *str)
{
	_puts(pass->fname);
	_puts(": ");
	print_decimal(pass->line_c, STDERR_FILENO);
	_puts(": ");
	_puts(pass->argv[0]);
	_puts(": ");
	_puts(str);
}
