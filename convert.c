#include "header.h"

/**
 * inter - re true if shell is inter mode
 * @info: struct addr
 *
 * Return: 1 if inter mode, or 0 otherwise
 */
int inter(inft *info)
{
	return (isatty(STDIN_FILENO) && info->rdfd <= 2);
}

/**
 * dlm - check if the character is a delimeter
 * @c: the chara to check
 * @delim: delimeter string
 * Return: 1 true, 0 false
 */
int dlm(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *alph - check for alphabetic charac
 *@c: charac to input
 *Return: 1 c is alphabetic, or 0 otherwise
 */

int alph(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *cnv - convert string to an integer
 *@s: string to be converted
 *Return: 0 if no numbers in string, or convert the number
 */

int cnv(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
