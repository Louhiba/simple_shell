#include "header.h"

/**
 * rsa_of_env - return string array copy of environ
 * @info: structure containing potential arguments.  to maintain
 *          constant function prototype.
 * Return: 0
 */
char **rsa_of_env(inft *info)
{
	if (!info->environ || info->envc)
	{
		info->environ = arr_of_str(info->env);
		info->envc = 0;
	}

	return (info->environ);
}

/**
 * mr_env_v - Remove the environment variable
 * @info: structure containing potential arguments.  to maintain
 *        constant function prototype.
 *  Return: 1 delete, or 0
 * @var: string env var property
 */
int mr_env_v(inft *info, char *var)
{
	lstt *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->envc = del_n_i(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envc);
}

/**
 * init_new_env - init new environment variable,
 *             or modify the existing one
 * @info: structure containing potential arguments. to maintain
 *        constant function prototype.
 * @var: string env var property
 * @value: string env var value
 *  Return: 0
 */
int init_new_env(inft *info, char *var, char *value)
{
	char *buf = NULL;
	lstt *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_l(var) + str_l(value) + 2);
	if (!buf)
		return (1);
	str_copy(buf, var);
	con_s(buf, "=");
	con_s(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envc = 1;
			return (0);
		}
		node = node->next;
	}
	an_endo_l(&(info->env), buf, 0);
	free(buf);
	info->envc = 1;
	return (0);
}
