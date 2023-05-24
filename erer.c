#include "header.h"

/**
 *pais - print input string
 * @str: string to be printed
 *
 * Return: void func
 */
void pais(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		w_to_stdr(str[i]);
		i++;
	}
}

/**
 * w_to_stdr - writes c character to stderr
 * @c: character to be printed
 *
 * Return: 1 success.
 * On error, -1 returned, errno is set appropriately.
 */
int w_to_stdr(char c)
{
	static int i;
	static char buf[W_BUFF_S];

	if (c == BUFF_FL || i >= W_BUFF_S)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFF_FL)
		buf[i++] = c;
	return (1);
}

/**
 * wc_to_fd - writes c character to given fd
 * @c: character to be printed
 * @fd: filedescriptor to write to
 *
 * Return: 1 on success.
 * On error, -1 returned, errno is set appropriately.
 */
int wc_to_fd(char c, int fd)
{
	static int i;
	static char buf[W_BUFF_S];

	if (c == BUFF_FL || i >= W_BUFF_S)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFF_FL)
		buf[i++] = c;
	return (1);
}

/**
 *pains - print input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int pains(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += wc_to_fd(*str++, fd);
	}
	return (i);
}
