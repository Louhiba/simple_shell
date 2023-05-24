include "header.h"

/**
 * len_lst - determine the length of the linked list
 * @h: the pointer to the first node
 *
 * Return: the size of the list
 */
size_t len_lst(const lstt *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * arr_of_str - return array of strings for the list->str
 * @head: the pointer to the first node
 *
 * Return: the array of the strings
 */
char **arr_of_str(lstt *head)
{
	lstt *node = head;
	size_t i = len_lst(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_l(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * p_all_ll - print all the elements for lstt linked list
 * @h: the pointer to the first node
 *
 * Return: the size of the list
 */
size_t p_all_ll(const lstt *h)
{
	size_t i = 0;

	while (h)
	{
		p_inp_str(conv_num(h->num, 10, 0));
		w_to_std_out(':');
		w_to_std_out(' ');
		p_inp_str(h->str ? h->str : "(nil)");
		p_inp_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nsw - return node whose string starts with the prefix
 * @node: the pointer to list the head
 * @prefix: the string to match
 * @c: next character after prefix to the match
 *
 * Return: match the node or null
 */
lstt *nsw(lstt *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gion - get index of the node
 * @head: the pointer to the list head
 * @node: the pointer to the node
 *
 * Return: the index of the node or -1
 */
ssize_t gion(lstt *head, lstt *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
