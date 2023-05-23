#include "shell.h"
/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal (int inp, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int a, b;

	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (inp < 0)
	{
		a = -inp;
		__putchar('-');
		c++;
	}
	else
		a = input;
	b  = a;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (a / i)
		{
			__putchar('0' + b / i);
			c++;
		}
		b %= i;
	}
	__putchar('0' + b);
	c++;

	return (c);
}
/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int err_putchar(char c)
{
	static int n;
	static char b[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, b, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		b[n++] = c;
	return (1);
}
