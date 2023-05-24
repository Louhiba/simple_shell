#include "header.h"

/**
 * myhistory - displays history list, one cmd by line, preceded
 *              with line num, starting at 0.
 * @info: structure containing potential arguments. to maintain
 *        constant function prototype.
 *  Return: 0
 */
int myhistory(inft *info)
{
	p_all_ll(info->history);
	return (0);
}

/**
 * unset_aliases - set alias to string
 * @info: struct param
 * @str: string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_aliases(inft *info, char *str)
{
	char *p, c;
	int ret;

	p = lcis(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_n_i(&(info->alias),
		gion(info->alias, nsw(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_aliases - set alias to string
 * @info: struct param
 * @str: string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_aliases(inft *info, char *str)
{
	char *p;

	p = lcis(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliases(info, str));

	unset_aliases(info, str);
	return (an_endo_l(&(info->alias), str, 0) == NULL);
}

/**
 * print_aliases - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_aliases(lstt *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = lcis(node->str, '=');
		for (a = node->str; a <= p; a++)
			w_to_std_out(*a);
		w_to_std_out('\'');
		p_inp_str(p + 1);
		p_inp_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * myaliases - mimics alias builtin (man alias)
 * @info: structure containing potential arguments. to maintain
 *          constant function prototype.
 *  Return: 0
 */
int myaliases(inft *info)
{
	int i = 0;
	char *p = NULL;
	lstt *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_aliases(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = lcis(info->argv[i], '=');
		if (p)
			set_aliases(info, info->argv[i]);
		else
			print_aliases(nsw(info->alias, info->argv[i], '='));
	}

	return (0);
}
