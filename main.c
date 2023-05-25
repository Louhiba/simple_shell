#include "header.h"

/**
 * main - the entry point of the program
 * @ac: the arg count
 * @av: the arg vector
 *
 * Return: 0 success, or 1 error
 */
int main(int ac, char **av)
{
	inft info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				pais(av[0]);
				pais(": 0: Can't open ");
				pais(av[1]);
				w_to_stdr('\n');
				w_to_stdr(BUFF_FL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->rdfd = fd;
	}
	pell(info);
	r_hst(info);
	msl(info, av);
	return (EXIT_SUCCESS);
}
