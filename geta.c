#include "header.h"

/**
 * clr_inf - init inft struct
 * @info: the struct address
 */
void clr_inf(inft *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * s_inf - init inft struct
 * @info: the struct address
 * @av: the argument vector
 */
void s_inf(inft *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_spl_2(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dupl_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		r_al(info);
		r_vrs(info);
	}
}

/**
 * fr_inf - clear inft struct fields
 * @info: the struct address
 * @all: true if clearing all fields
 */
void fr_inf(inft *info, int all)
{
	fsos(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->c_b)
			free(info->arg);
		if (info->env)
			f_lst(&(info->env));
		if (info->history)
			f_lst(&(info->history));
		if (info->alias)
			f_lst(&(info->alias));
		fsos(info->environ);
			info->environ = NULL;
		fr_p_a((void **)info->c_b);
		if (info->rdfd > 2)
			close(info->rdfd);
		w_to_std_out(BUFF_FL);
	}
}
