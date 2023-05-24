#include "header.h"

/**
 * msl - the main loop of the shell
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 success, 1 error, or error code
 */
int msl(inft *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clr_inf(info);
		if (inter(info))
			p_inp_str("$ ");
		w_to_stdr(BUFF_FL);
		r = g_inp(info);
		if (r != -1)
		{
			s_inf(info, av);
			builtin_ret = fbuild(info);
			if (builtin_ret == -1)
				fcmd(info);
		}
		else if (inter(info))
			w_to_std_out('\n');
		fr_inf(info, 0);
	}
	w_hst(info);
	fr_inf(info, 1);
	if (!inter(info) && info->sts)
		exit(info->sts);
	if (builtin_ret == -2)
	{
		if (info->errcfe == -1)
			exit(info->sts);
		exit(info->errcfe);
	}
	return (builtin_ret);
}

/**
 * fbuild - find a builtin cmd
 * @info: parameter & return info struct
 *
 * Return: -1 if builtin has not found,
 *			0 if builtin has executed successfully,
 *			1 if builtin has founded but not successful,
 *			-2 if builtin signals exit()
 */
int fbuild(inft *info)
{
	int i, built_in_ret = -1;
	blt_t builtintbl[] = {
		{"exit", mexit},
		{"env", p_cur_v},
		{"help", mhelp},
		{"history", myhistory},
		{"setenv", init_envv_or_m},
		{"unsetenv", raev},
		{"cd", mcd},
		{"alias", myaliases},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_c(info->argv[0], builtintbl[i].type) == 0)
		{
			info->err_c++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fcmd - finds a cmd in PATH
 * @info: parameter & return info struct
 *
 * Return: void func
 */
void fcmd(inft *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lcf == 1)
	{
		info->err_c++;
		info->lcf = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!dlm(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = f_path(info, g_env_v(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fkcmd(info);
	}
	else
	{
		if ((inter(info) || g_env_v(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->sts = 127;
			p_error(info, "not found\n");
		}
	}
}

/**
 * fkcmd - forks an exec thread to run command
 * @info: parameter & return info struct
 *
 * Return: void func
 */
void fkcmd(inft *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, rsa_of_env(info)) == -1)
		{
			fr_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->sts));
		if (WIFEXITED(info->sts))
		{
			info->sts = WEXITSTATUS(info->sts);
			if (info->sts == 126)
				p_error(info, "Permission denied\n");
		}
	}
}
