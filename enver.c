#include "header.h"

/**
 * p_cur_v - print current environme
 * @info: structure containing potential arguments. to maintain
 *          constant function prototype.
 * Return: 0
 */
int p_cur_v(inft *info)
{
	p_ostr_ll(info->env);
	return (0);
}

/**
 * g_env_v - the value of an environ variable
 * @info: structure containing potential arguments. to maintain
 * @name: the env var name
 *
 * Return: value
 */
char *g_env_v(inft *info, const char *name)
{
	lstt *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_envv_or_m - Initi new environment variable,
 *             or modify existing one
 * @info: structure containing potential arguments. to maintain
 *        constant function prototype.
 *  Return: 0
 */
int init_envv_or_m(inft *info)
{
	if (info->argc != 3)
	{
		pais("Incorrect number of arguements\n");
		return (1);
	}
	if (init_new_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * raev - rm an environment variable
 * @info: structure containing potential arguments.  to maintain
 *        constant function prototype.
 *  Return: 0
 */
int raev(inft *info)
{
	int i;

	if (info->argc == 1)
	{
		pais("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		mr_env_v(info, info->argv[i]);

	return (0);
}

/**
 * pell - the populates env linked list
 * @info: structure containing potential arguments. to maintain
 *          constant function prototype.
 * Return: 0
 */
int pell(inft *info)
{
	lstt *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		an_endo_l(&node, environ[i], 0);
	info->env = node;
	return (0);
}
