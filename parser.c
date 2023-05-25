#include "header.h"

/**
 * is_cmd - determine file is an executable cmd
 * @info: info of the struct
 * @path: the path to the file
 *
 * Return: 1 true, or 0
 */
int is_cmd(inft *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dp_c - the duplicate characters
 * @pathstr: PATH of string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: the pointer to the new buffer
 */
char *dp_c(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * f_path - find this cmd in the PATH string
 * @info: info of struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: full PATH of cmd if found or NULL
 */
char *f_path(inft *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_l(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dp_c(pathstr, curr_pos, i);
			if (!*path)
				con_s(path, cmd);
			else
			{
				con_s(path, "/");
				con_s(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
