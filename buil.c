#include "header.h"

/**
 * mexit - exit the shell
 * @info: Structure containing potential arguments. to maintain
 *          constant function prototype.
 *  Return: exit with a given exit stat
 *         (0) if info.argv[0] != "exit"
 */
int mexit(inft *info)
{
	int exitc;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitc = str_to_int(info->argv[1]);
		if (exitc == -1)
		{
			info->sts = 2;
			p_error(info, "Illegal number: ");
			pais(info->argv[1]);
			w_to_stdr('\n');
			return (1);
		}
		info->errcfe = str_to_int(info->argv[1]);
		return (-2);
	}
	info->errcfe = -1;
	return (-2);
}

/**
 * mcd - changes current drectory of a process
 * @info: structure containing potential arguments. to maintain
 *          constant function prototype.
 *  Return: 0
 */
int mcd(inft *info)
{
	char *s, *dr, buff[1024];
	int chdr_ret;

	s = getcwd(buff, 1024);
	if (!s)
		p_inp_str("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = g_env_v(info, "HOME=");
		if (!dr)
			chdr_ret = /* TODO: what should this be? */
				chdir((dr = g_env_v(info, "PWD=")) ? dr : "/");
		else
			chdr_ret = chdir(dr);
	}
	else if (str_c(info->argv[1], "-") == 0)
	{
		if (!g_env_v(info, "OLDPWD="))
		{
			p_inp_str(s);
			w_to_std_out('\n');
			return (1);
		}
		p_inp_str(g_env_v(info, "OLDPWD=")), w_to_std_out('\n');
		chdr_ret = /* TODO: what should this be? */
			chdir((dr = g_env_v(info, "OLDPWD=")) ? dr : "/");
	}
	else
		chdr_ret = chdir(info->argv[1]);
	if (chdr_ret == -1)
	{
		p_error(info, "can't cd to ");
		pais(info->argv[1]), w_to_stdr('\n');
	}
	else
	{
		init_new_env(info, "OLDPWD", g_env_v(info, "PWD="));
		init_new_env(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * mhelp - changes current drectory of a process
 * @info: structure containing potential arguments. to maintain
 *          constant function prototype.
 *  Return: 0
 */
int mhelp(inft *info)
{
	char **arga;

	arga = info->argv;
	p_inp_str("help call works. Function not yet implemented \n");
	if (0)
		p_inp_str(*arga); /* temp att_unused workaround */
	return (0);
}
