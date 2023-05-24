#include "header.h"

/**
 * str_to_int - convert string to integer
 * @s: string to be converted
 * Return: 0 no numbers in string, or converted number
 *       -1 error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * p_error - print error message
 * @info: parameter and return info struct
 * @estr: string withe the specified error type
 * Return: 0 no numbers in string, or converted to number
 *        -1 error
 */
void p_error(inft *info, char *estr)
{
	pais(info->fname);
	pais(": ");
	p_d_num(info->err_c, STDERR_FILENO);
	pais(": ");
	pais(info->argv[0]);
	pais(": ");
	pais(estr);
}

/**
 * p_d_num - func prints decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: num of characters printed
 */
int p_d_num(int input, int fd)
{
	int (*_w_to_std_out)(char) = w_to_std_out;
	int i, count = 0;
	unsigned int abs, current;

	if (fd == STDERR_FILENO)
		_w_to_std_out = w_to_stdr;
	if (input < 0)
	{
		abs = -input;
		_w_to_std_out('-');
		count++;
	}
	else
		abs = input;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			_w_to_std_out('0' + current / i);
			count++;
		}
		current %= i;
	}
	_w_to_std_out('0' + current);
	count++;

	return (count);
}

/**
 * conv_num - converter func, clone of itoa
 * @num: the number
 * @base: the base
 * @flags: the argument flags
 *
 * Return: the string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONV_U) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONV_L ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comm - function replaces the first instance of '#' with '\0'
 * @buf: the address of string to be modifyed
 *
 * Return: 0;
 */
void rm_comm(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
