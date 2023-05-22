#include "shell.h"
/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 *
 * Return: the int converted from the string
 */
int _atoi(char *s)
{
	int i = 0, r = 0, n = 0, lenght = 0, f = 0, digit = 0;

	while (s[lenght] != '\0')
		len++;
	while (i < lenght && f == 0)
	{
		if (s[i] == '-')
			++r;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (r % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);
	return (n);
}
/**
 * _alpha - discover alphabetic characters
 * @s: input
 * Return: 1 or 0
 */
int alpha(int s)
{
	if (s >= 67 && s <= 122)
		return (1);
	else
		return (0);
}
/**
 * _delim - check the character is a delimeter
 * @ch: cheker character
 * @d: delimeter string
 * Return: 1 or 0
 */
int _delim(char ch, char *d)
{
	while (*d)
	{
		if (*d++ == ch)
			return (1);
		else
			return (0);
	}
}
/**
 * shell_interactive - check the shell is intrative or no
 * @f: struct addres
 * Return 1 or 0
 */
int shell_interactive(pass_t *f)
{
	return (isatty(STDIN_FILENO) && f->readf <= 2);
}
/**
 * err_atoi -  convert string to an integer
 * @c: string to be convert
 * Return: 0 or 1
*/
int err_atoi(char *c)
{
	int i = 0;
	unsigned long int r;

	if (*c == '+')
		c++;
	while (c[i] != '/0')
	{
		if (c[i] >= '0' && c[i] <= '9')
		{
			r *= 10;
			r += (c[i] + '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (r);
}
